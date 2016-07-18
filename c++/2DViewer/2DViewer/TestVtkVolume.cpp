#include "stdafx.h"
#include "TestVtkVolume.h"

TestVtkVolume::TestVtkVolume():
    images8(0),
    images16(0),
    bitsNum(0),
    isInited(false)
{
    
}

TestVtkVolume::~TestVtkVolume()
{

}

void TestVtkVolume::SetImages( u_char *arg, u_int imageSize[3] )
{
    bitsNum = 8;
    images8 = arg;
    images16 = 0;
    isInited = true;
    width = imageSize[0];
    height = imageSize[1];
    thick = imageSize[2];
    
    
    
}

void TestVtkVolume::SetImages( u_short *arg, u_int imageSize[3] )
{
    bitsNum = 16;
    images16 = arg;
    images8 = 0;
    isInited = true;
    width = imageSize[0];
    height = imageSize[1];
    thick = imageSize[2];
}

bool TestVtkVolume::Update()
{
    if(isInited){
        importer = vtk_new(vtkImageImport);
        if(bitsNum = 8){
            importer->SetDataScalarTypeToUnsignedChar();
            importer->SetNumberOfScalarComponents(1);
            importer->SetWholeExtent(0, width - 1, 0, height - 1, 0, thick - 1);
            importer->SetDataExtent(0, width - 1, 0, height - 1, 0, thick - 1);
            importer->CopyImportVoidPointer(images8, width * height * thick);
            //importer->SetDataSpacing(resolution.at(0), resolution.at(1), resolution.at(2));
        }else if(bitsNum == 16){
            importer->SetDataScalarTypeToUnsignedShort();
            importer->SetNumberOfScalarComponents(1);
            importer->SetWholeExtent(0, width - 1, 0, height - 1, 0, thick - 1);
            importer->SetDataExtentToWholeExtent();
            importer->CopyImportVoidPointer(images16, width * height * thick);
            //importer->SetDataSpacing(resolution.at(0), resolution.at(1), resolution.at(2));
        }
        volume = vtk_new(vtkVolume);
        volMapper = vtk_new(vtkSmartVolumeMapper);
        volMapper->SetBlendModeToMaximumIntensity();
        colorTrans = vtk_new(vtkColorTransferFunction);
        colorTrans->AddRGBPoint(0.0, 0.0, 0.0, 0.0);
        colorTrans->AddRGBPoint(60.0, 1.0, 1.0, 1.0);
        opacTrans = vtk_new(vtkPiecewiseFunction);
        opacTrans->AddPoint(0.0, 0.0);
        opacTrans->AddPoint(255.0, 1.0);
        opacTrans->ClampingOff();
        volProperty = vtk_new(vtkVolumeProperty);
        volProperty->SetColor(colorTrans);
        volProperty->SetScalarOpacity(opacTrans);
        volProperty->ShadeOn();
        volProperty->SetAmbient(0.1);
        volProperty->SetDiffuse(0.9);
        volProperty->SetSpecular(0.2);
        volProperty->SetSpecularPower(10);
        volProperty->SetInterpolationTypeToLinear();
        volMapper->SetInput(importer->GetOutput());
        volume->SetMapper(volMapper);
        volume->SetProperty(volProperty);
        outlineFilter = vtk_new(vtkOutlineFilter);
        outlineMapper = vtk_new(vtkPolyDataMapper);
        outlineActor = vtk_new(vtkActor);
        
        
        
        outlineFilter->SetInputConnection(importer->GetOutputPort());
        outlineMapper->SetInputConnection(outlineFilter->GetOutputPort());
        outlineActor->SetMapper(outlineMapper);
        outlineActor->GetProperty()->SetColor(1.0, 1.0, 0);
        
        
        
        
        
        
        return true;
    }else{
        return false;
    }
}

