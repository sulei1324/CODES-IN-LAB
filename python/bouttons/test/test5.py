import vtk

c = vtk.vtkCollection()
i = vtk.vtkCollectionIterator()
a1 = vtk.vtkActor()
a2 = vtk.vtkActor()
c.AddItem(a1)
c.AddItem(a2)
c.InitTraversal()
ai = c.GetNextItemAsObject()



matrix1 = vtk.vtkMatrix4x4()
print matrix1

s = vtk.vtkAssemblyPath()
s.AddNode(a1, matrix1)
s.AddNode(a2, matrix1)
s.InitTraversal()
ai = s.GetNextNode()
while ai:
    ai = s.GetNextNode()
    
