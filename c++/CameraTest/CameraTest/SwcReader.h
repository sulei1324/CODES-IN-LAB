#include "stdafx.h"
#ifndef SWCREADER_H
#define SWCREADER_H
#include "TestVtkVolume.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>
#include <Eigen/Core>
#include <Eigen/Dense>
using std::string;
using std::vector;
typedef Eigen::Matrix<int, 1, 5> vec5i;
typedef Eigen::Matrix<int, 1, 7> vec7i;
#define vLine vector<vec5i>
#define vLines vector<vLine>
#define v7iSwc vector<vec7i>
#define vPoint vec5i

class SwcReader{
public:
    SwcReader();
    ~SwcReader();
    void SetInputName(const string &arg);
    bool Update();
    vLines& GetOutput();
    void PrintLines();
    //void SetRenderer(vtk_sp(vtkRenderer, arg)){ren = arg;}
    bool BuildActors(vtk_sp(vtkRenderer, arg), double ratio);
    
    
private:
    vtk_sp(vtkRenderer, ren);
    string swcName;
    vLines lines;
    bool isInit;
    bool isUpdated;
    vtk_sp(vtkActorCollection, lineActors);
    vtk_sp(vtkActorCollection, vertActors);
};


#endif
