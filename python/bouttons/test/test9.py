import vtk

assembly1 = vtk.vtkAssembly()
mappers = []
sources = []


def fun1(*args):
    global assembly1, ren
    print ren.GetNumberOfPropsRendered()
    ren.RemoveAllViewProps()
    ren.Modified()
    ren.Render()
    print ren.GetNumberOfPropsRendered()

for i in xrange(6):
    x = vtk.vtkMath.Random(-5, 5)
    y = vtk.vtkMath.Random(-5, 5)
    z = vtk.vtkMath.Random(-5, 5)
    source_i = vtk.vtkConeSource()
    source_i.SetCenter(x, y, z)
    sources.append(source_i)
    mapper_i = vtk.vtkPolyDataMapper()
    mapper_i.SetInput(source_i.GetOutput())
    actor_i = vtk.vtkActor()
    actor_i.SetMapper(mapper_i)
    c_r = (vtk.vtkMath.Random(0, 1))
    c_g = (vtk.vtkMath.Random(0, 1))
    c_b = (vtk.vtkMath.Random(0, 1))
    print c_r, c_g, c_b
    actor_i.GetProperty().SetColor(c_r, c_g, c_b)
    mappers.append(mapper_i)
    assembly1.AddPart(actor_i)

ren = vtk.vtkRenderer()
renWin = vtk.vtkRenderWindow()
renWin.AddRenderer(ren)
iren = vtk.vtkRenderWindowInteractor()
iren.SetRenderWindow(renWin)
ren.AddActor(assembly1)
iren.AddObserver('LeftButtonPressEvent', fun1)
iren.Initialize()
iren.Start()