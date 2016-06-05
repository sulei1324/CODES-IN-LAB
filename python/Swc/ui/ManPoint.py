import vtk
import numpy as np

class MyStyle(vtk.vtkInteractorStyleTrackballCamera):
    def __init__(self):
        self.AddObserver("LeftButtonPressEvent", self.MyLeftButtonDown)
        self.AddObserver("CharEvent", self.MyKeyDown)
    
    def MyKeyDown(self, obj, e):
        global Choose_Mode, Delete_Mode
        if self.GetInteractor().GetKeySym() == "1":
            Choose_Mode = True
            print "Enter Choose Mode!"
        elif self.GetInteractor().GetKeySym() == "2":
            Choose_Mode = False
            print "Exit Choose Mode!"
        elif self.GetInteractor().GetKeySym() == "3":
            Delete_Mode = True
            print "Enter Delete Mode!"
        elif self.GetInteractor().GetKeySym() == "4":
            Delete_Mode = False
            print "Exit Delete Mode!"  
    
    def MyLeftButtonDown(self, obj, e):
        global Choose_Mode, Delete_Mode, actors, actors_choosed_flags, ren
        click_pos = self.GetInteractor().GetEventPosition()
        click_x = click_pos[0]
        click_y = click_pos[1]
        if Choose_Mode == True:
            picker = vtk.vtkPropPicker()
            picker.Pick(click_x, click_y, 0, self.GetDefaultRenderer())
            picked_actor = picker.GetActor()
            if picked_actor is not None:
                try:
                    choosed_index = actors.index(picked_actor)
                    if actors_choosed_flags[choosed_index] == 0:
                        actors_choosed_flags[choosed_index] = 1
                        picked_actor.GetProperty().SetColor(0.0, 255.0, 0.0)
                        picked_actor.Modified()
                    elif actors_choosed_flags[choosed_index] == 1:
                        actors_choosed_flags[choosed_index] = 0
                        picked_actor.GetProperty().SetColor(255.0, 0.0, 0.0)
                        picked_actor.Modified()                       
                except:
                    print "Choose No Point"            
        elif Delete_Mode == True:
            picker = vtk.vtkPropPicker()
            picker.Pick(click_x, click_y, 0, self.GetDefaultRenderer())
            picked_actor = picker.GetActor()
            if picked_actor is not None:
                try:
                    choosed_index = actors.index(picked_actor)
                    ren.RemoveActor(picked_actor)
                    actors.pop(choosed_index)
                    actors_choosed_flags.pop(choosed_index)
#                    ren.Modified()                 
                except:
                    print "Choose No Point"             
        self.OnLeftButtonDown()


Choose_Mode = False
Delete_Mode = False


num = 18
points = np.random.randn(num, 3)
sources = []
mappers = []
actors = []
actors_choosed_flags = [0] * num
ren = vtk.vtkRenderer()
renWin = vtk.vtkRenderWindow()
iren = vtk.vtkRenderWindowInteractor()
for i in xrange(num):
    sources.append(vtk.vtkSphereSource())
    mappers.append(vtk.vtkPolyDataMapper())
    actors.append(vtk.vtkActor())
    sources[i].SetCenter(points[i, 0], points[i, 1], points[i, 2])
    sources[i].SetRadius(0.2)
    sources[i].SetThetaResolution(20)
    sources[i].SetPhiResolution(20)
    mappers[i].SetInput(sources[i].GetOutput())
    actors[i].SetMapper(mappers[i])
    actors[i].GetProperty().SetColor(255.0, 0.0, 0.0)
    ren.AddActor(actors[i])

style1 = MyStyle()
style1.SetDefaultRenderer(ren)
renWin.AddRenderer(ren)
renWin.SetSize(500, 500)
iren.SetRenderWindow(renWin)
iren.SetInteractorStyle(style1)
renWin.Render()
iren.Initialize()
iren.Start()


    
    

