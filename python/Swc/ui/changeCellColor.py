# import readSwc as rs
# import os
# import sys
# import vtk
# swc1 = rs.Swc(r"..\res\dendrite.swc", (0.3, 0.3, 1))
# swc1.displayInVtk()
import vtk

class MyStyle(vtk.vtkInteractorStyleTrackballCamera):
    def __init__(self, parent=None):
        self.AddObserver("LeftButtonPressEvent", self.pickLine)
        self.AddObserver("CharEvent", self.getChar)
    
    def getChar(self, obj, e):
        global edit_mode
        if self.GetInteractor().GetKeyCode() == "1":
            print self.GetInteractor().GetKeyCode()
            edit_mode = True
            print "Can Edit!"
        if self.GetInteractor().GetKeyCode() == "2":
            edit_mode = False
#             self.GetInteractor().SetKeyCode("r")
            print "Can not Edit!"
        print self.GetInteractor().GetKeySym()
        
        
    
    def pickLine(self, obj, e):                                                                              #       print obj == self!!!!!!!!!!!!!!!!!!!!
        global poly1, ren, iren, renWin, cell_scalars, edit_mode
        clickPos = self.GetInteractor().GetEventPosition()
        print e
        if edit_mode is True:
            print "hhhh"
            print self.GetInteractor().GetLastEventPosition()
            print self.GetInteractor().GetEventPosition()            
            picker = vtk.vtkCellPicker()
            picker.SetTolerance(1 / 80.0)
            picker.Pick(clickPos[0], clickPos[1], 0, self.GetDefaultRenderer())
            print picker.GetCellId()
            if cell_scalars.GetTuple(picker.GetCellId())[0] == 0.0 and cell_scalars.GetTuple(picker.GetCellId())[1] == 255.0 and cell_scalars.GetTuple(picker.GetCellId())[2] == 255.0 :
                poly1.GetCellData().GetScalars().SetTupleValue(picker.GetCellId(), [255, 0, 255])
            else:            
                poly1.GetCellData().GetScalars().SetTupleValue(picker.GetCellId(), [0, 255, 255])
            poly1.GetCellData().Modified()
            poly1.GetCellData().Update()
        else:
            print "ssss"
        self.OnLeftButtonDown()
    

edit_mode = False
points = vtk.vtkPoints()
lines = vtk.vtkCellArray()
points.InsertNextPoint(0, 0, 0)
points.InsertNextPoint(1, 1, 1)
points.InsertNextPoint(0, 1, 0)
# lines.InsertNextCell(2)
# lines.InsertCellPoint(0)
# lines.InsertCellPoint(1)
# lines.InsertNextCell(2)
# lines.InsertCellPoint(1)
# lines.InsertCellPoint(2)
line1 = vtk.vtkLine()
line1.GetPointIds().SetId(0, 0)
line1.GetPointIds().SetId(1, 1)
line2 = vtk.vtkLine()
line2.GetPointIds().SetId(0, 1)
line2.GetPointIds().SetId(1, 2)

lines.InsertNextCell(line1)
lines.InsertNextCell(line2)


poly1 = vtk.vtkPolyData()
poly1.SetPoints(points)
poly1.SetLines(lines)


cell_scalars = vtk.vtkUnsignedCharArray()
cell_scalars.SetNumberOfComponents(3)
cell_scalars.InsertNextTupleValue([255, 0, 255])
cell_scalars.InsertNextTupleValue([255, 255, 0])
poly1.GetCellData().SetScalars(cell_scalars)                              
poly1_mapper = vtk.vtkPolyDataMapper()
poly1_mapper.SetScalarModeToUseCellData()
poly1_mapper.SetInput(poly1)     
poly1_actor = vtk.vtkActor()
poly1_actor.SetMapper(poly1_mapper)
poly1_actor.GetProperty().SetLineWidth(1)
ren = vtk.vtkRenderer()
ren.AddActor(poly1_actor)
ren.SetBackground(0.1, 0.2, 0.3)       
renWin = vtk.vtkRenderWindow()
renWin.AddRenderer(ren)
renWin.SetSize(500, 500)
iren = vtk.vtkRenderWindowInteractor()
iren.SetRenderWindow(renWin)
style1 = MyStyle()
style1.SetDefaultRenderer(ren)
iren.SetInteractorStyle(style1)
renWin.Render()
iren.Start()    