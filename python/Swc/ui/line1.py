import vtk

class MyStyle(vtk.vtkInteractorStyleTrackballCamera):
    def __init__(self, parent=None):
        self.AddObserver("LeftButtonPressEvent", self.pickLine)
     
    def pickLine(self, obj, e):
        global line1, ren, iren, actor1
        clickPos = self.GetInteractor().GetEventPosition()
        print clickPos
 #       print obj == self
        picker = vtk.vtkCellPicker()
        print picker.GetTolerance()
        picker.SetTolerance(1 / 80.0)
        picker.Pick(clickPos[0], clickPos[1], 0, self.GetDefaultRenderer())
        print picker.GetCellId()
        picker2 = vtk.vtkPropPicker()
        picker2.Pick(clickPos[0], clickPos[1], 0, self.GetDefaultRenderer())

line1 = vtk.vtkLineSource()
points = vtk.vtkPoints()
points.InsertPoint(0, 1, 1, 1)
points.InsertPoint(1, 2, 2, 2)
line1.SetPoints(points)

mapper = vtk.vtkPolyDataMapper()
mapper.SetInput(line1.GetOutput())
actor1 = vtk.vtkActor()
actor1.SetMapper(mapper)
actor1.GetProperty().SetLineWidth(2.0)

ren = vtk.vtkRenderer()
ren.AddActor(actor1)
win1 = vtk.vtkRenderWindow()
win1.AddRenderer(ren)
win1.SetSize(500, 500)
iren = vtk.vtkRenderWindowInteractor()
iren.SetRenderWindow(win1)
style1 = MyStyle()
style1.SetDefaultRenderer(ren)
iren.SetInteractorStyle(style1)
win1.Render()
iren.Initialize()
iren.Start()

