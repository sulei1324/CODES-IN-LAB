import vtk

i = vtk.vtkImageData()
i.SetOrigin(0, 0, 0)
i.SetSpacing(1, 1, 1)
N = 3
ext = [0, N, 0, N, 0, N]
i.SetExtent(ext)
i.SetScalarTypeToInt()
i.SetNumberOfScalarComponents(1)
i.AllocateScalars()

for i in xrange(N):
    for j in xrange(N):
        for k in xrange(N):
            pos = [i, j, k]
            id = vtk.vtkStructuredData.ComputeCellIdForExtent(ext, pos)
            print id
            

