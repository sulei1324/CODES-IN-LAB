import vtk

class my_style(vtk.vtkInteractorStyleJoystickActor):
    def __init__(self, parent=None):
        print "hhhhh"


sphere1 = vtk.vtkSphereSource()
sphere1.SetCenter(4, 3, 4)
sphere1.SetRadius(2)
sphere1.SetPhiResolution(8)

arrow1 = vtk.vtkArrowSource()
arrow1.SetTipLength(4)
arrow1.SetShaftRadius(0.3)
arrow1.SetShaftResolution(1)

sphere_mapper = vtk.vtkPolyDataMapper()
arrow_mapper = vtk.vtkPolyDataMapper()

sphere_mapper.SetInputConnection(sphere1.GetOutputPort())
arrow_mapper.SetInputConnection(arrow1.GetOutputPort())

sphere_actor = vtk.vtkActor()
arrow_actor = vtk.vtkActor()

sphere_actor.SetMapper(sphere_mapper)
arrow_actor.SetMapper(arrow_mapper)

property1 = vtk.vtkProperty()
property1.SetColor(255, 0, 255)
sphere_actor.SetProperty(property1)


render1 = vtk.vtkRenderer()
render1.AddActor(sphere_actor)
render1.AddActor(arrow_actor)

ren_win = vtk.vtkRenderWindow()
ren_win.AddRenderer(render1)
ren_win.SetSize(200, 200)

ren_style = my_style()

iren = vtk.vtkRenderWindowInteractor()
iren.SetRenderWindow(ren_win)
iren.SetInteractorStyle(ren_style)
ren_win.Render()

iren.Start()