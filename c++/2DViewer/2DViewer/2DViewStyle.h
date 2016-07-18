#include "stdafx.h"
#ifndef TWO_DVIEWSTYLE_H
#define TWO_DVIEWSTYLE_H
#include "TestVtkVolume.h"

void coutDoubleArray(double *a, int n);

class TwoDViewStyle: public vtkInteractorStyleTrackballCamera{
public:
    vtkTypeMacro(TwoDViewStyle, vtkInteractorStyleTrackballCamera);
    static TwoDViewStyle *New();
    virtual void OnChar();
    virtual void OnLeftButtonDown();
    virtual void OnLeftButtonUp();
    virtual void OnRightButtonDown();
    virtual void OnRightButtonUp();
    virtual void OnMiddleButtonDown();
    virtual void OnMiddleButtonUp();
    virtual void OnMouseWheelForward();
    virtual void OnMouseWheelBackward();
    virtual void OnMouseMove();
    virtual void OnKeyPress();
    void SetRenderer(vtk_sp(vtkRenderer, arg)){ren = arg; threeDCamera = ren->GetActiveCamera();}
    void SetRendererBack(vtk_sp(vtkRenderer, arg)){renBack = arg;}
    void SetImageBlock(u_int xBeg, u_int xEnd, u_int yBeg, u_int yEnd, u_int zBeg, u_int zEnd);
    void SetImageBlock(u_int arg[6]);
    void Set2dCamera();
    
        
    
protected:
    TwoDViewStyle();
    ~TwoDViewStyle();
    
    
private:
    TwoDViewStyle(const TwoDViewStyle &);
    void operator=(const TwoDViewStyle &);        
    vtk_sp(vtkRenderer, renBack);
    vtk_sp(vtkRenderer, ren);
    vtk_sp(vtkCamera, twoDCamera);
    vtk_sp(vtkCamera, threeDCamera);
    vtk_sp(vtkTransform, sliceTransform);
    vtk_sp(vtkActor, sliceOutlineActor);
    vtk_sp(vtkActor, drawLineActor);
    vtk_sp(vtkActor, drawVertActor);
    bool is2DView;
    bool isIn2dZoomMode;
    bool isIn2dMoveMode;
    bool isInDrawMode;
    bool isDrawHasStartPoint;
    double *drawOldPoint;
    u_int *block;
    double dFromCamera2BlockEnd;
    double clippingDistance;
    double parallelScale;
    double zoomRatio;
    double moveStep;
    double rangeStep;
    
    
    
    
};


#endif