import vtk

s1 = vtk.vtkSphereSource()
m1 = vtk.vtkPolyDataMapper()
a1 = vtk.vtkActor()
a1.SetMapper(m1)
m1.SetInput(s1.GetOutput())

s2 = vtk.vtkConeSource()
m2 = vtk.vtkPolyDataMapper()
a2 = vtk.vtkActor()
a2.SetMapper(m2)
m2.SetInput(s2.GetOutput())

as1 = vtk.vtkAssembly()
as1.AddPart(a1)
as1.AddPart(a2)

t1 = vtk.vtkTransform()
t1.PostMultiply()
t1.Translate(5.0, 0.0, 0.0)

pc1 = vtk.vtkPropCollection()
as1.GetActors(pc1)
pc1.InitTraversal()
for i in xrange(pc1.GetNumberOfItems()):
    pc1.GetNextProp().GetProperty().SetColor(255.0, 0.0, 0.0)

ren = vtk.vtkRenderer()
renWin = vtk.vtkRenderWindow()
iren = vtk.vtkRenderWindowInteractor()
ren.AddActor(as1)
renWin.AddRenderer(ren)
iren.SetRenderWindow(renWin)

iren.Initialize()
iren.Start()