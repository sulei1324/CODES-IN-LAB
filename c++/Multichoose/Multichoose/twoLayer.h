#ifndef TWOLAYER_H
#define TWOLAYER_H
#include "TestStyle.h"
#include <vtkInteractorStyle.h>
#include <vtkInteractorStyleUser.h>
#include <vtkInteractorObserver.h>
#include <vtkCamera.h>
#include <vtkProp.h>
#include <vtkProp3D.h>
#include <vtkPolyDataToImageStencil.h>
#include <vtkImageStencil.h>
#include <vtkTIFFWriter.h>
#include <vtkPolygon.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkAxesActor.h>

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
    void SetRenImageEnabled(bool arg);
    void SetImageActor(vtk_sp(vtkImageActor, arg)){imageActor = arg;}
    void CreateSphereActors(int num, double bound);
    void SetAreaPicker(vtk_sp(vtkAreaPicker, arg)){areaPicker = arg;}
    
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
    vtk_sp(vtkAreaPicker, areaPicker);
    // 0 for 3d, 1 for image, 0 is inner, 1 is outer
    int whichLayerRenderInteractive;
};



class WindowModifiedCommand: public vtkCommand{
public:
    vtkTypeMacro(WindowModifiedCommand, vtkCommand);
    static WindowModifiedCommand *New(){return new WindowModifiedCommand;}
    void Execute(vtkObject *caller, unsigned long eventId, void *callData);
    void SetImageRenderer(vtk_sp(vtkRenderer, arg)){renImage = arg;}
    vtk_sp(vtkImageActor) GetImageActor(){return imageActor;}
    
protected:
    WindowModifiedCommand();
    ~WindowModifiedCommand();

private:
    WindowModifiedCommand(const WindowModifiedCommand &);
    void operator=(const WindowModifiedCommand &);
    vtk_sp(vtkRenderer, renImage);
    vtk_sp(vtkImageActor, imageActor);
    vtk_sp(vtkImageData, imageData);
    int oldWidth, oldHeight;
};


class ImageTracerCommand: public vtkCommand{
public:
    vtkTypeMacro(ImageTracerCommand, vtkCommand);
    static ImageTracerCommand *New(){return new ImageTracerCommand;}
    void Execute(vtkObject *caller, unsigned long eventId, void *callData);
    void SetWindow(vtk_sp(vtkRenderWindow, arg)){renWin = arg;}
    void SetImageRenderer(vtk_sp(vtkRenderer, arg)){renImage = arg;}
    void SetAreaPicker(vtk_sp(vtkAreaPicker, arg)){areaPicker = arg;}
    void Set3dRender(vtk_sp(vtkRenderer, arg)){ren3d = arg;}

protected:
    ImageTracerCommand();
    ~ImageTracerCommand();

private:
    ImageTracerCommand(const ImageTracerCommand &);
    void operator=(const ImageTracerCommand &);
    vtk_sp(vtkRenderWindow, renWin);
    vtk_sp(vtkRenderer, renImage);
    vtk_sp(vtkRenderer, ren3d);
    vtk_sp(vtkAreaPicker, areaPicker);
};
#endif
