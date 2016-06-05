__author__ = 'Su Lei'

import vtk


class MouseInteractorsStyle2(vtk.vtkInteractorStyleTrackballCamera):
    def __init__(self, parent=None):
        print 'here'
        self.AddObserver('LeftButtonPressEvent', self.leftButtonDown)

    def leftButtonDown(self, *arg):
        print "dddddd"
        clickPos = self.GetInteractor().GetEventPosition()
        picker = vtk.vtkPropPicker()
        print self.GetDefaultRenderer()
        picker.Pick(clickPos[0], clickPos[1], 0, self.GetDefaultRenderer())
        pos = picker.GetPickPosition()
        self.OnLeftButtonDown()
        print pos

        sphereSource = vtk.vtkSphereSource()
        sphereSource.SetCenter(pos[0], pos[1], pos[2])
        sphereSource.SetRadius(0.1)
        sphereMapper = vtk.vtkPolyDataMapper()
        sphereMapper.SetInputConnection(sphereSource.GetOutputPort())
        sphereActor = vtk.vtkActor()
        sphereActor.SetMapper(sphereMapper)
        self.GetDefaultRenderer().AddActor(sphereActor)








planeSource = vtk.vtkPlaneSource()
planeSource.Update()
polydata = planeSource.GetOutput()
mapper = vtk.vtkPolyDataMapper()
mapper.SetInput(polydata)
actor = vtk.vtkActor()
actor.SetMapper(mapper)
ren = vtk.vtkRenderer()
ren.AddActor(actor)
renWin = vtk.vtkRenderWindow()
renWin.AddRenderer(ren)
iren = vtk.vtkRenderWindowInteractor()
iren.SetRenderWindow(renWin)
# iren.RemoveObservers('LeftButtonPressEvent')
style = MouseInteractorsStyle2()
style.SetDefaultRenderer(ren)
iren.SetInteractorStyle(style)

ren.SetBackground(0, 0, 1)
renWin.Render()
iren.Initialize()
iren.Start()
