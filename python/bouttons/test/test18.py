import vtk
from vtk.qt4.QVTKRenderWindowInteractor import QVTKRenderWindowInteractor
import cv2
from PyQt4 import QtGui as qgui
from PyQt4 import QtCore as qcore
import sys
import numpy as np


class Mwindow(qgui.QMainWindow):
    def __init__(self):
        super(Mwindow, self).__init__()
        self.importer = vtk.vtkImageImport()
        self.main_widget = QVTKRenderWindowInteractor(parent=self)
        self.setCentralWidget(self.main_widget)
        self.ren = vtk.vtkRenderer()
        self.image_actor = vtk.vtkImageActor()
        self.image_actor.SetInputData(self.importer.GetOutput())
        self.iren = vtk.vtkRenderWindowInteractor()
        self.main_widget.GetRenderWindow().AddRenderer(self.ren)
        self.ren.AddActor(self.image_actor)
        self.im1 = cv2.imread('1.tif', cv2.CV_LOAD_IMAGE_UNCHANGED)
        self.im1_str = self.im1.tostring()       
        self.importer.SetNumberOfScalarComponents(1)
        self.importer.SetDataScalarTypeToUnsignedChar()
        self.importer.SetWholeExtent(0, 799, 0, 799, 0, 0)
        self.importer.SetDataExtent(0, 799, 0, 799, 0, 0)
        self.image_actor.SetDisplayExtent(0, 799, 0, 799, 0, 0)
        self.importer.SetImportVoidPointer(self.im1_str, len(self.im1_str))


if __name__ == '__main__':
    app = qgui.QApplication(sys.argv)
    mwin = Mwindow()
    mwin.show()
    print len(mwin.im1_str)
    
    print vtk.VTK_MAJOR_VERSION
    print vtk.VTK_VERSION
    mwin.importer.Update()
    mwin.main_widget.Initialize()
    mwin.main_widget.Start()     
    sys.exit(app.exec_())
