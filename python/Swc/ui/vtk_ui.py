import vtk
import readMostd as rm
import numpy as np
import libtiff
import treelib

class MyStyle(vtk.vtkInteractorStyleImage):
    def __init__(self):
        self.AddObserver("MouseWheelForwardEvent", self.slice_add)
        self.AddObserver("MouseWheelBackwardEvent", self.slice_sub)
        self.AddObserver("CharEvent", self.key_control)
        self.AddObserver("LeftButtonPressEvent", self.do_trace)
    
    def slice_add(self, obj, e):
        global t, im_view
        if im_view.GetSlice() < t - 1:
            self.clearAllActors()            
            im_view.SetSlice(im_view.GetSlice() + 1) 
        elif im_view.GetSlice() == (t - 1):
            self.clearAllActors()
            im_view.SetSlice(0)
        self.showSphereInSlice()
        self.showLinesInSlice()  
            
    def slice_sub(self, obj, e):
        global t, im_view
        if im_view.GetSlice() > 0:
            self.clearAllActors()
            im_view.SetSlice(im_view.GetSlice() - 1)
        elif im_view.GetSlice() == 0:
            self.clearAllActors()
            im_view.SetSlice(t - 1)
        self.showSphereInSlice()
        self.showLinesInSlice()  
            
    
    def key_control(self, obj, e):
        global im_view, trace_mode, choose_mode
        key_code = self.GetInteractor().GetKeyCode()                #str -- key_code
        if key_code == "+":
            cur_level = im_view.GetColorLevel()
            if cur_level < 80:
                im_view.SetColorLevel(cur_level + 1)
            elif cur_level >= 80:
                im_view.SetColorLevel(80)
            im_view.Render()
        elif key_code == "-":
            cur_level = im_view.GetColorLevel()
            if cur_level >  20:
                im_view.SetColorLevel(cur_level - 1)
            elif cur_level <= 20:
                im_view.SetColorLevel(20)
            im_view.Render()
        elif key_code == "1":
            print "Start Trace"
            trace_mode = True
        elif key_code == "2":
            print "End Trace"
            trace_mode = False
        elif key_code == "3":
            print "Start Choose"
            choose_mode = True
        elif key_code == "4":
            print "End Choose"
            choose_mode = False
        elif key_code == "5":
            print "Change Images"
        
    def clearAllActors(self):
        global iren, im_view, showed_spheres, showed_lines
        spheres_num = len(showed_spheres)
        lines_num = len(showed_lines)
        ren = im_view.GetRenderer()
        for i in xrange(spheres_num):
            ren.RemoveActor(showed_spheres[i])
        for i in xrange(lines_num):
            ren.RemoveActor(showed_lines[i])
        im_view.Render()        
    
    def showSphereInSlice(self):
        global im_view, showed_spheres, traced_lines, cur_picked_point, color_red, color_green, traced_tree
        this_slice = im_view.GetSlice()
        if traced_tree.size() == 0:
            return 0
        for node_id in traced_tree.expand_tree(traced_tree.root, mode=treelib.Tree.WIDTH):
            this_node = traced_tree.get_node(node_id)
            this_line = this_node.tag
            for i in xrange(len(this_line)):
                this_point = this_line[i]
                if this_point[2] != this_slice:
                    continue
                else:
                    if this_point != cur_picked_point.tolist():
                        self.ShowPoint(this_point, color_green)
                    else:
                        self.ShowPoint(this_point, color_red)
        
    def do_trace(self, obj, e):             
        global im_view, trace_mode, cur_picked_point, trace_mode, traced_lines, color_red, color_green, traced_tree
        cur_slice = im_view.GetSlice()
        click_pos = self.GetInteractor().GetEventPosition()
        if trace_mode == True and choose_mode == False:
            if cur_picked_point == [] and len(traced_lines) != 0:
                print "Must Choose a Point to Start!"
            else:
                trace_picker = vtk.vtkCellPicker()
                trace_picker.Pick(click_pos[0], click_pos[1], cur_slice, im_view.GetRenderer())
                picked_pos = trace_picker.GetPickPosition()
                traced_point = np.require(picked_pos, dtype=np.uint16)
                self.save2lines(traced_point)
                self.ShowPoint(traced_point, color_red)
                if cur_picked_point != []:
                    self.ShowLine(cur_picked_point.tolist(), traced_point.tolist())
                self.changeColor(traced_point, color_green, color_red)
                cur_picked_point = traced_point
        if choose_mode == True and trace_mode == False:
            if traced_tree.size() == 0:
                print "No Point to Choose, Please Trace First!"
            else:    
                choose_picker = vtk.vtkPropPicker()
                choose_picker.Pick(click_pos[0], click_pos[1], cur_slice, im_view.GetRenderer())
                if choose_picker.GetActor() != None:
                    choosen_point = choose_picker.GetActor().GetMapper().GetInput().GetCenter()
                    choosen_point = np.array(choosen_point, dtype=np.uint16)
                    self.changeColor(choosen_point, color_green, color_red)                  
                    cur_picked_point = choosen_point
                else:
                        print "Please Choose a Point"
    
    def save2lines(self, point1):
        global traced_lines, traced_tree, cur_picked_point
        if traced_tree.size() == 0:
            tree_root = treelib.Node([point1.tolist()])
            traced_tree.add_node(tree_root, parent=None)
        else:
            for node_id in traced_tree.expand_tree(traced_tree.root, mode=treelib.Tree.WIDTH):
                this_node = traced_tree.get_node(node_id)
                this_line = this_node.tag
                if cur_picked_point.tolist() in this_line:
                    cur_point_index = this_line.index(cur_picked_point.tolist())
                    if cur_point_index == 0 and len(this_line) != 1:
                        this_line.insert(0, point1.tolist())
                        this_node.tag = this_line
                    elif cur_point_index == 0 and len(this_line) == 1:
                        this_line.append(point1.tolist())
                        this_node.tag = this_line                        
                    elif cur_point_index == len(this_line) - 1:
                        this_line.append(point1.tolist())
                        this_node.tag = this_line
                    else:
                        new_node = treelib.Node([cur_picked_point.tolist(), point1.tolist()])
                        traced_tree.add_node(new_node, parent=this_node.identifier)
                    break
                
    def showLinesInSlice(self):
        global traced_tree, traced_lines, im_view
        if traced_tree.size() == 0:
            return
        this_slice = im_view.GetSlice()
        for node_id in traced_tree.expand_tree(traced_tree.root, mode=treelib.Tree.WIDTH):
            this_node = traced_tree.get_node(node_id)
            this_line = this_node.tag
            if len(this_line) == 1:
                continue
            else:
                for (this_point_index, this_point) in enumerate(this_line):
                    if this_point_index == len(this_line) - 1:
                        continue
                    else:
                        next_point = this_line[this_point_index + 1]
                        if this_point[2] == this_slice or next_point[2] == this_slice:
                            self.ShowLine(this_point, next_point)
                    
    def ShowLine(self, point1, point2):
        global im_view, color_yellow, showed_actors
        ren = im_view.GetRenderer()
        tmp_source = vtk.vtkLineSource()
        tmp_source.SetPoint1(point1[0], point1[1], point1[2])
        tmp_source.SetPoint2(point2[0], point2[1], point2[2])
        tmp_mapper = vtk.vtkPolyDataMapper()
        tmp_mapper.SetInput(tmp_source.GetOutput())
        tmp_actor = vtk.vtkActor()
        tmp_actor.SetMapper(tmp_mapper)
        tmp_actor.GetProperty().SetLineWidth(2.0)
        tmp_actor.GetProperty().SetColor(color_yellow[0], color_yellow[1], color_yellow[2])
        showed_lines.append(tmp_actor)
        ren.AddActor(tmp_actor)
        im_view.Render()
        
    def changeColor(self, point1, color1, color2):
        global iren, im_view, traced_lines, showed_points, cur_picked_point, color_green, color_red, showed_spheres
        sphere_num = len(showed_spheres)
        if len(cur_picked_point) == 0:
            return 0
        if sphere_num == 0:
            return -1
        else:
            for i in xrange(sphere_num):
                this_sphere = showed_spheres[i]
                this_center = this_sphere.GetMapper().GetInput().GetCenter()
                this_center = np.array(this_center, dtype=np.uint16)
                if this_center.tolist() == cur_picked_point.tolist():
                    this_sphere.GetProperty().SetColor(color1[0], color1[1], color1[2])
                elif this_center.tolist() == point1.tolist():
                    this_sphere.GetProperty().SetColor(color2[0], color2[1], color2[2])
            im_view.Render()
        return 0

    def ShowPoint(self, point1, color1):
        global iren, im_view, showed_points, showed_spheres
        showed_points.append(point1)
        tmp_source = vtk.vtkSphereSource()
        tmp_source.SetCenter(point1[0], point1[1], point1[2])
        tmp_source.SetRadius(2.0)
        tmp_mapper = vtk.vtkPolyDataMapper()
        tmp_mapper.SetInput(tmp_source.GetOutput())
        tmp_actor = vtk.vtkActor()
        tmp_actor.SetMapper(tmp_mapper)
        tmp_actor.GetProperty().SetColor(color1[0], color1[1], color1[2])
        showed_spheres.append(tmp_actor)
        im_view.GetRenderer().AddActor(tmp_actor)
        im_view.Render()


# xs = 17800
# ys = 20300
# zs = 2400
w = 512
h = 512
t = 512
color_red = [255.0, 0.0, 0.0]
color_green = [0.0, 255.0, 0.0]
color_yellow = [255.0, 255.0, 0.0]
showed_spheres = []
showed_lines = []
showed_points = []
choose_mode = False
trace_mode = False
traced_tree = treelib.Tree()
traced_lines = [] 
cur_picked_point = []


# roi1 = rm.Roi((xs, ys, zs, w, h, t), r"TDI072.mostd")
# used_image = roi1.getImages()
tiff3d_obj = libtiff.TIFF3D.open(r'G:\\sulei\\workplace\\Swc\\res\\22_24_12.tif', 'r')
used_image = tiff3d_obj.read_image()
im = np.require(used_image, dtype=np.uint8)
im_strs = im.tostring()
im_importer = vtk.vtkImageImport()
im_importer.CopyImportVoidPointer(im_strs, len(im_strs))
im_importer.SetDataScalarTypeToUnsignedChar()
im_importer.SetNumberOfScalarComponents(1)
im_importer.SetDataExtent(0, w - 1, 0, h - 1, 0, t - 1)
im_importer.SetWholeExtent(0, w - 1, 0, h - 1, 0, t - 1)

im_view = vtk.vtkImageViewer2()
im_view.SetInput(im_importer.GetOutput())
style1 = MyStyle()
iren = vtk.vtkRenderWindowInteractor()

im_view.SetupInteractor(iren)
im_view.SetColorLevel(50)
im_view.SetColorWindow(100)
im_view.GetRenderWindow().SetSize(600, 600)
im_view.SetSlice(100)
im_view.SetSliceOrientationToXY()
im_view.Render()
iren.SetInteractorStyle(style1)
iren.Initialize()
iren.Start()
