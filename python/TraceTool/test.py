import sys
from test_ui import Ui_MainWindow
from PyQt4 import QtCore 
from PyQt4 import QtGui
import vtk

def ren1():
    global iren
    iren.Initialize()
    iren.Start()    

ren = vtk.vtkRenderer()
app = QtGui.QApplication(sys.argv)
mainwindow = QtGui.QMainWindow()
ui = Ui_MainWindow()
ui.setupUi(mainwindow)
ui.vtkWidget.GetRenderWindow().AddRenderer(ren)
mainwindow.connect(ui.pushButton, QtCore.SIGNAL("clicked()"), ren1)
iren = ui.vtkWidget.GetRenderWindow().GetInteractor()
source1 = vtk.vtkSphereSource()
source1.SetCenter(0, 0, 0) 
source1.SetRadius(5.0)
mapper1 = vtk.vtkPolyDataMapper()
mapper1.SetInputConnection(source1.GetOutputPort())
actor1 = vtk.vtkActor()
actor1.SetMapper(mapper1)
ren.AddActor(actor1)
mainwindow.show()

sys.exit(app.exec_())

