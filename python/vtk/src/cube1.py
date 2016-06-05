import vtk

class MyStyle(vtk.vtkInteractorStyleTrackballCamera):
    def __init__(self, parent=None):
        self.AddObserver("LeftButtonPressEvent", self.pickLine)
     
    def pickLine(self, obj, e):
        global cube1, ren, iren, cubeActor
        clickPos = self.GetInteractor().GetEventPosition()
        print clickPos
 #       print obj == self
        picker = vtk.vtkCellPicker()
        picker.Pick(clickPos[0], clickPos[1], 0, self.GetDefaultRenderer())
        print picker.GetCellId()
        picker2 = vtk.vtkPropPicker()
        picker2.Pick(clickPos[0], clickPos[1], 0, self.GetDefaultRenderer())
        print picker2.GetActor() == cubeActor


p_array = [
           [0, 0, 0],
           [1, 0, 0],
           [1, 1, 0],
           [0, 1, 0],
           [0, 0, 1],
           [1, 0, 1],
           [1, 1, 1],
           [0, 1, 1]
           ]

pts = [
       [0, 1, 2, 3],
       [4, 5, 6, 7],
       [0, 1, 5, 4],
       [1, 2, 6, 5],
       [2, 3, 7, 6],
       [3, 0, 4, 7]
       ]

cube1 = vtk.vtkPolyData()
points = vtk.vtkPoints()
polys = vtk.vtkCellArray()
scalars = vtk.vtkFloatArray()

for i in xrange(len(p_array)):
    points.InsertPoint(i, p_array[i])

for i in xrange(len(pts)):
    polys.InsertNextCell(4, pts[i])

for i in xrange(len(p_array)):
    scalars.InsertTuple1(i, i)

cube1.SetPoints(points)
cube1.SetPolys(polys)
cube1.GetPointData().SetScalars(scalars)

cubeMapper = vtk.vtkPolyDataMapper()
cubeMapper.SetInputData(cube1)
cubeMapper.SetScalarRange(0, 7)

cubeActor = vtk.vtkActor()
cubeActor.SetMapper(cubeMapper)

camera = vtk.vtkCamera()
camera.SetPosition(10, 10, 10)
camera.SetFocalPoint(0, 0, 0)


ren = vtk.vtkRenderer()
ren.AddActor(cubeActor)
ren.SetActiveCamera(camera)
ren.SetBackground(0.1, 0.2, 0.3)

renWin = vtk.vtkRenderWindow()
renWin.AddRenderer(ren)
renWin.SetSize(300, 300)

iren = vtk.vtkRenderWindowInteractor()
iren.SetRenderWindow(renWin)
style1 = MyStyle()
style1.SetDefaultRenderer(ren)
iren.SetInteractorStyle(style1)
renWin.Render()
iren.Start()


