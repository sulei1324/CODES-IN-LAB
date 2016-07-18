#include "twoLayer.h"

void coutDoubleArray(double *a, int n){
    for(int i = 0; i < n; ++i){
        cout<<a[i]<<" ";
    }
    cout<<endl;
}


vtkStandardNewMacro(RenderOneStyle);
RenderOneStyle::RenderOneStyle(){
    drawFlag = false;
    whichLayerRenderInteractive = 0;
}
RenderOneStyle::~RenderOneStyle(){

}

void RenderOneStyle::OnLeftButtonDown(){
    vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
}

void RenderOneStyle::OnLeftButtonUp(){
    vtkInteractorStyleTrackballCamera::OnLeftButtonUp();
}

void RenderOneStyle::OnMouseMove(){
    if(whichLayerRenderInteractive == 0){
        vtkInteractorStyleTrackballCamera::OnMouseMove();
    }else{
        
    }
    
}

void RenderOneStyle::OnMouseWheelForward()
{
    if(whichLayerRenderInteractive == 0){
        vtk_sp(vtkCamera, camera3d) = ren3d->GetActiveCamera();
        camera3d->Zoom(1.1);
        this->GetInteractor()->Render();  
    }
}


void RenderOneStyle::OnMouseWheelBackward()
{
    if(whichLayerRenderInteractive == 0){
        vtk_sp(vtkCamera, camera3d) = ren3d->GetActiveCamera();
        camera3d->Zoom(0.9);
        this->GetInteractor()->Render();  
    }
}

void RenderOneStyle::OnRightButtonDown()
{

}

void RenderOneStyle::OnRightButtonUp()
{

}

void RenderOneStyle::OnChar()
{
    vtk_sp(vtkRenderWindowInteractor, iren) = this->GetInteractor();
    char inputKey = iren->GetKeyCode();
    switch(inputKey){
        case 'c':
        case 'C':
        {
            drawFlag = ! drawFlag;
            if(drawFlag){
                ren3d->SetInteractive(false);
                renImage->SetInteractive(true);
                whichLayerRenderInteractive = 1;
            
            }else{
                ren3d->SetInteractive(true);
                renImage->SetInteractive(false);
                whichLayerRenderInteractive = 0;
            }
            SetRenImageEnabled(drawFlag);
            break;
        
        }
    
    
    }

}


void RenderOneStyle::SetRenImageEnabled(bool arg)
{
    imageActor->SetVisibility(arg);
    if(arg){
        imageTracer->On();
    }else{
        imageTracer->Off();
    }
    this->GetInteractor()->Render();
}

void RenderOneStyle::CreateSphereActors(int num, double bound )
{
    for(int i = 0; i < num; ++i){
        vtk_spnew(vtkActor, actorI);
        vtk_spnew(vtkSphereSource, sourceI);
        vtk_spnew(vtkPolyDataMapper, mapperI);
        sourceI->SetRadius(vtkMath::Random(1, 5));
        sourceI->SetCenter(vtkMath::Random(-bound, bound), vtkMath::Random(-bound, bound), vtkMath::Random(-bound, bound));
        mapperI->SetInput(sourceI->GetOutput());
        actorI->SetMapper(mapperI);
        actorI->GetProperty()->SetColor(vtkMath::Random(0, 1), vtkMath::Random(0, 1), vtkMath::Random(0, 1));
        ren3d->AddActor(actorI);
        areaPicker->AddPickList(actorI);
    }
    
}


WindowModifiedCommand::WindowModifiedCommand()
{
    imageActor = vtk_new(vtkImageActor);
    oldHeight = -1;
    oldWidth = -1;
}

WindowModifiedCommand::~WindowModifiedCommand()
{

}

void WindowModifiedCommand::Execute( vtkObject *caller, unsigned long eventId, void *callData )
{
    vtk_sp(vtkRenderWindow, renWin) = vtkRenderWindow::SafeDownCast(caller);
    int *winSize = renWin->GetSize();
    int winHeight = winSize[1];
    int winWidth = winSize[0];
    if(oldWidth != winWidth || oldHeight != winHeight){
        imageData = vtk_new(vtkImageData);
        vtk_sp(vtkCamera, cameraImage) = renImage->GetActiveCamera();
        imageData->SetDimensions(winWidth, winHeight, 1);
        imageData->SetWholeExtent(0, winWidth - 1, 0, winHeight - 1, 0, 0);
        imageData->SetScalarTypeToUnsignedChar();
        imageData->SetNumberOfScalarComponents(4);
        for(int y = 0; y < winHeight; ++y){
            for(int x = 0; x < winWidth; ++x){
                unsigned char *pixel = reinterpret_cast<unsigned char*>(imageData->GetScalarPointer(x, y, 0));
                if((x > 0 && x < 3) || (y > 0 && y < 3) || (x < winWidth && x > winWidth - 3) || (y < winHeight && y > winHeight - 3)){
                    pixel[0] = 255;
                    pixel[1] = 255;
                    pixel[2] = 0;
                    pixel[3] = 255;
                }else{
                    pixel[0] = 0;
                    pixel[1] = 0;
                    pixel[2] = 0;
                    pixel[3] = 0;
                }
            }
        }
        imageActor->SetInput(imageData);
        imageActor->Modified();
        cameraImage->ParallelProjectionOn();
        cameraImage->SetPosition(winWidth / 2, winHeight / 2, 10);
        cameraImage->SetFocalPoint(winWidth / 2, winHeight / 2, 0);
        cameraImage->SetParallelScale(winHeight / 2);
        cameraImage->SetViewUp(0.0, 1.0, 0.0);
        cameraImage->SetClippingRange(9, 11);
        cameraImage->Modified();
        if(renImage->GetViewProps()->IsItemPresent(imageActor) != 0){
        
        }else{
            renImage->AddActor(imageActor);
        }
        renImage->Render();
        oldHeight = winHeight;
        oldWidth = winWidth;
    }
}

ImageTracerCommand::ImageTracerCommand()
{

}

ImageTracerCommand::~ImageTracerCommand()
{

}

void ImageTracerCommand::Execute( vtkObject *caller, unsigned long eventId, void *callData )
{
    vtk_sp(vtkImageTracerWidget, imageTracer) = vtkImageTracerWidget::SafeDownCast(caller);
    if(eventId == vtkCommand::StartInteractionEvent){
        imageTracer->GetLineProperty()->SetOpacity(255);
        imageTracer->GetHandleProperty()->SetOpacity(255);  
    }else if(eventId == vtkCommand::EndInteractionEvent){
        imageTracer->GetLineProperty()->SetOpacity(0);
        imageTracer->GetHandleProperty()->SetOpacity(0);
        vtk_spnew(vtkPolyData, tracerPoly);
        imageTracer->GetPath(tracerPoly);
        vtkIdType pointNum = tracerPoly->GetPoints()->GetNumberOfPoints();
        vtk_spnew(vtkPoints, areaPoints);
        vtk_sp(vtkPoints, tracerPoints) = tracerPoly->GetPoints();
        vtk_spnew(vtkPolygon, areaPolygon);
        areaPolygon->GetPointIds()->SetNumberOfIds(pointNum);
        for(vtkIdType i = 0; i < pointNum; ++i){
            double p[3];
            tracerPoints->GetPoint(i, p);
            areaPoints->InsertNextPoint(p[0], p[1], 0);
            areaPolygon->GetPoints()->InsertNextPoint(p[0], p[1], 0);
            areaPolygon->GetPointIds()->SetId(i, i);
        }
        areaPolygon->Modified();

        vtk_spnew(vtkCellArray, areaCells);
        vtk_spnew(vtkPolyData, areaPoly);
        areaCells->InsertNextCell(areaPolygon);
        areaPoly->SetPoints(areaPoints);
        areaPoly->SetPolys(areaCells);
        areaPoly->Update();
        areaPolygon->Modified();
        double bounds[6];
        areaPoly->GetBounds(bounds);
        double normal[3];
        areaPolygon->ComputeNormal(areaPolygon->GetPoints()->GetNumberOfPoints(), static_cast<double *>(areaPolygon->GetPoints()->GetData()->GetVoidPointer(0)), normal);
        double boundsPolygon[6];
        areaPolygon->GetBounds(boundsPolygon);
        //coutDoubleArray(boundsPolygon, 6);
        //coutDoubleArray(normal, 3);
        //coutDoubleArray(bounds, 6);
        //vtk_spnew(vtkActor, areaActor);
        //vtk_spnew(vtkPolyDataMapper, areaMapper);
        //areaMapper->SetInput(areaPoly);
        //areaActor->SetMapper(areaMapper);
        //renImage->AddActor(areaActor);
        //renImage->Render();
        areaPicker->AreaPick(bounds[0], bounds[2], bounds[1], bounds[3], ren3d);
        int pickNum = areaPicker->GetProp3Ds()->GetNumberOfItems();
        vtk_spnew(vtkActorCollection, areaActors);
        for(int i = 0; i < pickNum; ++i){
            vtk_sp(vtkActor, actorI) = vtkActor::SafeDownCast(areaPicker->GetProp3Ds()->GetItemAsObject(i));
            double *centerI = actorI->GetCenter();
            ren3d->SetWorldPoint(centerI[0], centerI[1], centerI[2], 1.0);
            ren3d->WorldToDisplay();
            double *displayCenter = ren3d->GetDisplayPoint();
            displayCenter[2] = 0.0;
            //coutDoubleArray(displayCenter, 3);
            int isPointInPolygon = areaPolygon->PointInPolygon(displayCenter, pointNum, static_cast<double *>(areaPolygon->GetPoints()->GetData()->GetVoidPointer(0)), boundsPolygon, normal);
            if(isPointInPolygon > 0){
                ren3d->RemoveActor(actorI);
            }
        }
        ren3d->Render();
        
        
        
        
        
        
        
        
    }
}
