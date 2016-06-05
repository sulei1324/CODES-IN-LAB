# -*- coding: utf-8 -*-

import libtiff as lt
import vtk
import numpy as np


cube_data = vtk.vtkPolyData()
cube_points = vtk.vtkPoints()
cube_cells = vtk.vtkCellArray()

cube_points.InsertPoint(0, (0.0, 0.0, 0.0))
cube_points.InsertPoint(1, (0.0, 511.0, 0.0))
cube_points.InsertPoint(2, (0.0, 511.0, 511.0))
cube_points.InsertPoint(3, (0.0, 0.0, 511.0))
cube_points.InsertPoint(4, (511.0, 0.0, 0.0))
cube_points.InsertPoint(5, (511.0, 511.0, 0.0))
cube_points.InsertPoint(6, (511.0, 0.0, 511.0))
cube_points.InsertPoint(7, (511.0, 511.0, 511.0))
cube_cells.InsertNextCell(5)
cube_cells.InsertCellPoint(0)
cube_cells.InsertCellPoint(1)
cube_cells.InsertCellPoint(2)
cube_cells.InsertCellPoint(3)
cube_cells.InsertCellPoint(0)
cube_cells.InsertNextCell(5)
cube_cells.InsertCellPoint(0)
cube_cells.InsertCellPoint(4)
cube_cells.InsertCellPoint(5)
cube_cells.InsertCellPoint(1)
cube_cells.InsertCellPoint(0)
cube_cells.InsertNextCell(5)
cube_cells.InsertCellPoint(4)
cube_cells.InsertCellPoint(5)
cube_cells.InsertCellPoint(7)
cube_cells.InsertCellPoint(6)
cube_cells.InsertCellPoint(4)
cube_cells.InsertNextCell(5)
cube_cells.InsertCellPoint(2)
cube_cells.InsertCellPoint(3)
cube_cells.InsertCellPoint(6)
cube_cells.InsertCellPoint(7)
cube_cells.InsertCellPoint(2)
cube_data.SetPoints(cube_points)
cube_data.SetLines(cube_cells)
cube_mapper = vtk.vtkPolyDataMapper()
cube_mapper.SetInput(cube_data)

cube_actor = vtk.vtkActor()
cube_actor.SetMapper(cube_mapper)
cube_pro = cube_actor.GetProperty()
cube_pro.SetColor(1.0, 0.0, 0.0)
cube_pro.SetLineWidth(5.0)










tiff = lt.TIFF3D.open('G:\\sulei\\workplace\\Swc\\res\\22_24_12.tif', 'r')
a = tiff.read_image()
#print len(a)


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
alphaChannelFunc.AddPoint(100, 1.0)

colorFunc = vtk.vtkPiecewiseFunction()

colorFunc.AddPoint(5, 0.3)
colorFunc.AddPoint(25, 0.5)
colorFunc.AddPoint(125, 0.7)
colorFunc.AddPoint(255, 1.0)

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
camera1 = ren.GetActiveCamera()
#print camera2.GetPosition()
#print camera2.GetFocalPoint()
#print camera2.GetViewUp()
#print camera2.GetViewAngle()
#print camera2.GetClippingRange()
#print camera2.GetEyeAngle()
#(0.0, 0.0, 1.0)
#(0.0, 0.0, 0.0)
#(0.0, 1.0, 0.0)
#30.0
#(0.01, 1000.01)
#2.0
#camera1.ParallelProjectionOff()
camera1.SetPosition(256.0, 256.0, 10.0)
camera1.SetFocalPoint(256.0, 256.0, 100.0)
camera1.SetViewUp(0.0, -1.0, 0.0)
camera1.SetViewAngle(60.0)
camera1.SetClippingRange(-1.0, 800.0)
#camera1.ParallelProjectionOff()
ren.SetActiveCamera(camera1)




renWin = vtk.vtkRenderWindow()
renWin.AddRenderer(ren)
iren = vtk.vtkRenderWindowInteractor()

iren.SetRenderWindow(renWin)
ren.AddActor(cube_actor)
ren.AddVolume(volume)
ren.SetBackground(0.1, 0.1, 0.1)
renWin.Render()
iren.Start()

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