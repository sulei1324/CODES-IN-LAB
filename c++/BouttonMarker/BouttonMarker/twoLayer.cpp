#include "twoLayer.h"

void coutDoubleArray(double *a, int n){
    for(int i = 0; i < n; ++i){
        cout<<a[i]<<" ";
    }
    cout<<endl;
}


vtkStandardNewMacro(RenderOneStyle);
RenderOneStyle::RenderOneStyle(){
    drawFlag = false;
    whichLayerRenderInteractive = 1;
}
RenderOneStyle::~RenderOneStyle(){

}

void RenderOneStyle::OnLeftButtonDown(){
    cout<<"sss"<<endl;
    imageTracer->On();
    vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
}

void RenderOneStyle::OnLeftButtonUp(){
    cout<<"sssseee"<<endl;
    vtkInteractorStyleTrackballCamera::OnLeftButtonUp();
}

void RenderOneStyle::OnMouseMove(){
    if(whichLayerRenderInteractive == 0){
        vtkInteractorStyleTrackballCamera::OnMouseMove();
    }else{
        
    }
    
}

void RenderOneStyle::OnMouseWheelForward()
{
    vtk_sp(vtkCamera, cameraImage) = renImage->GetActiveCamera();
    vtk_sp(vtkCamera, camera3d) = ren3d->GetActiveCamera();
    camera3d->Zoom(1.1);
    cameraImage->Zoom(1.1);
    cout<<cameraImage->GetViewAngle()<<endl;
    this->GetInteractor()->Render();
    
    

}


void RenderOneStyle::OnMouseWheelBackward()
{
    vtk_sp(vtkCamera, cameraImage) = renImage->GetActiveCamera();
    vtk_sp(vtkCamera, camera3d) = ren3d->GetActiveCamera();
    camera3d->Zoom(0.9);
    cameraImage->Zoom(0.9);
    cout<<cameraImage->GetViewAngle()<<endl;
    this->GetInteractor()->Render();
}

void RenderOneStyle::OnRightButtonDown()
{

}

void RenderOneStyle::OnRightButtonUp()
{

}

void RenderOneStyle::OnChar()
{
    vtk_sp(vtkRenderWindowInteractor, iren) = this->GetInteractor();
    char inputKey = iren->GetKeyCode();
    switch(inputKey){
        case 'c':
        case 'C':
        {
            cout<<"eeeqq"<<endl;
            SetRenImageEnabled(drawFlag);
            break;
        
        }
    
    
    }

}

void RenderOneStyle::SetupImageData()
{
    imageData = vtk_new(vtkImageData);
    vtk_sp(vtkRenderWindow, renWin) = this->GetInteractor()->GetRenderWindow();
    imageData->SetScalarTypeToUnsignedChar();
    imageData->SetNumberOfScalarComponents(4);
    imageData->SetDimensions(renWin->GetSize()[0], renWin->GetSize()[1], 1);
    imageData->SetExtent(0, renWin->GetSize()[0] - 1, 0, renWin->GetSize()[1] - 1, 0, 0);
    imageData->SetSpacing(1, 1, 1);
    imageData->SetWholeExtent(0, renWin->GetSize()[0] - 1, 0, renWin->GetSize()[1] - 1, 0, 0);
    for(int y = 0; y < renWin->GetSize()[1]; ++y){
        for(int x =0; x < renWin->GetSize()[0]; ++x){
            unsigned char *pixel = static_cast<unsigned char *>(imageData->GetScalarPointer(x, y, 0));
            if((x > 0 && x < 3) || (y > 0 && y < 3) || (x < renWin->GetSize()[0] && x > renWin->GetSize()[0] - 3) || (y < renWin->GetSize()[1] && y > renWin->GetSize()[0] - 3)){
                pixel[0] = 255;
                pixel[1] = 0;
                pixel[2] = 0;
                pixel[3] = 255;
            }else{
                pixel[0] = 255;
                pixel[1] = 255;
                pixel[2] = 255;
                pixel[3] = 40;
            }
        }
    }
    imageActor = vtkSmartPointer<vtkImageActor>::New();
    imageActor->SetInput(imageData);
    renImage->AddActor(imageActor);
}

void RenderOneStyle::SetRenImageEnabled(bool arg)
{
    imageActor->SetVisibility(arg);
    if(arg){
        imageTracer->On();
    }else{
        imageTracer->Off();
    }
    this->GetInteractor()->Render();
    drawFlag = ! drawFlag;
}


WindowModifiedCommand::WindowModifiedCommand()
{

}

WindowModifiedCommand::~WindowModifiedCommand()
{

}

void WindowModifiedCommand::Execute( vtkObject *caller, unsigned long eventId, void *callData )
{

}
