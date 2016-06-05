import vtk

s1 = vtk.vtkConeSource()
m1= vtk.vtkPolyDataMapper()
m1.SetInputConnection(s1.GetOutputPort())



a1 = vtk.vtkActor()
a2 = vtk.vtkActor()
a1.SetMapper(m1)
a2.SetMapper(m1)
r = vtk.vtkRenderer()
r.AddActor(a1)
r.AddActor(a2)
rw = vtk.vtkRenderWindow()
rw.AddRenderer(r)
ir = vtk.vtkRenderWindowInteractor()
ir.SetRenderWindow(rw)
r.Render()
print r.GetNumberOfPropsRendered()

r.RemoveActor(a2)
r.Render()
print r.GetNumberOfPropsRendered()

ir.Initialize()
ir.Start()
