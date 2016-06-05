// CameraTest.cpp : 定义控制台应用程序的入口点。
//
/********************************************************************
	created:	2016/05/31
	created:	31:5:2016   9:51
	filename: 	g:\sulei\workplace\vs\CameraTest\CameraTest\CameraTest.cpp
	file path:	g:\sulei\workplace\vs\CameraTest\CameraTest
	file base:	CameraTest
	file ext:	cpp
	author:		Su Lei
	
	purpose:	To Find How to Use VtkCamera
*********************************************************************/
#include "stdafx.h"
#define VTK_SPNew(type, var) vtkSmartPointer<type> var =  vtkSmartPointer<type>::New()
#define VTK_SP(type, var) vtkSmartPointer<type> var

void coutDoubleArray(double *a, int n){
    for(int i = 0; i < n; ++i){
        cout<<a[i]<<" ";
    }
    cout<<endl;
}




int _tmain(int argc, _TCHAR* argv[])
{
    VTK_SPNew(vtkCamera, camera);
    double focal[3] = {20.0, 0.0, -10.0};
    camera->SetFocalPoint(focal);
    double position[3] = {0.0, 0.0, -10.0};
    double planeSix[24];
    camera->SetPosition(position);
    camera->SetClippingRange(10.0, 30.0);
    camera->SetViewAngle(10.0);
    camera->Modified();
    VTK_SPNew(vtkCameraActor, actor1);
    actor1->SetCamera(camera);
    actor1->GetProperty()->SetLineWidth(5.0);
    actor1->GetProperty()->SetColor(255, 0, 0);
    actor1->Modified();
    coutDoubleArray(actor1->GetBounds(), 6);
    
    VTK_SPNew(vtkSphereSource, sphere);
    sphere->SetCenter(0.0, 0.0, -10.0);
    sphere->SetRadius(1.0);
    
    VTK_SPNew(vtkPolyDataMapper, mapper);
    VTK_SPNew(vtkActor, actor);
    mapper->SetInput(sphere->GetOutput());
    mapper->Update();
    cout<<sphere->GetOutput()->GetNumberOfPoints()<<endl;
    cout<<sphere->GetOutput()->GetNumberOfCells()<<endl;
    actor->SetMapper(mapper);
    actor->Modified();
    double *bounds = actor->GetBounds();
    cout<<bounds[0]<<" "<<bounds[1]<<" "<<bounds[2]<<" "<<bounds[3]<<" "<<bounds[4]<<" "<<bounds[5]<<endl;
    //actor->GetProperty()->SetLineWidth(10.0);
    VTK_SPNew(vtkRenderer, ren);
    VTK_SPNew(vtkRenderWindow, renWin);
    VTK_SPNew(vtkRenderWindowInteractor, iren);
    VTK_SPNew(vtkInteractorStyleTrackballCamera, irenStyle);
    VTK_SP(vtkCamera, renCamera) = ren->GetActiveCamera();
    //renCamera->ParallelProjectionOn();
    ren->AddActor(actor);
    ren->AddActor(actor1);
    renWin->AddRenderer(ren);
    iren->SetRenderWindow(renWin);
    iren->SetInteractorStyle(irenStyle);
    renWin->Render();
    ren->ResetCamera();
    //renCamera->Modified();
    cout<<renCamera->GetPosition()[0]<<" "<<renCamera->GetPosition()[1]<<" "<<renCamera->GetPosition()[2]<<endl;
    cout<<renCamera->GetFocalPoint()[0]<<" "<<renCamera->GetFocalPoint()[1]<<" "<<renCamera->GetFocalPoint()[2]<<endl;
    iren->Initialize();
    iren->Start();
    
	return 0;
}

