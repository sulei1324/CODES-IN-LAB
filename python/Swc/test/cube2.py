# -*- coding: utf-8 -*-


import vtk



cube_data = vtk.vtkPolyData()
cube_points = vtk.vtkPoints()
cube_cells = vtk.vtkCellArray()

cube_points.InsertPoint(0, (0.0, 0.0, 0.0))
cube_points.InsertPoint(1, (0.0, 5.0, 0.0))
cube_points.InsertPoint(2, (0.0, 5.0, 5.0))
cube_points.InsertPoint(3, (0.0, 0.0, 5.0))
cube_points.InsertPoint(4, (5.0, 0.0, 0.0))
cube_points.InsertPoint(5, (5.0, 5.0, 0.0))
cube_points.InsertPoint(6, (5.0, 0.0, 5.0))
cube_points.InsertPoint(7, (5.0, 5.0, 5.0))
cube_cells.InsertNextCell(5)
cube_cells.InsertCellPoint(0)
cube_cells.InsertCellPoint(1)
cube_cells.InsertCellPoint(2)
cube_cells.InsertCellPoint(3)
cube_cells.InsertCellPoint(0)
cube_cells.InsertNextCell(5)
cube_cells.InsertCellPoint(0)
cube_cells.InsertCellPoint(4)
cube_cells.InsertCellPoint(5)
cube_cells.InsertCellPoint(1)
cube_cells.InsertCellPoint(0)
cube_cells.InsertNextCell(5)
cube_cells.InsertCellPoint(4)
cube_cells.InsertCellPoint(5)
cube_cells.InsertCellPoint(7)
cube_cells.InsertCellPoint(6)
cube_cells.InsertCellPoint(4)
cube_cells.InsertNextCell(5)
cube_cells.InsertCellPoint(2)
cube_cells.InsertCellPoint(3)
cube_cells.InsertCellPoint(6)
cube_cells.InsertCellPoint(7)
cube_cells.InsertCellPoint(2)
cube_data.SetPoints(cube_points)
cube_data.SetLines(cube_cells)









cube_mapper = vtk.vtkPolyDataMapper()
cube_mapper.SetInput(cube_data)

cube_actor = vtk.vtkActor()
cube_actor.SetMapper(cube_mapper)

ren = vtk.vtkRenderer()
ren.AddActor(cube_actor)

renWin = vtk.vtkRenderWindow()
renWin.AddRenderer(ren)

iren = vtk.vtkRenderWindowInteractor()
iren.SetRenderWindow(renWin)
renWin.Render()
iren.Initialize()
iren.Start()

