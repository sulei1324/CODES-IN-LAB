# -*- coding: utf-8 -*-


import readSwc as rs
import funs
import readMostd as rm
import vtk
#import libtiff as lt


swc_src = '../res/axon_test.swc'
mostd_src = '../res/TDI072-test.mostd'
dst = 'G:\\sulei\\workplace\\Swc\\result\\'
image_resolution = (0.3, 0.3, 1)
block_width = 256
block_height = 256
block_depth = 64



swc = rs.Swc(swc_src, image_resolution)

line = swc.lines[0]
points = line.points
i = 0
for s, e in zip(xrange(0, len(points), 64), xrange(63, len(points), 64)):
    if i != 0:
        continue
    used_64_points = points[s : e + 1]
    used_center = funs.get_center(used_64_points)
    block_section = funs.get_section(used_center, block_width, block_height, block_depth, image_resolution)
    used_images = rm.Roi(block_section, mostd_src).getImages()
#    funs.save_vtk_image(used_images, dst, i)
    image_import = vtk.vtkImageImport()
    image_import.CopyImportVoidPointer(used_images.tostring(), len(used_images.tostring()))
    image_import.SetDataScalarTypeToUnsignedChar()
    image_import.SetNumberOfScalarComponents(1)
    image_import.SetDataExtent(0, used_images.shape[2] - 1, 0, used_images.shape[1] - 1, 0, used_images.shape[0] - 1)
    image_import.SetWholeExtent(0, used_images.shape[2] - 1, 0, used_images.shape[1] - 1, 0, used_images.shape[0] - 1)
    volume = vtk.vtkVolume()
    volume_mapper = vtk.vtkVolumeRayCastMapper()
    volume_mapper.SetSampleDistance(1)
    volume_mapper.SetAutoAdjustSampleDistances(0)
    volume_mapper.SetImageSampleDistance(1)
    alpha_channel_func = vtk.vtkPiecewiseFunction()
    alpha_channel_func.AddPoint(0.0, 0.0)
#    alpha_channel_func.AddPoint(64, 0.3)
#    alpha_channel_func.AddPoint(128, 0.5)
#    alpha_channel_func.AddPoint(80, 1.0)
    alpha_channel_func.AddPoint(100, 1.0)
    alpha_channel_func.ClampingOn()
    color_func = vtk.vtkPiecewiseFunction()
    color_func.AddPoint(5, 0.3)
    color_func.AddPoint(25, 0.5)
    color_func.AddPoint(125, 0.7)
    color_func.AddPoint(255, 1.0)
    color_func.ClampingOff()
    color_func1 = vtk.vtkColorTransferFunction()
    color_func1.AddRGBPoint(0.0,0.0,0.0,0.0)
    color_func1.AddRGBPoint(5.0,0.0,0.3,0.0)
    color_func1.AddRGBPoint(25.0,0.0,0.5,0.0)
    color_func1.AddRGBPoint(125.0,0.0,0.7,0.0)
    color_func1.AddRGBPoint(255.0,0.0,1.0,0.0)
    volume_property = vtk.vtkVolumeProperty()
    volume_property.SetColor(color_func)
    volume_property.SetScalarOpacity(alpha_channel_func)
    volume_property.ShadeOff()
    volume_property.SetInterpolationTypeToLinear()
    volume.SetProperty(volume_property)
    volume_ray_cast_func = vtk.vtkVolumeRayCastMIPFunction()
    volume_mapper.SetInputConnection(image_import.GetOutputPort())
    volume_mapper.SetVolumeRayCastFunction(volume_ray_cast_func)
    volume.SetMapper(volume_mapper)
    
    ren = vtk.vtkRenderer()
    ren.AddVolume(volume)
    ren.SetBackground(0, 0, 0)
    renWin = vtk.vtkRenderWindow()
    iren = vtk.vtkRenderWindowInteractor()
    iren.SetRenderWindow(renWin)
    renWin.SetSize(300, 300)
    renWin.AddRenderer(ren)
    renWin.Render()
    window_2_image = vtk.vtkWindowToImageFilter()
    window_2_image.SetInput(renWin)
    window_2_image.Update()
    
    png_writer = vtk.vtkPNGWriter()
    png_writer.SetFileName(dst + '%05d'%(i) + '.png')
    png_writer.SetInput(window_2_image.GetOutput())
    png_writer.Write()    
    iren.Initialize()
    iren.Start()    
    print i
    i += 1

