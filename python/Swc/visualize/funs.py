# -*- coding: utf-8 -*-
import vtk
import numpy as np

def get_center(points):
    sum_x = 0
    sum_y = 0
    sum_z = 0
    for i in xrange(len(points)):
        sum_x += points[i][2]
        sum_y += points[i][3]
        sum_z += points[i][4]
    
    return (sum_x / len(points), sum_y / len(points), sum_z / len(points))
    


def get_section(center, w, h, d, r):
    x_s = center[0]/ r[0] - w / 2
#    x_e = (center[0] + w / 2 - 1) / r[0]
    y_s = center[1] / r[1] - h / 2
#    y_e = (center[1] + h / 2 - 1) / r[1]
    z_s = center[2] - d / 2
#    z_e = center[2] + d / 2 - 1
    return (int(x_s), int(y_s), int(z_s), w, h , d)
    

def save_vtk_image(images, dst, i):    
    image_import = vtk.vtkImageImport()
    image_import.CopyImportVoidPointer(images.tostring(), len(images.tostring()))
    image_import.SetDataScalarTypeToUnsignedChar()
    image_import.SetNumberOfScalarComponents(1)
    image_import.SetDataExtent(0, images.shape[2] - 1, 0, images.shape[1] - 1, 0, images.shape[0] - 1)
    image_import.SetWholeExtent(0, images.shape[2] - 1, 0, images.shape[1] - 1, 0, images.shape[0] - 1)
    volume = vtk.vtkVolume()
    volume_mapper = vtk.vtkVolumeRayCastMapper()
    alpha_channel_func = vtk.vtkPiecewiseFunction()
    alpha_channel_func.AddPoint(0, 0.0)
#    alpha_channel_func.AddPoint(64, 0.3)
#    alpha_channel_func.AddPoint(128, 0.5)
    alpha_channel_func.AddPoint(100, 1.0)
    alpha_channel_func.ClampingOn()
    color_func = vtk.vtkPiecewiseFunction()
    color_func.AddPoint(5, 0.3)
    color_func.AddPoint(25, 0.5)
    color_func.AddPoint(125, 0.7)
    color_func.AddPoint(255, 1.0)
    volume_property = vtk.vtkVolumeProperty()
    volume_property.SetColor(color_func)
    volume_property.SetInterpolationTypeToLinear()
    volume_property.SetScalarOpacity(alpha_channel_func)
    volume.SetProperty(volume_property)
    volume_ray_cast_func = vtk.vtkVolumeRayCastMIPFunction()
    volume_mapper.SetInputConnection(image_import.GetOutputPort())
    volume_mapper.SetVolumeRayCastFunction(volume_ray_cast_func)
#    volume_mapper.SetSampleDistance(1)
#    volume_mapper.SetAutoAdjustSampleDistances(0)
#    volume_mapper.SetImageSampleDistance(1)
    volume.SetMapper(volume_mapper)
    
    ren = vtk.vtkRenderer()
    ren.AddVolume(volume)
    ren.SetBackground(0, 0, 0)
    renWin = vtk.vtkRenderWindow()
    renWin.SetSize(1024, 1024)
    renWin.AddRenderer(ren)
    renWin.Render()
    
    window_2_image = vtk.vtkWindowToImageFilter()
    window_2_image.SetInput(renWin)
    window_2_image.Update()
    
    png_writer = vtk.vtkPNGWriter()
    png_writer.SetFileName(dst + '%05d'%(i) + '.png')
    png_writer.SetInput(window_2_image.GetOutput())
    png_writer.Write()
    
    
            
    
    
    

