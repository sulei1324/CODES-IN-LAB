#include "stdafx.h"
#include "test.h"

NGInteractorStyleImage::NGInteractorStyleImage(){
    isLeftButtonPressed = false;
    mwlc = vtkSmartPointer<vtkImageMapToWindowLevelColors>::New();
}

void NGInteractorStyleImage::OnLeftButtonDown(){
    isLeftButtonPressed = true;
}

void NGInteractorStyleImage::OnLeftButtonUp(){
    isLeftButtonPressed = false;
}

void NGInteractorStyleImage::OnMouseMove(){
    vtkSmartPointer<vtkRenderWindowInteractor> rwi = this->Interactor;
    if(rwi->GetShiftKey()){
        cout<<rwi->GetEventPosition()[0]<<endl;
    }else{
        cout<<"eeee"<<endl;
    }
}

void NGInteractorStyleImage::OnMouseWheelForward(){
    vtkSmartPointer<vtkRenderWindowInteractor> rwi = this->Interactor;
    double* bounds = imActor->GetBounds();
    int w = static_cast<int>(bounds[1]) + 1;
    int h = static_cast<int>(bounds[3]) + 1;
    int t = imActor->GetSliceNumberMax() + 1;
    int cs = imActor->GetZSlice();
    int ns = cs + 1;
    if(ns > t - 1){
        ns = t - 1;
    }
    imActor->SetDisplayExtent(0, w-1, 0, h-1, ns, ns);
    imActor->Modified();
    cout<<rwi->GetShiftKey()<<endl;
    ren->ResetCamera();
    rwi->Render();
}

void NGInteractorStyleImage::OnMouseWheelBackward(){
    vtkSmartPointer<vtkRenderWindowInteractor> rwi = this->Interactor;
    double* bounds = imActor->GetBounds();
    int w = static_cast<int>(bounds[1]) + 1;
    int h = static_cast<int>(bounds[3]) + 1;
    int t = imActor->GetSliceNumberMax() + 1;
    int cs = imActor->GetZSlice();
    int ns = cs - 1;
    if(ns < 0){
        ns = 0;
    }
    imActor->SetDisplayExtent(0, w-1, 0, h-1, ns, ns);
    imActor->Modified();
    ren->ResetCamera();
    rwi->Render();
}

NGInteractorStyleImage *NGInteractorStyleImage::New(){
    return new NGInteractorStyleImage();
}

NGInteractorStyleImage::~NGInteractorStyleImage(){
}