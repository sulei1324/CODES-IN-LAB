#include "stdafx.h"
#include <vtkActor.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCollection.h>
#include <vtkRendererCollection.h>
#include <vtkBoxWidget.h>
#include <vtkImageActor.h>
#include <vtkImageData.h>
#include <vtkCommand.h>
#include <vtkImageViewer2.h>
#include <vtkInteractorStyleImage.h>
#include <vtkMath.h>
#include <vtkImageMapToWindowLevelColors.h>
#include <math.h>

class NGInteractorStyleImage: public vtkInteractorStyleImage{
public:
    static NGInteractorStyleImage* New();
    virtual ~NGInteractorStyleImage();
    void SetImageActor(vtkSmartPointer<vtkImageActor> arg){imActor = arg;}
    void SetRenderer(vtkSmartPointer<vtkRenderer> arg){ren = arg;}
protected:
    NGInteractorStyleImage();
    virtual void OnMouseWheelForward();
    virtual void OnMouseWheelBackward();
    virtual void OnLeftButtonDown();
    virtual void OnMouseMove();
    virtual void OnLeftButtonUp();

private:
    vtkSmartPointer<vtkImageActor> imActor;
    vtkSmartPointer<vtkRenderer> ren;
    bool isLeftButtonPressed;
    vtkSmartPointer<vtkImageMapToWindowLevelColors> mwlc;
};