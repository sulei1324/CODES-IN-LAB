# -*- coding: utf-8 -*-

import vtk
import numpy as np
import libtiff as lt




class MyStyle(vtk.vtkInteractorStyleImage):
    def __init__(self, parent=None):
        print "ddd"
        self.AddObserver("LeftButtonPressEvent", self.leftButtonDown)
        self.AddObserver("MouseWheelForwardEvent", self.forward_fun)
        self.AddObserver("MouseWheelBackwardEvent", self.backward_fun)
        
        
    def forward_fun(self, *arg):
        s = imageViewer.GetSlice()
        n = s + 1
        if n > 511:
            n = 0
        imageViewer.SetSlice(n)
    
    def backward_fun(self, *arg):
        s = imageViewer.GetSlice()
        n = s - 1
        if n < 0:
            n = 511
        imageViewer.SetSlice(n)
    
    def leftButtonDown(self, *arg):
        inter1 = self.GetInteractor()
        click_pos = inter1.GetEventPosition()
        s = imageViewer.GetSlice()
#        print imageViewer.GetSize()
#        print imageViewer.GetImageActor().GetBounds()
#        image_data.SetScalarComponentFromFloat(click_pos[0], click_pos[1], s, 0, 255.0)
#        image_data.SetScalarComponentFromFloat(click_pos[0] + 1, click_pos[1], s, 0, 255.0)
#        image_data.SetScalarComponentFromFloat(click_pos[0], click_pos[1] + 1, s, 0, 255.0)
#        image_data.SetScalarComponentFromFloat(click_pos[0] - 1, click_pos[1], s, 0, 255.0)
#        image_data.SetScalarComponentFromFloat(click_pos[0], click_pos[1] - 1, s, 0, 255.0)
#        image_import.Modified()
#        image_import.Update()
#        imageViewer.SetInput(image_import.GetOutput())
#        imageViewer.Render()
        picker = vtk.vtkCellPicker()
        picker.Pick(click_pos[0], click_pos[1], s, imageViewer.GetRenderer())
        pos = picker.GetPickPosition()
        print pos
        sphereSource = vtk.vtkSphereSource()
        sphereSource.SetCenter(pos[0], pos[1], pos[2])
        sphereSource.SetRadius(1)
        sphereMapper = vtk.vtkPolyDataMapper()
        sphereMapper.SetInputConnection(sphereSource.GetOutputPort())
        sphereActor = vtk.vtkActor()
        sphereActor.SetMapper(sphereMapper)
        sphereActor.GetProperty().SetColor(255.0, 0.0, 0.0)
        imageViewer.GetRenderer().AddActor(sphereActor)
        imageViewer.Render()

def fun1():
    print "ddddd"

global i, imageViewer

i = 100
Tiff = lt.TIFF3D.open('G:\\sulei\\workplace\\Swc\\res\\22_24_12.tif', 'r')

images = Tiff.read_image()

image_import  = vtk.vtkImageImport()

images = np.require(images, dtype=np.uint8)
images_string = images.tostring()
image_import.CopyImportVoidPointer(images_string, len(images_string))
image_import.SetDataScalarTypeToUnsignedChar()
image_import.SetDataExtent(0, 511, 0, 511, 0, 511)
image_import.SetWholeExtent(0, 511, 0, 511, 0, 511)
image_import.SetNumberOfScalarComponents(1)
image_import.Update()
image_data = image_import.GetOutput()
#image_data1 = vtk.vtkImageData()
#image_data1.DeepCopy(image_data)
style = MyStyle()
irenWin = vtk.vtkRenderWindowInteractor()
   
#style = vtk.vtkInteractorStyleImage()
#style.SetInteractionModeToImageSlicing()
#style.AddObserver("LeftButtonPressEvent", fun1)

#irenWin.SetInteractorStyle(style)
imageViewer = vtk.vtkImageViewer2()
imageViewer.SetInput(image_data)

imageViewer.SetupInteractor(irenWin)
imageViewer.SetColorLevel(50)
imageViewer.SetColorWindow(100)
imageViewer.SetSlice(i)
imageViewer.SetSliceOrientationToXY()
imageViewer.Render()
irenWin.SetInteractorStyle(style)                                    #the location is important
irenWin.Start()




