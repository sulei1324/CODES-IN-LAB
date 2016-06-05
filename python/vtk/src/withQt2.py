from PyQt4 import QtCore, QtGui
from PyQt4.QtGui import QApplication
import vtk
from vtk.qt4.QVTKRenderWindowInteractor import QVTKRenderWindowInteractor
import sys

class MyStyle(vtk.vtkInteractorStyleJoystickActor):
    def __init__(self):
        self.AddObserver("KeyPressEvent", self.keyPress)
    
    def keyPress(self, obj, e):
        print obj.GetInteractor().GetKeyCode()
        print obj.GetInteractor().GetShiftKey()


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(603, 553)
        self.centralWidget = QtGui.QWidget(MainWindow) 
        self.gridlayout = QtGui.QGridLayout(self.centralWidget)
        self.vtkWidget = QVTKRenderWindowInteractor(self.centralWidget)
        self.gridlayout.addWidget(self.vtkWidget, 0, 0, 1, 1)
        MainWindow.setCentralWidget(self.centralWidget)
        
class SimpleView(QtGui.QMainWindow):
    def __init__(self, parent=None):
        QtGui.QMainWindow.__init__(self, parent)
        self.setWindowTitle("Qt With Vtk")
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        self.ren = vtk.vtkRenderer()
        self.istyle = MyStyle()
        self.ui.vtkWidget.SetInteractorStyle(self.istyle)
        self.ui.vtkWidget.GetRenderWindow().AddRenderer(self.ren)
        self.iren = self.ui.vtkWidget.GetRenderWindow().GetInteractor()
        
        source1 = vtk.vtkSphereSource()
        source1.SetCenter(0, 0, 0)
        source1.SetRadius(5.0)
        mapper1 = vtk.vtkPolyDataMapper()
        mapper1.SetInputConnection(source1.GetOutputPort())
        actor1 = vtk.vtkActor()
        actor1.SetMapper(mapper1)
        
        self.ren.AddActor(actor1)
  
if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = SimpleView()
    window.show()
    window.iren.Initialize()
    sys.exit(app.exec_())
            
