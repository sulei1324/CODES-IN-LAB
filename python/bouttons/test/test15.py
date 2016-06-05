import random
import vtk

a = []
for i in xrange(5):
    b = []
    print id(b)
    for j in xrange(3):
        b.append(random.randint(1, 100))
    a.append(b)
    print id(a[i])

print a

r = vtk.vtkRenderer()
print r.GetNumberOfPropsRendered()