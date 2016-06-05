# -*- coding: utf-8 -*-

import vtk

x = [[0, 0, 0], [1, 0, 0], [1, 1, 0], [0, 1, 0], [0, 0, 1], [1, 0, 1], [1, 1, 1], [0, 1, 1]]
pts = [[0, 1, 2, 3], [4, 5, 6, 7], [0, 1, 5, 4], [1, 2, 6, 5], [2, 3, 7, 6], [3, 0, 4, 7]]

cube = vtk.vtkPolyData()
points = vtk.vtkPoints()
polys = vtk.vtkCellArray()
scalars = vtk.vtkFloatArray()

for i in xrange(8):
    print i
    points.InsertPoint(i, x[i])

for i in xrange(6):
    polys.InsertNextCell(len(pts[i]))
    for j in xrange(len(pts[i])):
        polys.InsertCellPoint(pts[i][j])

for i in xrange(8):
    scalars.InsertTuple1(i, i)

cube.SetPoints(points)
cube.SetPolys(polys)
cube.GetPointData().SetScalars(scalars)                  

cubeMapper = vtk.vtkPolyDataMapper()
cubeMapper.SetInput(cube)
cubeMapper.SetScalarRange(0, 7)

cubeActor = vtk.vtkActor()
cubeActor.SetMapper(cubeMapper)

camera = vtk.vtkCamera()
camera.SetPosition(1, 1, 1)
camera.SetFocalPoint(0, 0, 0)

ren = vtk.vtkRenderer()
renWin = vtk.vtkRenderWindow()
renWin.AddRenderer(ren)

iren = vtk.vtkRenderWindowInteractor()
iren.SetRenderWindow(renWin)

ren.AddActor(cubeActor)
ren.SetActiveCamera(camera)
ren.ResetCamera()
ren.SetBackground(1, 1, 1)

renWin.SetSize(300, 300)
renWin.Render()
iren.Start()
