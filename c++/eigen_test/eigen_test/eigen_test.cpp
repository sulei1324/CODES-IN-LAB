// eigen_test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Eigen/Dense>
#include <Eigen/Core>
#include <iostream>
#include "test.h"   
#include "math.h"
typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> MatrixXdR1C2;
using namespace std;
double round(double &x){
    if(floor(x + 0.5) > floor(x)){
        return ceil(x);
    }else{
        return floor(x);
    }
}

int main()
{
    vtkSmartPointer<vtkMath> ma1 = vtkSmartPointer<vtkMath>::New();
    vtkSmartPointer<vtkImageData> id1 = vtkSmartPointer<vtkImageData>::New();
    id1->SetNumberOfScalarComponents(1);
    id1->SetScalarTypeToUnsignedChar();
    id1->SetDimensions(50, 50, 50);
    id1->Update();
    int* dims = id1->GetDimensions();
    for(int i = 0; i < dims[2]; i++){
        for(int j = 0; j < dims[1]; j++){
            for(int k = 0; k < dims[0]; k++){
                unsigned char* pixel = static_cast<unsigned char*>(id1->GetScalarPointer(k, j, i));
                pixel[0] = static_cast<int>(ma1->Random(0, 50));
                if(j == i || j == i + 1 || j == i + 2){
                    pixel[0] = 0;
                }  
            } 
        }
    }
    double* scalar_range = id1->GetScalarRange();
    double max_scalar = id1->GetScalarRange()[1];
    double min_scalar = id1->GetScalarRange()[0];
    vtkSmartPointer<vtkImageMapToWindowLevelColors> im2wlm  = vtkSmartPointer<vtkImageMapToWindowLevelColors>::New();
    im2wlm->SetLevel((min_scalar + (max_scalar - min_scalar) / 2));
    im2wlm->SetWindow(max_scalar - min_scalar);
    im2wlm->SetInput(id1);
    cout<<(min_scalar + (max_scalar - min_scalar) / 2)<<" "<<(max_scalar - min_scalar)<<endl;
    cout<<max_scalar<<" "<<min_scalar<<endl;
    vtkImageData *id2 = vtkImageData::SafeDownCast(im2wlm->GetOutput());
    cout<<id2->GetScalarTypeMin()<<endl;
    
    
    
    vtkSmartPointer<vtkImageActor> imActor1 = vtkSmartPointer<vtkImageActor>::New();
    
    imActor1->SetInput(im2wlm->GetOutput()); 
    double* ex1 = imActor1->GetBounds();
    cout<<ex1[0]<<" "<<ex1[1]<<" "<<ex1[2]<<" "<<ex1[3]<<" "<<ex1[4]<<" "<<ex1[5]<<" "<<endl;
    imActor1->SetDisplayExtent(0, 49, 0, 49, 25, 25);
    //imActor1->SetZSlice(25);
    cout<<imActor1->GetZSlice()<<endl;
    cout<<ex1[4]<<" "<<ex1[5]<<endl;
    vtkSmartPointer<vtkRenderer> r1 = vtkSmartPointer<vtkRenderer>::New();
    r1->AddActor(imActor1);
    vtkSmartPointer<NGInteractorStyleImage> s1 = vtkSmartPointer<NGInteractorStyleImage>::New();
    s1->SetImageActor(imActor1);
    s1->SetRenderer(r1);
    cout<<abs(1.7 -8)<<endl;
    //vtkSmartPointer<vtkImageViewer2> view1 = vtkSmartPointer<vtkImageViewer2>::New();
    //view1->SetInput(id1);
    //view1->SetupInteractor(i1);
    //view1->SetSlice(25);
    //view1->Render();
    vtkSmartPointer<vtkRenderWindowInteractor> i1 = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    vtkSmartPointer<vtkRenderWindow> w1 = vtkSmartPointer<vtkRenderWindow>::New();
    i1->SetRenderWindow(w1);
    i1->SetInteractorStyle(s1);
    w1->AddRenderer(r1);
    i1->Initialize();
    i1->Start();
    
}

