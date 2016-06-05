#include "bouttonmarker.h"
#include "twoLayer.h"
#include <map>
#include <memory>

int main(int argc, char *argv[])
{
    vtkSmartPointer<vtkRenderer> renImage = vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkRenderer> ren3d = vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
    vtkSmartPointer<vtkInteractorStyleTrackballCamera> is_trackball = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    renWin->SetSize(600, 600);
    vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renWin->SetNumberOfLayers(2);
    renImage->SetLayer(1);
    ren3d->SetLayer(0);
    renWin->AddRenderer(ren3d);
    renWin->AddRenderer(renImage);
    iren->SetRenderWindow(renWin);
    vtkSmartPointer<vtkSphereSource> sphere = vtkSmartPointer<vtkSphereSource>::New();
    sphere->SetRadius(100);
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInput(sphere->GetOutput());
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    ren3d->AddActor(actor);
    vtk_spnew(vtkImageTracerWidget, imageTracer);
    imageTracer->SetInteractor(iren);
    vtkSmartPointer<RenderOneStyle> renStyle = vtkSmartPointer<RenderOneStyle>::New();
    iren->SetInteractorStyle(renStyle);
    renStyle->SetRenderImage(renImage);
    renStyle->SetRender3d(ren3d);
    renStyle->SetImageTracer(imageTracer);
    renStyle->SetupImageData();
    //renImage->ResetCamera();
    vtk_sp(vtkCamera, cameraImage) = renImage->GetActiveCamera();
    //double *p = cameraImage->GetPosition();
    //double *f = cameraImage->GetFocalPoint();
    //double a = cameraImage->GetViewAngle();
    //double *u = cameraImage->GetViewUp();
    //double *c = cameraImage->GetClippingRange();
    //coutDoubleArray(p, 3);
    //coutDoubleArray(f, 3);
    //cout<<a<<endl;
    //coutDoubleArray(u, 3);
    //coutDoubleArray(c, 2);
    cameraImage->SetPosition(299.5, 299.5, 299.5);
    cameraImage->SetFocalPoint(299.5, 299.5, 0);
    cameraImage->SetViewAngle(90);
    cameraImage->SetViewUp(0.0, 1.0, 0.0);
    cameraImage->SetClippingRange(299, 400);
    double *v = cameraImage->GetViewShear();
    coutDoubleArray(v, 3);


    
    cameraImage->Modified();
    imageTracer->SetViewProp(renStyle->GetImageActor());
    ren3d->SetInteractive(0);
    renImage->SetInteractive(1);
    renWin->Render();
    iren->Initialize();
    iren->Start();
}

