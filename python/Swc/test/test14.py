import vtk




def pickActor(obj, e):
    global iren, ren, aspath
    picker1 = vtk.vtkPropPicker()
    x, y = iren.GetEventPosition()
    picker1.Pick(x, y, 0, ren)
    print picker1.GetActor()
    i1 = vtk.vtkCollectionIterator()
    aspath.InitTraversal(i1)
    for i in xrange(aspath.GetNumberOfItems()):
        actor_i = aspath.GetNextItemAsObject()
        print id(actor_i)
    print '____________________________'
    aspath.InitTraversal()
    for i in xrange(aspath.GetNumberOfItems()):
        actor_i = aspath.GetNextItemAsObject()
        print id(actor_i)



def creatActor():
    sphere1 = vtk.vtkSphereSource()
    x = vtk.vtkMath.Random(-5.0, 5.0)
    y = vtk.vtkMath.Random(-5.0, 5.0)
    z = vtk.vtkMath.Random(-5.0, 5.0)
    r = vtk.vtkMath.Random(1.0, 3.0)
    R = vtk.vtkMath.Random(0.0, 1.0)
    G = vtk.vtkMath.Random(0.0, 1.0)
    B = vtk.vtkMath.Random(0.0, 1.0)
    sphere1.SetCenter(x, y, z)
    sphere1.SetRadius(r)
    mapper1 = vtk.vtkPolyDataMapper()
    mapper1.SetInput(sphere1.GetOutput())
    actor1 = vtk.vtkActor()
    actor1.SetMapper(mapper1)
    actor1.GetProperty().SetColor(R, G, B)
    return actor1


if __name__ == '__main__':
    global iren, ren, aspath
    aspath = vtk.vtkAssemblyPath()
    ren = vtk.vtkRenderer()
    iren = vtk.vtkRenderWindowInteractor()
    renWin = vtk.vtkRenderWindow()
    iren.SetRenderWindow(renWin)
    renWin.AddRenderer(ren)
    assembly1 = vtk.vtkAssembly()
    matrix1 = vtk.vtkMatrix4x4()
    print matrix1
    for i in xrange(30):
        actor_i = creatActor()
        ren.AddActor(actor_i)
        aspath.AddNode(actor_i, matrix1)
    iren.AddObserver('LeftButtonPressEvent', pickActor)
    iren.Initialize()
    iren.Start()