// MultiWidget.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "vtkOrientationMarkerWidget.h"
#include "vtkSmartPointer.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkSphereSource.h"
#include "vtkActor.h"
#include "vtkPolyDataMapper.h"
#include "vtkProperty.h"
#include "vtkAxesActor.h"
#include "vtkImageTracerWidget.h"
#include "vtkObject.h"
#include "vtkCallbackCommand.h"
#define vtk_sp(type, arg) vtkSmartPointer<type> arg
#define vtk_spnew(type, arg) vtkSmartPointer<type> arg = vtkSmartPointer<type>::New()
#define vtk_new(type) vtkSmartPointer<type>::New()


void fun1(vtkObject *caller, unsigned long eventId, void *clientData, void *callData){
    vtk_sp(vtkImageTracerWidget, tracer) = vtkImageTracerWidget::SafeDownCast(caller);
    cout<<"eeee"<<endl;




}




int main()
{
	vtk_spnew(vtkRenderer, ren);
	vtk_spnew(vtkRenderWindow, renWin);
	vtk_spnew(vtkRenderWindowInteractor, iren);
	vtk_spnew(vtkInteractorStyleTrackballCamera, cameraStyle);
	vtk_spnew(vtkActor, actor);
	vtk_spnew(vtkPolyDataMapper, mapper);
	vtk_spnew(vtkSphereSource, source);
	vtk_spnew(vtkOrientationMarkerWidget, marker);
	vtk_spnew(vtkAxesActor, axes);
	vtk_spnew(vtkImageTracerWidget, tracer);
	vtk_spnew(vtkCallbackCommand, com);
	source->SetRadius(10.0);
	mapper->SetInput(source->GetOutput());
	actor->SetMapper(mapper);
	ren->AddActor(actor);
    
	
	
	
	renWin->AddRenderer(ren);
	iren->SetRenderWindow(renWin);
	iren->SetInteractorStyle(cameraStyle);
	tracer->SetInteractor(iren);
	tracer->SetViewProp(actor);
	com->SetCallback(fun1);
    tracer->AddObserver(vtkCommand::StartInteractionEvent, com);
    tracer->AddObserver(vtkCommand::EndInteractionEvent, com);
	
	
	
	
    marker->SetInteractor(iren);
    marker->SetOrientationMarker(axes);
    marker->SetEnabled(1);
    marker->SetInteractive(true);
    tracer->On();
	renWin->Render();
	iren->Initialize();
	iren->Start();
	
	
	
	
	
	
}

