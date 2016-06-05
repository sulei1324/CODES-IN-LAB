# -*- coding: utf-8 -*-

# -*- coding: utf-8 -*-


import readSwc as rs
import funs
import readMostd as rm
import vtk
#import libtiff as lt


swc_src = '../res/axon_test.swc'
mostd_src = '../res/TDI072-test.mostd'
dst = 'G:\\sulei\\workplace\\Swc\\result\\1\\'
image_resolution = (0.3, 0.3, 1)
block_width = 1024
block_height = 1024
block_depth = 400



swc = rs.Swc(swc_src, image_resolution)

line = swc.lines[0]
points = line.points
i = 0
for s, e in zip(xrange(0, len(points), 64), xrange(63, len(points), 64)):
    used_64_points = points[s : e + 1]
    used_center = funs.get_center(used_64_points)
    block_section = funs.get_section(used_center, block_width, block_height, block_depth, image_resolution)
    used_images = rm.Roi(block_section, mostd_src).getImages()
#    rm.Roi(block_section, mostd_src).outputImages(dst, False)
#    funs.save_vtk_image(used_images, dst, i)
    image_import = vtk.vtkImageImport()
    image_import.CopyImportVoidPointer(used_images.tostring(), len(used_images.tostring()))
#    image_import.SetDataScalarTypeToUnsignedShort()    #16bit
    image_import.SetDataScalarTypeToUnsignedChar()  #8bit
    image_import.SetNumberOfScalarComponents(1)
    image_import.SetDataExtent(0, used_images.shape[2] - 1, 0, used_images.shape[1] - 1, 0, used_images.shape[0] - 1)
    image_import.SetWholeExtent(0, used_images.shape[2] - 1, 0, used_images.shape[1] - 1, 0, used_images.shape[0] - 1)
    volume = vtk.vtkVolume()
    volume_mapper = vtk.vtkVolumeRayCastMapper()
    volume_mapper.SetSampleDistance(1)
    volume_mapper.SetAutoAdjustSampleDistances(0)
    volume_mapper.SetImageSampleDistance(1)
    alpha_channel_func = vtk.vtkPiecewiseFunction()
#    alpha_channel_func.AddPoint(5, 0.3)
#    alpha_channel_func.AddPoint(100, 0.5)
#    alpha_channel_func.AddPoint(300, 0.9)
#    alpha_channel_func.AddPoint(65536, 1.0)         #16bit
    alpha_channel_func.AddPoint(5, 0.3)
    alpha_channel_func.AddPoint(50, 0.5)
    alpha_channel_func.AddPoint(100, 0.7)
    alpha_channel_func.AddPoint(255, 1.0)
    alpha_channel_func.ClampingOn()
    color_func = vtk.vtkPiecewiseFunction()
    color_func.AddPoint(5, 0.3)
    color_func.AddPoint(50, 0.5)
    color_func.AddPoint(100, 0.7)
    color_func.AddPoint(255, 1.0)
    color_func.ClampingOff()
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
    
    
    
    
#    camera1 = vtk.vtkCamera()
    ren = vtk.vtkRenderer()
 #   camera2 = ren.GetActiveCamera() 
#    camera2.SetPosition(128, 128, -1000)
#    camera2.SetFocalPoint(128, 128, 300)
#    camera2.SetViewAngle(30.0)
#    camera2.SetClippingRange((-10, 300))
#    camera2.ParallelProjectionOn()
#    ren.SetActiveCamera(camera2)
#    camera2.SetFocalPoint(0.0, 0.0, 0.0)
#    camera2.SetPosition(0.0, 0.0, 50.0)
#    print camera2.GetPosition()
#    print camera2.GetFocalPoint()
#    print camera2.GetViewUp()
#    print camera2.GetViewAngle()
#    print camera2.GetClippingRange()
#    print camera2.GetEyeAngle()
#    print volume.GetBounds()  # (0.0, 255.0, 0.0, 255.0, 0.0, 255.0)
    ren.AddVolume(volume)
    ren.SetBackground(0, 0, 0)
    renWin = vtk.vtkRenderWindow()
#    iren = vtk.vtkRenderWindowInteractor()
#    iren.SetRenderWindow(renWin)
    renWin.SetSize(600, 600)
    renWin.AddRenderer(ren)
    renWin.Render()
    window_2_image = vtk.vtkWindowToImageFilter()
    window_2_image.SetInput(renWin)
    window_2_image.Update()
    
    png_writer = vtk.vtkBMPWriter()
    png_writer.SetFileName(dst + '%05d'%(i) + '.bmp')
    png_writer.SetInput(window_2_image.GetOutput())
    png_writer.Write()    
#    iren.Initialize()
#    iren.Start()    
    print i
    i += 1



