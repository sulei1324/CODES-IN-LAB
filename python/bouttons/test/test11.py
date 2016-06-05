import vtk


class MyActor(vtk.vtkActor):
    def __init__(self):
        self.FieldData = vtk.vtkFieldData()
        
        
def GetActor():
    data1 = vtk.vtkFieldData()
    array1 = vtk.vtkIntArray()
    array1.SetNumberOfComponents(1)
    array1.InsertNextValue(1)
    data1.AddArray(array1)
    sphere = vtk.vtkSphereSource()
    mapper = vtk.vtkPolyDataMapper()
    actor = vtk.vtkActor()
    mapper.SetInput(sphere.GetOutput())
    sphere.GetOutput().SetFieldData(data1)
    actor.SetMapper(mapper)
    return actor

class A():
    def __init__(self):
        print 'sss'
    
    def getActor(self):
        data1 = vtk.vtkFieldData()
        array1 = vtk.vtkIntArray()
        array1.SetNumberOfComponents(1)
        array1.InsertNextValue(1)
        array2 = vtk.vtkIntArray()
        array2.SetNumberOfComponents(1)
        array2.InsertNextValue(44)
        data1.AddArray(array1)
        data1.AddArray(array2)
        sphere = vtk.vtkSphereSource()
        mapper = vtk.vtkPolyDataMapper()
        actor = vtk.vtkActor()
        mapper.SetInput(sphere.GetOutput())
        sphere.GetOutput().SetFieldData(data1)
        actor.SetMapper(mapper)
        return actor



if __name__ == '__main__':
    data1 = vtk.vtkFieldData()
    array1 = vtk.vtkIntArray()
    array1.SetNumberOfComponents(1)
    array1.InsertNextValue(1)
    array2 = vtk.vtkIntArray()
    array2.SetNumberOfComponents(1)
    array2.InsertNextValue(44)
    data1.AddArray(array1)
    data1.AddArray(array2)
    sphere = vtk.vtkSphereSource()
    mapper = vtk.vtkPolyDataMapper()
    actor = MyActor()
    mapper.SetInput(sphere.GetOutput())
    mapper.SetScalarModeToUseCellData()
    actor.SetMapper(mapper)
    actor.FieldData = data1
    ren = vtk.vtkRenderer()
    iren = vtk.vtkRenderWindowInteractor()
    renWin = vtk.vtkRenderWindow()
    renWin.AddRenderer(ren)
    iren.SetRenderWindow(renWin)
    b = actor
    ren.AddActor(b)
    print actor.FieldData
    renWin.Render()
    print actor.FieldData
    iren.Initialize()
    iren.Start()
    