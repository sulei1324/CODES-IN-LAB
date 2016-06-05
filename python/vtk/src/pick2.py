#coding: utf-8
import vtk

picker = vtk.vtkCellPicker()

def picking(object2, event):
    global renWin, cone, ren
    pos = object2.GetSelectionPoint()
    textMapper.SetInput("hello picker")
    textActor.SetPosition(pos[0], pos[1])
    textActor.VisibilityOn()
    print object2.GetCellId()
    cone_data = cone.GetOutput()
    poly1 = vtk.vtkPolyData()
    cell1 = vtk.vtkCellArray()
    cell1.InsertNextCell(3, [0, 1, 2])
    poly1.SetPoints(cone_data.GetCell(object2.GetCellId()).GetPoints())
    poly1.SetPolys(cell1)
    mapper1= vtk.vtkPolyDataMapper()
    mapper1.SetInputData(poly1)
    actor1 = vtk.vtkActor()
    actor1.GetProperty().SetColor(255, 0, 255)
    actor1.SetMapper(mapper1)
    ren.AddActor(actor1)
    renWin.Render()
    print ren.GetActors().GetNumberOfItems()    
    

def pickerfunc (object1, event):
    global ren
    #style = clientdata;
    #pickPos = picker.GetPickPosition()
    if event == 'LeftButtonPressEvent':
        print 'DOK'
    if event == 'LeftButtonReleaseEvent':
        print 'ROK'    
#    print object1.GetInteractor().GetEventPosition()
    object1.GetInteractor().GetPicker().Pick(object1.GetInteractor().GetEventPosition()[0], object1.GetInteractor().GetEventPosition()[1], 0, ren)
#    object1.OnLeftButtonDown()

    
    


cone = vtk.vtkConeSource()
cone.SetHeight( 3.0 )
cone.SetRadius( 1.0 )
cone.SetResolution( 10 )

map1 = vtk.vtkPolyDataMapper()
map1.SetInputConnection(cone.GetOutputPort())

actor = vtk.vtkActor()
actor.SetMapper(map1)

textMapper = vtk.vtkTextMapper()
tprop = textMapper.GetTextProperty()
tprop.SetFontFamilyToArial()
tprop.SetFontSize(10)
tprop.BoldOn()
tprop.ShadowOn()
tprop.SetColor(1, 0, 0)
textActor = vtk.vtkActor2D()
textActor.VisibilityOff()
textActor.SetMapper(textMapper)



ren = vtk.vtkRenderer()
ren.AddActor(actor)
ren.AddActor(textActor)
ren.SetBackground(0.1, 0.2, 0.4)

renWin = vtk.vtkRenderWindow()
renWin.AddRenderer(ren)
renWin.SetSize(300, 300)

iren = vtk.vtkRenderWindowInteractor()
iren.SetRenderWindow(renWin)

style = vtk.vtkInteractorStyleTrackballCamera()
iren.SetInteractorStyle(style)

picker.AddObserver("EndPickEvent", picking)    
style.AddObserver ('LeftButtonPressEvent', pickerfunc)
# style.AddObserver ('LeftButtonReleaseEvent', pickerfunc)
# style.AddObserver ('MouseMoveEvent', pickerfunc)

#style.RemoveObservers ('LeftButtonPressEvent')       
#style.RemoveObservers ('LeftButtonReleaseEvent')
#style.RemoveObservers ('MouseMoveEvent')

iren.SetPicker (picker)
iren.Initialize()
renWin.Render()
iren.Start()