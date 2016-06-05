# -*- coding: utf-8 -*-
"""
Created on Wed Aug 12 16:12:08 2015

@author: 苏雷
"""

import vtk
import cv2 as cv
import numpy as np
import libtiff

res = 'G:\\sulei\\TDI072\\resample\\'
file_pre = res + 'test_'
file_post = '_res.tif'
n = 11895
width = 1188
height = 1750
b = 6
e = 1190

brain_array = np.zeros((1750, 1188, 1185), dtype=np.uint8)

for i in xrange(b, e + 1):
    file_name = file_pre + "%05d"%i + file_post
    brain_array[:, :, i - 6] =cv.imread(file_name, cv.CV_LOAD_IMAGE_UNCHANGED)
    print i

brain_str = np.require(brain_array, dtype=np.uint8)
brain_str = brain_array.tostring('C')

image_importer = vtk.vtkImageImport()
image_importer.CopyImportVoidPointer(brain_str, len(brain_str))
image_importer.SetDataScalarTypeToUnsignedChar()
image_importer.SetNumberOfScalarComponents(1)
image_importer.SetDataExtent(0, 1187, 0, 1749, 0, 1184)
image_importer.SetWholeExtent(0, 1187, 0, 1749, 0, 1184)


alphaChannelFunc = vtk.vtkPiecewiseFunction()
alphaChannelFunc.AddPoint(0, 0.0)
alphaChannelFunc.AddPoint(64, 0.3)
alphaChannelFunc.AddPoint(128, 0.5)
alphaChannelFunc.AddPoint(200, 0.7)

colorFunc = vtk.vtkColorTransferFunction()

colorFunc.AddRGBPoint(50, 1.0, 0.0, 0.0)
colorFunc.AddRGBPoint(100, 0.0, 1.0, 0.0)
colorFunc.AddRGBPoint(150, 0.0, 0.0, 1.0)

vp = vtk.vtkVolumeProperty()
vp.SetColor(colorFunc)
vp.SetScalarOpacity(alphaChannelFunc)
cf = vtk.vtkVolumeRayCastMIPFunction()
vM = vtk.vtkVolumeRayCastMapper()
vM.SetInputConnection(image_importer.GetOutputPort())
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





