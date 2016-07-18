#include "stdafx.h"
#ifndef MOSTDTRAVELLER_H
#define MOSTDTRAVELLER_H
#include "TestVtkVolume.h"
#include "SwcReader.h"
#include "MostdReader.h"

class MostdTraveller: public vtkInteractorStyleTrackballCamera{
public:
    vtkTypeMacro(MostdTraveller, vtkInteractorStyleTrackballCamera);
    static MostdTraveller *New();
    void SetMostd(Mostd *arg);
    void SetSwc(SwcReader *arg);
    void SetTravelLineIndex(u_int arg){travelLineIndex_ = arg;}
    void SetRenderer(vtk_sp(vtkRenderer, arg));
    void SetBitNum(u_int arg){bitNum_ = arg;}
    void SamplePoints(vLine &arg, double step);
    void SetResolution(vector<float> &arg){resolution_ = arg;}
    bool GetCaremaPosition(double focalPoint[3], double lastFocalPoint[3], double cameraPosition[3]);
    bool GetViewUp(double focalPoint[3], double lastFocalPoint[3], double viewUp[3]);
    bool GetClipRange(double cameraPostion[3], double focalPoint[3], double *clipRange);
    virtual void OnKeyPress();
    virtual void OnLeftButtonDown();
    virtual void OnLeftButtonUp();
    virtual void OnMouseWheelForward();
    virtual void OnMouseWheelBackward();
    virtual void OnChar();
    virtual void OnMouseMove();
    
    
    
protected:
    MostdTraveller();
    ~MostdTraveller();
        
private:
    void CalcuForwardCameraPosition(double position[3], double focal[3], double step);
    void CalcuLeftCameraPosition(double up[3], double position[3], double focal[3], double step);
    void cameraMoveForward(double step);
    void cameraMoveLeftRight(double step);
    bool testMode_;
    bool isLeftMouseDown;
    MostdTraveller(const MostdTraveller &);
    void operator=(const MostdTraveller &);    
    Mostd *mostd_;
    SwcReader *swc_;
    bool isInTravelMode_;
    bool isInited_;
    bool toggleCamera_;
    u_int wholePointNum_;
    u_int curPointIndex_;
    u_int travelLineIndex_;
    u_int bitNum_;
    double distanceFromFocal2Camera;
    double clipHalfDistance;
    double cameraAngel;
    double step_;
    double moveVelocity_;
    int *oldMousePoint_;
    vLine travelLine_;
    vLine usedLine_;
    vPoint oldPoint_;
    vtk_sp(vtkActor, lineActor_);
    vtk_sp(vtkRenderer, ren_);
    vtk_sp(vtkVolume, vol_);
    vtk_sp(vtkActor, outline_);
    vtk_sp(vtkCameraActor, testActor_);
    vector<float> resolution_;
    vtk_sp(vtkPoints, rawPoints_);
    vtk_sp(vtkPoints, usedPoints_);
    vtk_sp(vtkCamera, testCamera_);
    
    
    
    

};






#endif