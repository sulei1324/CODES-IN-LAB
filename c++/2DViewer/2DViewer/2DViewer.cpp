// 2DViewer.cpp : 定义控制台应用程序的入口点。
/********************************************************************
	created:	2016/06/24
	created:	24:6:2016   9:12
	filename: 	g:\sulei\workplace\c++\2DViewer\2DViewer\2DViewer.cpp
	file path:	g:\sulei\workplace\c++\2DViewer\2DViewer
	file base:	2DViewer
	file ext:	cpp
	author:		Su Lei
	
	purpose:	toggle 2d view and 3d view, and achieve some edit operations in 2d view
*********************************************************************/
#include "stdafx.h"
#include "SwcReader.h"
#include "MostdReader.h"
#include "TestVtkVolume.h"
#include "2DViewStyle.h"




int _tmain(int argc, _TCHAR* argv[])
{
    vtk_spnew(vtkRenderer, ren);
    vtk_spnew(vtkRenderWindow, renWin);
    vtk_spnew(vtkRenderWindowInteractor, iren);
    vtk_spnew(TwoDViewStyle, twoDStyle);
    vtk_spnew(vtkTransform, transformForVolume);
    vtk_spnew(vtkInteractorStyleTrackballCamera, irenStyle);
    vtk_spnew(vtkRenderer, renBack);
    
    
    vtk_sp(vtkCamera, camera);
    vtk_sp(vtkVolume, volume);
    vtk_sp(vtkActor, outlineActor);
    renWin->SetNumberOfLayers(2);
    renWin->AddRenderer(ren);
    renWin->AddRenderer(renBack);
    ren->SetLayer(1);
    renBack->SetLayer(0);
    twoDStyle->SetRenderer(ren);
    twoDStyle->SetRendererBack(renBack);
    iren->SetRenderWindow(renWin);
    iren->SetInteractorStyle(twoDStyle);


    SwcReader swc;
    double ratio = 0.3;
    swc.SetInputName("test1.swc");
    if(swc.Update()){
        swc.BuildActors(renBack, ratio);
    }else{
        return -1;
    }


    TestVtkVolume volumeWarpper;   
    vLines& lines = swc.GetOutput();
    vLine firstLine = lines.at(0);
    vPoint firstPoint = firstLine.at(0);



    Mostd mostd("TDI072.mostd", 8);
    u_int xBeg = static_cast<u_int>(firstPoint(1)  / ratio) - 200;
    u_int xEnd = xBeg + 400;
    u_int yBeg = static_cast<u_int>(firstPoint(2) / ratio) - 200;
    u_int yEnd = yBeg+ 400;
    u_int zBeg = firstPoint(3) - 100;
    u_int zEnd = zBeg + 200;
    u_int width = xEnd - xBeg + 1;
    u_int height = yEnd - yBeg + 1;
    u_int thick = zEnd - zBeg + 1;
    cout<<xBeg<<" "<<xEnd<<" "<<yBeg<<" "<<yEnd<<" "<<zBeg<<" "<<zEnd<<endl;
    u_int imagesSize[3] = {width, height, thick};
    twoDStyle->SetImageBlock(xBeg, xEnd, yBeg, yEnd, zBeg, zEnd);


    if(mostd.loadMostd() && mostd.setROI(xBeg, xEnd, yBeg, yEnd, zBeg, zEnd)){
        if(mostd.loadImages()){
            vector<float>& resolution = mostd.GetResolution();

            volumeWarpper.SetImages(mostd.GetImageData8(), imagesSize);
            volumeWarpper.SetResolution(resolution);
            if(volumeWarpper.Update()){
                volume = volumeWarpper.GetOutput();
                outlineActor = volumeWarpper.GetOutline();
            }
            //mostd.showImages();
        }
    }else{
        return -1;
    }




    transformForVolume->Translate(xBeg, yBeg, zBeg);
    volume->SetUserTransform(transformForVolume);
    outlineActor->SetUserTransform(transformForVolume);
    ren->AddActor(volume);
    ren->AddActor(outlineActor);
    renWin->PointSmoothingOn();

    //renBack->SetBackground(0.2, 0.0, 0.0);
    ren->SetInteractive(true);
    renBack->SetInteractive(false);
    ren->ResetCamera();
    camera = ren->GetActiveCamera();
    renBack->SetActiveCamera(camera);
    camera->SetParallelProjection(true);
    cout<<camera->GetParallelScale()<<endl;


    renWin->Render();
    iren->Initialize();
    iren->Start();

    return 0;
}

