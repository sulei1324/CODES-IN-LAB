#coding:utf-8
import treelib
import os
import re
import vtk

class SwcBranch(treelib.Node):
    def __init__(self, data1=None, tag=None, depth=0):
        super(SwcBranch, self).__init__(tag)
        self.__data = data1
        self.__depth = depth
    
    def getLine(self):
        return self.__data
    
    def getDepth(self):
        return self.__depth

class SwcTree(treelib.Tree):
    def __init__(self, swcpath=None):
        assert self.__checkSwcPath(swcpath), "Incorrect Swc Path!!"
        super(SwcTree, self).__init__()
        self.__src = swcpath
        self.__lists = self.__swc2lists()
        self.__lines = self.__swc2lines()
        self.__swc2tree()
        self.__ren = None
        self.__renWin = None
        self.__iren = None
    
    def getQtVtkRenderer(self):
        self.__ren = vtk.vtkRenderer()
        self.__ren.SetBackground(0.2, 0.2, 0.2)
        for tmpBranchId in self.expand_tree(self.root, mode=self.DEPTH):
            self.__showBranch(self.get_node(tmpBranchId), mode=4)        
        return self.__ren
    
    def renderInVtk(self, ren):
        self.__ren = ren
        for tmpBranchId in self.expand_tree(self.root, mode=self.DEPTH):
            self.__showBranch(self.get_node(tmpBranchId), mode=1)        
        return self.__ren        
    
    def vtkShow(self):
        self.__ren = vtk.vtkRenderer()
        self.__renWin = vtk.vtkRenderWindow()
        self.__iren = vtk.vtkRenderWindowInteractor()
        self.__ren.SetBackground(0.2, 0.2, 0.2)
        self.__renWin.AddRenderer(self.__ren)
        self.__renWin.SetSize(600, 600)
        self.__iren.SetRenderWindow(self.__renWin)
        for tmpBranchId in self.expand_tree(self.root, mode=self.DEPTH):
            self.__showBranch(self.get_node(tmpBranchId), mode=5)
        self.__renWin.Render()
        self.__iren.Initialize()
        self.__iren.Start()
            
    
    def __showBranch(self, branch_arg, mode=1):
        assert self.__ren != None, "vtkRenderer is not Ready!"
        line_data = branch_arg.getLine()
        if mode == 1:
            for i in xrange(len(line_data)):
                tmp_point = line_data[i]
                tmp_sphere = vtk.vtkSphereSource()
                tmp_sphere.SetCenter(tmp_point[2], tmp_point[3], tmp_point[4])
                tmp_sphere.SetRadius(1.0)
                tmp_mapper = vtk.vtkPolyDataMapper()
                tmp_mapper.SetInput(tmp_sphere.GetOutput())
                tmp_actor = vtk.vtkActor()
                tmp_actor.SetMapper(tmp_mapper)
                self.__ren.AddActor(tmp_actor)
        elif mode == 2:
            tmp_points = vtk.vtkPoints()
            tmp_line_cell = vtk.vtkCellArray()
            for i in xrange(len(line_data)):
                tmp_point = line_data[i]
                tmp_points.InsertNextPoint((tmp_point[2], tmp_point[3], tmp_point[4]))
            tmp_line_cell.InsertNextCell(len(line_data))
            for i in xrange(len(line_data)):
                tmp_line_cell.InsertCellPoint(i)
            tmp_line = vtk.vtkPolyData()
            tmp_line.SetPoints(tmp_points)
            tmp_line.SetLines(tmp_line_cell)
            tmp_mapper = vtk.vtkPolyDataMapper()
            tmp_mapper.SetInput(tmp_line)
            tmp_actor = vtk.vtkActor()
            tmp_property = vtk.vtkProperty()
            tmp_property.SetLineWidth(2.0)
            tmp_property.SetColor(0.0, 1.0, 0.0)
            tmp_actor.SetMapper(tmp_mapper)
            tmp_actor.SetProperty(tmp_property)
            self.__ren.AddActor(tmp_actor)
        elif mode == 3:
            tmp_points = vtk.vtkPoints()
            tmp_line_cell = vtk.vtkCellArray()
            for i in xrange(len(line_data)):
                tmp_point = line_data[i]
                tmp_points.InsertNextPoint((tmp_point[2], tmp_point[3], tmp_point[4]))
            tmp_line_cell.InsertNextCell(len(line_data))
            for i in xrange(len(line_data)):
                tmp_line_cell.InsertCellPoint(i)
            tmp_line = vtk.vtkPolyData()
            tmp_line.SetPoints(tmp_points)
            tmp_line.SetLines(tmp_line_cell)
            tmp_mapper1 = vtk.vtkPolyDataMapper()
            tmp_mapper1.SetInput(tmp_line)
            tmp_actor1 = vtk.vtkActor()
            tmp_property1 = vtk.vtkProperty()
            tmp_property1.SetLineWidth(3.0)
            tmp_property1.SetColor(1.0, 0.0, 0.0)
            tmp_actor1.SetMapper(tmp_mapper1)
            tmp_vertices = vtk.vtkPolyData()
            tmp_vertices.SetPoints(tmp_points)
            tmp_vertices.SetVerts(tmp_line_cell)
            tmp_mapper2 = vtk.vtkPolyDataMapper()
            tmp_mapper2.SetInput(tmp_vertices)
            tmp_actor2 = vtk.vtkActor()
            tmp_property2 = vtk.vtkProperty()
            tmp_property2.SetPointSize(1.0)
            tmp_property2.SetColor(0.0, 1.0, 0.0)
            tmp_actor2.SetMapper(tmp_mapper2)
            tmp_actor1.SetProperty(tmp_property1)
            tmp_actor2.SetProperty(tmp_property2)          
            self.__ren.AddActor(tmp_actor1)  
            self.__ren.AddActor(tmp_actor2)
        elif mode == 4:
            tmp_points = vtk.vtkPoints()
            tmp_line_cell = vtk.vtkCellArray()
            for i in xrange(len(line_data)):
                tmp_point = line_data[i]
                tmp_points.InsertNextPoint((tmp_point[2], tmp_point[3], tmp_point[4]))
            tmp_line_cell.InsertNextCell(len(line_data))
            for i in xrange(len(line_data)):
                tmp_line_cell.InsertCellPoint(i)
            tmp_line = vtk.vtkPolyData()
            tmp_line.SetPoints(tmp_points)
            tmp_line.SetLines(tmp_line_cell)
            tmp_spline_filter = vtk.vtkSplineFilter()
            tmp_spline_filter.SetInput(tmp_line)
            tmp_spline_filter.SetNumberOfSubdivisions(5*len(line_data))
            tmp_spline_filter.Update()                         
            tmp_tube_filter = vtk.vtkTubeFilter()
            tmp_tube_filter.SetInputConnection(tmp_spline_filter.GetOutputPort())
            tmp_tube_filter.SetRadius(1.0)
            tmp_tube_filter.SetNumberOfSides(20)
            tmp_tube_filter.CappingOn()
            tmp_mapper = vtk.vtkPolyDataMapper()
            tmp_mapper.SetInputConnection(tmp_tube_filter.GetOutputPort())
            tmp_actor = vtk.vtkActor()
            tmp_actor.GetProperty().SetColor(1.0, 0.0, 0.0)
            tmp_actor.SetMapper(tmp_mapper)
            self.__ren.AddActor(tmp_actor)
        elif mode == 5:
            tmp_points1 = vtk.vtkPoints()
            tmp_vertices_cell = vtk.vtkCellArray()
            for i in xrange(2):
                if i == 0:
                    tmp_point = line_data[0]
                else:
                    tmp_point = line_data[len(line_data) - 1]
                tmp_points1.InsertNextPoint((tmp_point[2], tmp_point[3], tmp_point[4]))
            tmp_vertices_cell.InsertNextCell(2)
            for i in xrange(2):
                tmp_vertices_cell.InsertCellPoint(i)
            tmp_points2 = vtk.vtkPoints()
            tmp_line_cell = vtk.vtkCellArray()
            for i in xrange(len(line_data)):
                tmp_point = line_data[i]
                tmp_points2.InsertNextPoint((tmp_point[2], tmp_point[3], tmp_point[4]))
            tmp_line_cell.InsertNextCell(len(line_data))
            for i in xrange(len(line_data)):
                tmp_line_cell.InsertCellPoint(i)                 
            tmp_line = vtk.vtkPolyData()
            tmp_line.SetPoints(tmp_points2)
            tmp_line.SetLines(tmp_line_cell)
            tmp_mapper1 = vtk.vtkPolyDataMapper()
            tmp_mapper1.SetInput(tmp_line)
            tmp_actor1 = vtk.vtkActor()
            tmp_property1 = vtk.vtkProperty()
            tmp_property1.SetLineWidth(3.0)
            tmp_property1.SetColor(1.0, 0.0, 0.0)
            tmp_actor1.SetMapper(tmp_mapper1)
            tmp_vertices = vtk.vtkPolyData()
            tmp_vertices.SetPoints(tmp_points1)
            tmp_vertices.SetVerts(tmp_vertices_cell)
            tmp_mapper2 = vtk.vtkPolyDataMapper()
            tmp_mapper2.SetInput(tmp_vertices)
            tmp_actor2 = vtk.vtkActor()
            tmp_property2 = vtk.vtkProperty()
            tmp_property2.SetPointSize(5.0)
            tmp_property2.SetColor(0.0, 1.0, 0.0)
            tmp_actor2.SetMapper(tmp_mapper2)
            tmp_actor1.SetProperty(tmp_property1)
            tmp_actor2.SetProperty(tmp_property2)          
            self.__ren.AddActor(tmp_actor1)  
            self.__ren.AddActor(tmp_actor2)
    
    def __checkSwcPath(self, path1):
        if path1 is None or not os.path.isfile(path1):
            return False
        hasSwcPost = False
        m = re.match('.+\.[Ss][Ww][Cc]$', path1)
        if m is not None:
            hasSwcPost = True
        return hasSwcPost
    
    def __swc2tree(self):
        lines = self.__lines
        for i in xrange(len(lines)):
            tmpLine = lines[i]
            if i == 0:
                tmpBranch = SwcBranch(tmpLine, tag='0', depth=0)
                self.add_node(tmpBranch)
            else:
                fatherId, fatherDepth = self.__findFatherId(tmpLine)
                if fatherId != -1:
                    currentSonsNum = len(self.is_branch(fatherId))
                    tmpTag = '%s_%d_%d'%(self.get_node(fatherId).tag, fatherDepth + 1, currentSonsNum)
                    tmpBranch = SwcBranch(tmpLine, tag=tmpTag, depth=fatherDepth + 1)
                    self.add_node(tmpBranch, parent=fatherId)
    
    def __findFatherId(self, line1):
        start_serial = line1[0][0]
        for branchId in self.expand_tree(self.root, mode=self.DEPTH):
            branch = self.get_node(branchId)
            lineI = branch.getLine()
            lineI_serials = []
            for i in xrange(len(lineI)):
                lineI_serials.append(lineI[i][0])
            if start_serial in lineI_serials:
                return branchId, branch.getDepth()
        return -1, -1
    
    def getSwcList(self):
        return self.__lists
    
    def getLines(self):
        return self.__lines
    
    def __swc2lines(self):
        swc_list = self.__lists
        self.__clear_isolated_points(swc_list)
        line_list = []
        if len(swc_list) == 0:
            print "there is no node!"
            return None
        for i in xrange(len(swc_list)):
            if swc_list[i][6] == -1 and i == 0:
                tmp_line = []
                tmp_line.append(swc_list[i])
            elif swc_list[i][6] != swc_list[i][0] - 1:
                pre_node = swc_list[i][6]
                line_list.append(tmp_line)
                tmp_line = []
                tmp_line.append(swc_list[pre_node - 1])
                tmp_line.append(swc_list[i])
            else:
                tmp_line.append(swc_list[i])
            if i == len(swc_list) - 1:
                line_list.append(tmp_line)
        return line_list
    
    def __swc2lists(self):
        swc_file = open(self.__src)
        swc_list = []
        for line in swc_file:
            tmp_node = []
            str_list_node_info = line.strip().split(' ')
            assert len(str_list_node_info) == 7, "Swc File Has Incorrect Format!!!"
            for i in xrange(len(str_list_node_info)):
                if i in [0, 1, 6]:
                    tmp_node.append(int(str_list_node_info[i]))
                else:
                    tmp_node.append(float(str_list_node_info[i]))   
            swc_list.append(tmp_node)
        return swc_list

    def __clear_isolated_points(self, swc_list):
        for i in xrange(len(swc_list) - 1, -1, -1):
            if swc_list[i][6] == -1:
                swc_list.pop()
            else:
                break        


if __name__ == '__main__':
    s = SwcTree(r'dendrite.swc')
    s.vtkShow()
    

    