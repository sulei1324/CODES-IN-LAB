# -*- coding: utf-8 -*-

import libtiff as lt
import vtk
import numpy as np



tiff = lt.TIFF3D.open(r'..\\res\\22_24_12.tif', 'r')
a = tiff.read_image()

#origImg = np.require(a, dtype=np.uint8)
#[w, h, f] = origImg.shape
#dataImporter = vtk.vtkImageImport()
#data_string = origImg.tostring()
#dataImporter.CopyImportVoidPointer(data_string, len(data_string))
#dataImporter.CopyImportVoidPointer(a, len(a))
#dataImporter.SetDataScalarTypeToUnsignedChar()
#dataImporter.SetNumberOfScalarComponents(1)
#dataImporter.SetDataExtent(0, f-1, 0, h-1, 0, w-1)
#dataImporter.SetWholeExtent(0, f-1, 0, h-1, 0, w-1)
#
#alphaChannelFunc = vtk.vtkPiecewiseFunction()
#colorFunc = vtk.vtkColorTransferFunction()
#alphaChannelFunc.AddPoint(0, 0.0)
#alphaChannelFunc.AddPoint(255, 0.9)
#for i in xrange(0, 255):
#    colorFunc.AddRGBPoint(i,i/255.0,i/255.0,i/255.0)
#colorFunc.AddRGBPoint(0, 0, 0, 0)
#
#volumeProperty = vtk.vtkVolumeProperty()
#volumeProperty.SetColor(colorFunc)
#volumeProperty.SetScalarOpacity(alphaChannelFunc)
#
#compositeFunction = vtk.vtkVolumeRayCastCompositeFunction()
#mipRayCastFunction = vtk.vtkVolumeRayCastMIPFunction()
#volumeMapper = vtk.vtkVolumeRayCastMapper()
#volumeMapper.SetVolumeRayCastFunction(compositeFunction)
#volumeMapper.SetVolumeRayCastFunction(mipRayCastFunction)
#volumeMapper.SetMaximumImageSampleDistance(0.01)
#volumeMapper.SetInputConnection(dataImporter.GetOutputPort())
#
#volume = vtk.vtkVolume()
#volume.SetMapper(volumeMapper)
#volume.SetProperty(volumeProperty)
#
#ren = vtk.vtkRenderer()
#
#
#ren.AddVolume(volume)
#ren.SetBackground(0, 0, 0)
#ren.ResetCamera()
#
#renWin = vtk.vtkRenderWindow()
#renWin.AddRenderer(ren)
#iren = vtk.vtkRenderWindowInteractor()
#iren.SetRenderWindow(renWin)
#renWin.Render()
#iren.Start()
b = np.require(a, dtype=np.uint8)
b_string = b.tostring()
data_importer = vtk.vtkImageImport()
data_importer.CopyImportVoidPointer(b_string, len(b_string))
data_importer.SetDataScalarTypeToUnsignedChar()
data_importer.SetNumberOfScalarComponents(1)
data_importer.SetDataExtent(0, 511, 0, 511, 0, 511)
data_importer.SetWholeExtent(0, 511, 0, 511, 0, 511)
 
alphaChannelFunc = vtk.vtkPiecewiseFunction()
alphaChannelFunc.AddPoint(0, 0.0)
alphaChannelFunc.AddPoint(64, 0.3)
alphaChannelFunc.AddPoint(128, 0.5)
alphaChannelFunc.AddPoint(200, 0.7)
 
colorFunc = vtk.vtkPiecewiseFunction()
 
colorFunc.AddPoint(50, 0.1)
colorFunc.AddPoint(100, 0.5)
colorFunc.AddPoint(150, 0.7)
 
vp = vtk.vtkVolumeProperty()
vp.SetColor(colorFunc)
vp.SetScalarOpacity(alphaChannelFunc)
cf = vtk.vtkVolumeRayCastMIPFunction()
vM = vtk.vtkVolumeRayCastMapper()
vM.SetInputConnection(data_importer.GetOutputPort())
vM.SetVolumeRayCastFunction(cf)
volume = vtk.vtkVolume()
volume.SetMapper(vM)
volume.SetProperty(vp)
 
ren = vtk.vtkRenderer()
renWin = vtk.vtkRenderWindow()
renWin.AddRenderer(ren)
iren = vtk.vtkRenderWindowInteractor()
 
iren.SetRenderWindow(renWin)
ren.AddVolume(volume)
ren.SetBackground(0, 0, 0)
renWin.Render()
iren.Start()

