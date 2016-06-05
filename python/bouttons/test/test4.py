import os, sys, threading
import vtk

def fun1(obj, e):
    global widget1
    print 'sss'
    print widget1.GetBorderRepresentation().GetPosition()
    


renWin = vtk.vtkRenderWindow()
ren = vtk.vtkRenderer()
iren = vtk.vtkRenderWindowInteractor()
renWin.AddRenderer(ren)
iren.SetRenderWindow(renWin)
widget1 = vtk.vtkBorderWidget()
widget1.SetInteractor(iren)
widget1.CreateDefaultRepresentation()
widget1.GetBorderRepresentation().MovingOn()
widget1.On()
widget1.AddObserver('EndInteractionEvent', fun1)
iren.Initialize()
iren.Start()