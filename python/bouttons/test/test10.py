import vtk

a = vtk.vtkDoubleArray()
a.SetNumberOfComponents(3)
a.InsertNextTupleValue((3.0, 4.0, 5.0))
a.InsertNextTupleValue((1.1, 2.2, 3.3))
b = [0.0] * 3
a.GetTupleValue(0, b)
a.SetName('rrr')

c = vtk.vtkFieldData()
c.AddArray(a)
print c.GetArray(0)

