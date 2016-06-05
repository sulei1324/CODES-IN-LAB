import vtk
import PyQt4
from PyQt4 import QtGui as qgui
from PyQt4 import QtCore as qcore
from vtk.qt4.QVTKRenderWindowInteractor import QVTKRenderWindowInteractor
import threading as thdg
import sys
import swctree as st
from testUI import Ui_MainWindow

def box_fun(obj1, e):
    global win
    t = vtk.vtkTransform()
    obj1.GetRepresentation().GetTransform(t)
    win.actor.SetUserTransform(t)
    win.ui.label.Render()


# class VtkCallback1(vtk):
#     def __init__(self):
#         super(VtkCallback1, self).__init__()
#      
#     def SetActor(self, a):
#         self.actor = a
#      
#     def execute(self, caller, i, *args):
#         t = vtk.vtkTransform()
#         caller.GetRepresentation().GetTransform()
#         self.actor.SetUserTransfrom(t)
        









class MainWin(qgui.QMainWindow):
    def __init__(self):
        super(MainWin, self).__init__()
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        self.ui.pushButton.clicked.connect(self.buttonDown)
        
    def buttonDown(self, *args):
        self.iniVTK()
        self.ren.ResetCamera()
        self.ui.label.Initialize()
        self.ui.label.Start()
    
    def iniVTK(self):
        self.actor = vtk.vtkActor()
        self.sphere = vtk.vtkSphereSource()
        self.sphere.SetRadius(3.0)
        self.mapper = vtk.vtkPolyDataMapper()
        self.mapper.SetInput(self.sphere.GetOutput())
        self.actor.SetMapper(self.mapper)
        self.actor.GetProperty().SetColor(0.0, 255.0, 0.0)
        self.ren = vtk.vtkRenderer()
        self.ren.AddActor(self.actor)
        self.ren.SetBackground(0, 0, 1)
        self.ui.label.GetRenderWindow().AddRenderer(self.ren)
        self.style = vtk.vtkInteractorStyleTrackballCamera()
        self.ui.label.SetInteractorStyle(self.style)
        self.box_widget = vtk.vtkBoxWidget2()
        self.box_widget.SetInteractor(self.ui.label)
        self.box_widget.GetRepresentation().SetPlaceFactor(1.25)
        self.box_widget.GetRepresentation().PlaceWidget(self.actor.GetBounds())
        self.box_widget.AddObserver('InteractionEvent', box_fun)
        self.box_widget.On()
        

if __name__ == '__main__':
    app = qgui.QApplication(sys.argv)
    win = MainWin()
    win.show()
    sys.exit(app.exec_())
