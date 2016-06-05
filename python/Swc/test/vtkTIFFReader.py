import libtiff as lt
import vtk

#tiff = lt.TIFF3D.open('.\\res\\2.tif', 'r')
#a = tiff.read_image()


reader = vtk.vtkTIFFReader()
reader.SetFileName('.\\res\\0.tif')
reader.Update()
image_viewer = vtk.vtkImageViewer2()
image_viewer.SetSize(1000, 1000)

image_viewer.SetInputConnection(reader.GetOutputPort())
iren = vtk.vtkRenderWindowInteractor()
image_viewer.SetupInteractor(iren)
image_viewer.Render()
image_viewer.GetRenderer().ResetCamera()
image_viewer.Render()
iren.Start()