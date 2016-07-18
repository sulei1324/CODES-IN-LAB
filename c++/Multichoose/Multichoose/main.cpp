#include "multichoose.h"
#include "twoLayer.h"
#include <map>
#include <memory>

int main(int argc, char *argv[])
{
    //window, interacor
    vtkSmartPointer<vtkRenderer> renImage = vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkRenderer> ren3d = vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
    //vtkSmartPointer<vtkInteractorStyleTrackballCamera> is_trackball = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    renWin->SetSize(600, 600);
    vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renWin->SetNumberOfLayers(2);
    renImage->SetLayer(1);
    ren3d->SetLayer(0);
    renWin->AddRenderer(ren3d);
    renWin->AddRenderer(renImage);
    iren->SetRenderWindow(renWin);
    
    //tracerWidget
    vtk_spnew(vtkImageTracerWidget, imageTracer);
    imageTracer->SetInteractor(iren);
    imageTracer->AutoCloseOn();
    
    
    //area picker
    vtk_spnew(vtkAreaPicker, areaPicker);
    areaPicker->PickFromListOn();
    
    
    //style
    vtkSmartPointer<RenderOneStyle> renStyle = vtkSmartPointer<RenderOneStyle>::New();
    iren->SetInteractorStyle(renStyle);
    renStyle->SetRenderImage(renImage);
    renStyle->SetRender3d(ren3d);
    renStyle->SetImageTracer(imageTracer);
    renStyle->SetAreaPicker(areaPicker);
    renStyle->CreateSphereActors(100, 100);
    
    
    
    //window modifed command
    vtk_spnew(WindowModifiedCommand, winCommand);
    winCommand->SetImageRenderer(renImage);
    renWin->AddObserver(vtkCommand::ModifiedEvent, winCommand);
    imageTracer->SetViewProp(winCommand->GetImageActor());
    renStyle->SetImageActor(winCommand->GetImageActor());
    winCommand->GetImageActor()->SetVisibility(false);
    
    
    //tracer command
    vtk_spnew(ImageTracerCommand, tracerCommand);
    tracerCommand->SetWindow(renWin);
    tracerCommand->SetImageRenderer(renImage);
    tracerCommand->Set3dRender(ren3d);
    tracerCommand->SetAreaPicker(areaPicker);
    imageTracer->AddObserver(vtkCommand::StartInteractionEvent, tracerCommand);
    imageTracer->AddObserver(vtkCommand::EndInteractionEvent, tracerCommand);
    
    
    ren3d->SetInteractive(1);
    renImage->SetInteractive(0);
    renWin->Render();
    iren->Initialize();
    iren->Start();
}

