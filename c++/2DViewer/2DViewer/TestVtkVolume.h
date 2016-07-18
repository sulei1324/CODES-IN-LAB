#include "stdafx.h"
#ifndef TESTVTKVOLUME_H
#define TESTVTKVOLUME_H
#include <vtkAppendPolyData.h>
#include <vtkOutlineSource.h>
#include <vtkImageDataGeometryFilter.h>
#include <vtkImageActor.h>
#include <vtkImageData.h>
#include <vtkObject.h>
#include <vtkObjectFactory.h>
#include <vtkVolume.h>
#include <vtkVolumeMapper.h>
#include <vtkCamera.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkPiecewiseFunction.h>
#include <vtkVolumeProperty.h>
#include <vtkSmartPointer.h>
#include <vtkImageImport.h>
#include <vtkSmartVolumeMapper.h>
#include <vtkColorTransferFunction.h>
#include <vtkPiecewiseFunction.h>
#include <vtkOutlineFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkTransformFilter.h>
#include <vtkTransform.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkCamera.h>
#include <vtkActorCollection.h>
#include <vtkMath.h>
#include <vtkCellArray.h>
#include <vtkPoints.h>
#include <vtkProperty.h>
#define vtk_sp(type, arg) vtkSmartPointer<type> arg
#define vtk_spnew(type, arg) vtkSmartPointer<type> arg = vtkSmartPointer<type>::New()
#define vtk_new(type) vtkSmartPointer<type>::New()
typedef unsigned char   u_char;
typedef unsigned short  u_short;
typedef unsigned int    u_int;
typedef unsigned long   u_long;

class TestVtkVolume{
public:
    TestVtkVolume();
    ~TestVtkVolume();
    void SetImages(u_char *arg, u_int imageSize[3]);
    void SetImages(u_short *arg,  u_int imageSize[3]);
    void SetResolution(vector<float>& arg){resolution = arg;}
    bool Update();
    vtkSmartPointer<vtkVolume> GetOutput(){return volume;}
    vtkSmartPointer<vtkActor> GetOutline(){return outlineActor;}


private:
    u_char *images8;
    u_short *images16;
    u_int bitsNum;
    u_int width;
    u_int height;
    u_int thick;
    bool isInited;
    vector<float> resolution;
    vtk_sp(vtkVolume, volume);
    vtk_sp(vtkImageImport, importer);
    vtk_sp(vtkSmartVolumeMapper, volMapper);
    vtk_sp(vtkVolumeProperty, volProperty);
    vtk_sp(vtkColorTransferFunction, colorTrans);
    vtk_sp(vtkPiecewiseFunction, opacTrans);
    vtk_sp(vtkActor, outlineActor);
    vtk_sp(vtkOutlineFilter, outlineFilter);
    vtk_sp(vtkPolyDataMapper, outlineMapper);
     
};

#endif