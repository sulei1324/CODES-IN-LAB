import vtk

c = vtk.vtkActorCollection()

a1 = vtk.vtkActor()
a2 = vtk.vtkActor()
c.AddItem(a1)
c.AddItem(a2)
print c.GetNumberOfItems()
c.InitTraversal()
for i in xrange(2):
    print c.GetNextActor()
    
    

