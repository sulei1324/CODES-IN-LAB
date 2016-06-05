import vtk

points = vtk.vtkPointSource()
points.SetCenter(0.0, 0.0, 0.0)
points.SetNumberOfPoints(500)
points.SetRadius(50.0)

m = vtk.vtkPolyDataMapper()
m.SetInput(points.GetOutput())

a = vtk.vtkActor()
a.SetMapper(m)
r = vtk.vtkRenderer()
r.AddActor(a)
w = vtk.vtkRenderWindow()
w.AddRenderer(r)
i = vtk.vtkRenderWindowInteractor()
i.SetRenderWindow(w)

i.Initialize()
i.Start()