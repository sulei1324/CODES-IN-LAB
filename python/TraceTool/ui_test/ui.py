import swctree
import PyQt4
from PyQt4 import QtGui, QtCore
import vtk
from vtk.qt4.QVTKRenderWindowInteractor import QVTKRenderWindowInteractor
import sys

class LineDialog(QtGui.QDialog):
    def __init__(self):
        super(LineDialog, self).__init__()
        self.layout = QtGui.QHBoxLayout()
        self.label = QtGui.QLabel("1111")
        self.lineEdit = QtGui.QLineEdit()
        self.layout.addWidget(self.label)
#         self.layout.addWidget(self.lineEdit)
        self.setLayout(self.layout)
        self.lineEdit.setText("eeeee")
        self.slider = QtGui.QSlider()
        self.slider.setOrientation(QtCore.Qt.Horizontal)
        self.slider.setRange(1, 100)
        self.layout.addWidget(self.slider)
        print self.slider.value()
        self.slider.valueChanged.connect(self.showSliderValue)
    
    def showSliderValue(self):
        print self.slider.value()
        print self.changeLineWidth()
        
    def changeLineWidth(self):
        global vtk_widget
        line_width = self.slider.value()
        tmp_renWin = vtk_widget.GetRenderWindow()
        tmp_rens = tmp_renWin.GetRenderers()
        tmp_ren = tmp_rens.GetFirstRenderer()
        tmp_actors = tmp_ren.GetActors()
        return tmp_actors.GetNumberOfItems()

class SwcEditStyle(vtk.vtkInteractorStyleTrackballCamera):
    global ren, vtk_widget
    def __init__(self):
        self.__pickPointMode = False
        self.AddObserver("LeftButtonPressEvent", self.pickPoint)
    
    def setPickPointMode(self, b):
        self.__pickPointMode = b
    
    def pickPoint(self, obj, e):
        if self.__pickPointMode == True:
            print self.GetInteractor().GetEventPosition()
            clicked_point = self.GetInteractor().GetEventPosition()
            picker1 = vtk.vtkPointPicker()
            picker1.Pick(clicked_point[0], clicked_point[1], 0, ren)
            
            picker2 = vtk.vtkPropPicker()
            picker2.PickProp(clicked_point[0], clicked_point[1], ren)
            picked_prop = picker2.GetActor()
            if picked_prop != None:    
                picked_prop.GetProperty().SetColor(1.0, 1.0, 0.0)
            else:
                print "None is picked!"
        self.OnLeftButtonDown()


def changeLineWidth():
    line_dialog = LineDialog()
    line_dialog.exec_()

def loadSwcFile():
    global vtk_widget, mainwin, ren
    swc_dialog = QtGui.QFileDialog()
    swc_src = swc_dialog.getOpenFileName(mainwin, 'Load Swc File', '.\\', "Swc File (*.swc)")
    if swc_src != '':
        s = swctree.SwcTree(swc_src)
        ren = s.renderInVtk(ren)
        vtk_widget.GetRenderWindow().AddRenderer(ren)
        
def showInVtkWidget():
    global vtk_widget, ren
    
    if ren.GetActors().GetNumberOfItems() != 0:
        vtk_widget.Render()
    else:
        swc_src = "dendrite.swc"
        s = swctree.SwcTree(swc_src)
        ren = s.renderInVtk(ren)
        vtk_widget.GetRenderWindow().AddRenderer(ren)
        vtk_widget.Render()        

def editSwc():
    global style1, tool2
    if tool2.isChecked():
        style1.setPickPointMode(True)
    else:
        style1.setPickPointMode(False)

if __name__ == '__main__':
    app = QtGui.QApplication(sys.argv) 
    mainwin = QtGui.QMainWindow()
    menubar1 = QtGui.QMenuBar(mainwin)
    menu1 = QtGui.QMenu('&File', menubar1)
    action1 = QtGui.QAction('&Load', menu1)
    menu1.addAction(action1)
    menubar1.addMenu(menu1)
    action1.triggered.connect(loadSwcFile)
    
    toolbar1 = QtGui.QToolBar(mainwin)
    tool1 = QtGui.QAction(toolbar1)
    tool1_icon = QtGui.QIcon()
    tool1_icon.addFile(r"G:\sulei\workplace\TraceTool\Resource\seed.png")
    tool1.setIcon(tool1_icon)
    tool1.setEnabled(True)
    toolbar1.addAction(tool1)
    tool1.triggered.connect(showInVtkWidget)
    tool2 = QtGui.QAction(toolbar1)
    tool2.setCheckable(True)
    tool2_icon = QtGui.QIcon()
    tool2_icon.addFile(r'G:\sulei\workplace\TraceTool\Resource\monkey_off_32x32.png', state=QtGui.QIcon.Off)
    tool2.setIcon(tool2_icon)
    tool2.setEnabled(True)
    tool2.toggled.connect(editSwc)
    toolbar1.addAction(tool2)
    tool3 = QtGui.QAction(toolbar1)
    tool3_icon = QtGui.QIcon()
    tool3_icon.addFile(r'G:\sulei\workplace\TraceTool\Resource\Science.png')
    tool3.setIcon(tool3_icon)
    tool3.triggered.connect(changeLineWidth)
    toolbar1.addAction(tool3)
    
    
    mainwin.addToolBar(toolbar1)
    mainwin.setMenuBar(menubar1)
    mainwin_location = QtCore.QRect(600, 300, 400, 400)
    mainwin.setMaximumSize(400, 400)
    mainwin.setGeometry(mainwin_location)
    central_widget = QtGui.QWidget(mainwin)
    mainwin.setCentralWidget(central_widget)
    layout1 = QtGui.QHBoxLayout()
    central_widget.setLayout(layout1)
    vtk_widget = QVTKRenderWindowInteractor(central_widget)
    vtk_widget.setMinimumSize(50, 50)
    layout1.addWidget(vtk_widget)
    vtk_widget.setSizePolicy(QtGui.QSizePolicy.Fixed, QtGui.QSizePolicy.Fixed)
    ren = vtk.vtkRenderer()
    style1 = SwcEditStyle()
    iren = vtk_widget.GetRenderWindow().GetInteractor()
    iren.SetInteractorStyle(style1)
    vtk_widget.Initialize()
    vtk_widget.Start()
    mainwin.show()
    sys.exit(app.exec_())