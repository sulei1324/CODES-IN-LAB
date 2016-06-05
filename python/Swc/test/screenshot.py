# -*- coding: utf-8 -*-

import vtk

ren = vtk.vtkRenderer()
renWin = vtk.vtkRenderWindow()
renWin.AddRenderer(ren)
renWin.SetSize(600, 600)


iren = vtk.vtkRenderWindowInteractor()
iren.SetRenderWindow(renWin)
style = vtk.vtkInteractorStyleTrackballCamera()
iren.SetInteractorStyle(style)

camera = vtk.vtkCamera()
camera.SetPosition(0, 0, -30)
camera.SetFocalPoint(0, 0, 10)
ren.SetActiveCamera(camera)

coordinate = vtk.vtkCoordinate()
coordinate.SetCoordinateSystemToWorld()
coordinate.SetValue(5, 0, 0)
print coordinate.GetComputedDisplayValue(ren)




source = vtk.vtkSphereSource()
source.SetCenter(0, 0, 0)
source.SetRadius(5.0)

mapper = vtk.vtkPolyDataMapper()
mapper.SetInput(source.GetOutput())

actor = vtk.vtkActor()
actor.SetMapper(mapper)

actor.GetProperty().SetColor(1, 0, 0)

ren.AddActor(actor)
renWin.Render()


#w2if = vtk.vtkWindowToImageFilter()
#w2if.SetInput(renWin)
#w2if.Update()
#
#writer =vtk.vtkPNGWriter()
#writer.SetFileName('1.png')
#writer.SetInput(w2if.GetOutput())
#writer.Write()
#
iren.Initialize()
iren.Start()

