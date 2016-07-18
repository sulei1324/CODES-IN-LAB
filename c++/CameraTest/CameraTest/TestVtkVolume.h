#include "stdafx.h"
#ifndef TESTVTKVOLUME_H
#define TESTVTKVOLUME_H

#define vtk_sp(type, arg) vtkSmartPointer<type> arg
#define vtk_spnew(type, arg) vtkSmartPointer<type> arg = vtkSmartPointer<type>::New()
#define vtk_new(type) vtkSmartPointer<type>::New()
typedef unsigned char   u_char;
typedef unsigned short  u_short;
typedef unsigned int    u_int;
typedef unsigned long   u_long;


void coutDoubleArray(double *a, int n);

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