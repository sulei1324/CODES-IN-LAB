#include "stdafx.h"
#include "RenderWidget.h"

void SliderCommand::Execute( vtkObject *caller, unsigned long eventId, void *callData )
{
    vtkSliderWidget *slider = vtkSliderWidget::SafeDownCast(caller);
    cout<<slider->GetSliderRepresentation()->GetTitleText()<<endl;
    cout<<slider->GetSliderRepresentation()->GetValue()<<endl;  
}

SliderCommand::SliderCommand()
{

}

SliderCommand::~SliderCommand()
{

}

