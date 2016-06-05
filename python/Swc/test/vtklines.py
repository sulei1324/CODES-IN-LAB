# -*- coding: utf-8 -*-
import vtk
import readMostd as rmd
import readSwc as rs


swc = rs.Swc("dendrite.swc", (0.3, 0.3, 1))


lines = swc.lines
lines_actors = []

for i in xrange(len(lines)):   
    this_line = lines[i].data
    this_line_poly_data = vtk.vtkPolyData()
    this_line_points = vtk.vtkPoints()
    for i in xrange(len(this_line)):
        this_line_points.InsertPoint(i, this_line[i][2:5])
    this_line_cells = vtk.vtkCellArray()
    this_line_cells.InsertNextCell(len(this_line))
    for i in xrange(len(this_line)):
        this_line_cells.InsertCellPoint(i)
    
    this_line_poly_data.SetPoints(this_line_points)
    this_line_poly_data.SetLines(this_line_cells)
    this_line_mapper = vtk.vtkPolyDataMapper()
    this_line_mapper.SetInput(this_line_poly_data)
    this_line_actor = vtk.vtkActor()
    this_line_actor.SetMapper(this_line_mapper)
    this_line_actor.GetProperty().SetLineWidth(1)
    lines_actors.append(this_line_actor)

ren = vtk.vtkRenderer()
for i in lines_actors:
    ren.AddActor(i)
ren.SetBackground(0.1, 0.2, 0.3)

renWin = vtk.vtkRenderWindow()
renWin.AddRenderer(ren)

iren = vtk.vtkRenderWindowInteractor()
iren.SetRenderWindow(renWin)
renWin.Render()
iren.Start()
