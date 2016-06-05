#ifndef TWOLAYER_H
#define TWOLAYER_H
#include "TestStyle.h"
#include <vtkInteractorStyle.h>
#include <vtkInteractorStyleUser.h>
#include <vtkInteractorObserver.h>
#include <vtkCamera.h>

void coutDoubleArray(double *a, int n);

class RenderOneStyle: public vtkInteractorStyleTrackballCamera{
public:
    vtkTypeMacro(RenderOneStyle, vtkInteractorStyleTrackballCamera);
    static RenderOneStyle *New();
    virtual void OnLeftButtonDown();
    virtual void OnMouseMove();
    virtual void OnLeftButtonUp();
    virtual void OnMouseWheelForward();
    virtual void OnMouseWheelBackward();
    virtual void OnRightButtonDown();
    virtual void OnRightButtonUp();
    virtual void OnChar();
    void SetRenderImage(vtkSmartPointer<vtkRenderer> arg){renImage = arg;}
    void SetRender3d(vtkSmartPointer<vtkRenderer> arg){ren3d  = arg;}
    void SetImageTracer(vtk_sp(vtkImageTracerWidget, arg)){imageTracer = arg;}
    void SetupImageData();
    void SetRenImageEnabled(bool arg);
    vtkSmartPointer<vtkImageActor> GetImageActor(){return imageActor;}
    
protected:
    RenderOneStyle();
    ~RenderOneStyle();


private:
    RenderOneStyle(const RenderOneStyle &);
    void operator=(const RenderOneStyle &);
    bool drawFlag;
    vtkSmartPointer<vtkRenderer> renImage;
    vtkSmartPointer<vtkRenderer> ren3d;
    vtkSmartPointer<vtkImageActor> imageActor;
    vtk_sp(vtkImageTracerWidget, imageTracer);
    vtk_sp(vtkImageData, imageData);
    // 0 for 3d, 1 for image, 0 is inner, 1 is outer
    int whichLayerRenderInteractive;
};



class WindowModifiedCommand: public vtkCommand{
public:
    vtkTypeMacro(WindowModifiedCommand, vtkCommand);
    static WindowModifiedCommand *New(){return new WindowModifiedCommand;}
    void Execute(vtkObject *caller, unsigned long eventId, void *callData);
    
protected:
    WindowModifiedCommand();
    ~WindowModifiedCommand();

private:
    WindowModifiedCommand(const WindowModifiedCommand &);
    void operator=(const WindowModifiedCommand &);
};
#endif
