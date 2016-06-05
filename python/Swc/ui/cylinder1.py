import vtk
import math

class MyStyle(vtk.vtkInteractorStyleTrackballCamera):
    def __init__(self, parent=None):
        self.AddObserver("LeftButtonPressEvent", self.pickLine)
     
    def pickLine(self, obj, e):
        global cy1, ren, iren, actor1
        clickPos = self.GetInteractor().GetEventPosition()
        print clickPos
        picker = vtk.vtkCellPicker()
        picker.Pick(clickPos[0], clickPos[1], 0, self.GetDefaultRenderer())
        print picker.GetCellId()
        picker2 = vtk.vtkPropPicker()
        picker2.Pick(clickPos[0], clickPos[1], 0, self.GetDefaultRenderer())
        print picker2.GetActor() == actor1
        self.OnLeftButtonDown()


point1 = [4, 4, 4]
point2 = [2, 2, 2]
cy1 = vtk.vtkCylinderSource()
cy1.SetCenter(3, 3, 3)
cy1.SetHeight(2)
# cy1.SetCenter((point1[0] - point2[0]) / 2 + point2[0], (point1[1] - point2[1]) / 2 + point2[1], (point1[2] - point2[2]) / 2 + point2[2])
# cy1.SetHeight(math.sqrt((point1[0] - point2[0])^2 + (point1[0] - point2[0])^2 + (point1[0] - point2[0])^2))
cy1.SetRadius(0.1)

sp1 = vtk.vtkSphereSource()
sp1.SetCenter(4, 4, 4)
sp1.SetRadius(0.2)
sp2 = vtk.vtkSphereSource()
sp2.SetCenter(2, 2, 2)
sp2.SetRadius(0.2)


mapper1 = vtk.vtkPolyDataMapper()
mapper1.SetInput(cy1.GetOutput())
actor1 = vtk.vtkActor()
actor1.SetMapper(mapper1)
# actor1.GetProperty().SetLineWidth(10)
mapper2 = vtk.vtkPolyDataMapper()
mapper2.SetInput(sp1.GetOutput())
actor2 = vtk.vtkActor()
actor2.SetMapper(mapper2)
mapper3 = vtk.vtkPolyDataMapper()
mapper3.SetInput(sp2.GetOutput())
actor3 = vtk.vtkActor()
actor3.SetMapper(mapper3)

ren = vtk.vtkRenderer()
ren.AddActor(actor1)
ren.AddActor(actor2)
ren.AddActor(actor3)
win1 = vtk.vtkRenderWindow()
win1.AddRenderer(ren)
iren = vtk.vtkRenderWindowInteractor()
iren.SetRenderWindow(win1)
style1 = MyStyle()
style1.SetDefaultRenderer(ren)
iren.SetInteractorStyle(style1)
win1.Render()
iren.Initialize()
iren.Start()
