#include "stdafx.h"
#include "2DViewStyle.h"


void coutDoubleArray(double *a, int n){
    for(int i = 0; i < n; ++i){
        cout<<a[i]<<" ";
    }
    cout<<endl;
}


vtkStandardNewMacro(TwoDViewStyle);
TwoDViewStyle::TwoDViewStyle():
    block(0),
    drawOldPoint(0)
{
    is2DView = false;
    isIn2dZoomMode = false;
    isIn2dMoveMode = false;
    isInDrawMode = false;
    isDrawHasStartPoint = false;
    clippingDistance = 1;
    dFromCamera2BlockEnd = 1000;
    parallelScale = 0;
    zoomRatio = 0.9;
    moveStep = 5.0;
    rangeStep = 2.0;
    sliceOutlineActor = vtk_new(vtkActor);
    twoDCamera = vtk_new(vtkCamera);
    twoDCamera->SetParallelProjection(true);
    
} 


TwoDViewStyle::~TwoDViewStyle()
{
    if(block){
        delete []block;
    }
    if(drawOldPoint){
        delete []drawOldPoint;
    }
}



void TwoDViewStyle::OnChar(){
    char key = this->GetInteractor()->GetKeyCode();   
    switch(key){
        case '2':
        {
            is2DView = ! is2DView;
            if(is2DView){
                if(block){
                    ren->SetActiveCamera(twoDCamera);
                    renBack->SetActiveCamera(twoDCamera);    
                    Set2dCamera();
                    ren->AddActor(sliceOutlineActor);
                    this->GetInteractor()->Render();       
                }else{
                    is2DView = false;
                }


            }else{
                ren->SetActiveCamera(threeDCamera);
                renBack->SetActiveCamera(threeDCamera);
                ren->RemoveActor(sliceOutlineActor);
                ren->Render();
                GetInteractor()->Render();
            }
            break;
        }
        
        case 'p':
        case 'P':
        {
            if(is2DView){
                isInDrawMode = !isInDrawMode;
                if(isInDrawMode){
                    drawLineActor = vtk_new(vtkActor);
                    drawVertActor = vtk_new(vtkActor);
                    drawVertActor->GetProperty()->SetPointSize(4.0);
                    drawVertActor->GetProperty()->SetColor(0.0, 1.0, 0.0);
                    drawLineActor->GetProperty()->SetLineWidth(3.0);
                    drawLineActor->GetProperty()->SetColor(1.0, 1.0, 0.0);
                    renBack->AddActor(drawLineActor);
                    renBack->AddActor(drawVertActor);
                }else{
                    isDrawHasStartPoint = false;
                }
            }
            break;
        }
        
        
        case 's':
        case 'S':
        {
            if(isIn2dZoomMode){
                double curParallelScale = twoDCamera->GetParallelScale();
                curParallelScale /= zoomRatio;
                if(curParallelScale > 2000){
                    cout<<"Can not be smaller!"<<endl;
                }else{
                    twoDCamera->SetParallelScale(curParallelScale);
                    this->GetInteractor()->Render();
                }
            }else if(isIn2dMoveMode){
                double cameraPostion[3];
                double focalPoint[3];
                twoDCamera->GetFocalPoint(focalPoint);
                twoDCamera->GetPosition(cameraPostion);
                cameraPostion[1] = cameraPostion[1] + moveStep;
                focalPoint[1] = focalPoint[1] + moveStep;
                twoDCamera->SetFocalPoint(focalPoint);
                twoDCamera->SetPosition(cameraPostion);
                coutDoubleArray(cameraPostion, 3);
                
                
                
                twoDCamera->Modified();
                this->GetInteractor()->Render();
            }
            break;
        }

        case 'w':
        case 'W':
        {
            if(isIn2dZoomMode){
                double curParallelScale = twoDCamera->GetParallelScale();
                curParallelScale *= zoomRatio;
                if(curParallelScale < 1){
                    cout<<"Can not be larger!"<<endl;
                }else{
                    twoDCamera->SetParallelScale(curParallelScale);
                    this->GetInteractor()->Render();
                }
            }else if(isIn2dMoveMode){
                double cameraPostion[3];
                double focalPoint[3];
                twoDCamera->GetFocalPoint(focalPoint);
                twoDCamera->GetPosition(cameraPostion);
                cameraPostion[1] = cameraPostion[1] - moveStep;
                twoDCamera->SetPosition(cameraPostion);
                focalPoint[1] = focalPoint[1] - moveStep;
                twoDCamera->SetFocalPoint(focalPoint);
                coutDoubleArray(cameraPostion, 3);
                twoDCamera->Modified();
                this->GetInteractor()->Render();
            }
            break;
        }

        case 'a':
        case 'A':
        {
            if(isIn2dMoveMode){
                double cameraPostion[3];
                double focalPoint[3];
                twoDCamera->GetFocalPoint(focalPoint);
                twoDCamera->GetPosition(cameraPostion);
                cameraPostion[0] = cameraPostion[0] + moveStep;
                twoDCamera->SetPosition(cameraPostion);
                focalPoint[0] = focalPoint[0] + moveStep;
                twoDCamera->SetFocalPoint(focalPoint);
                coutDoubleArray(cameraPostion, 3);
                twoDCamera->Modified();
                this->GetInteractor()->Render();
            }
            break;
        }

        case 'd':
        case 'D':
        {
            if(isIn2dMoveMode){
                double cameraPostion[3];
                double focalPoint[3];
                twoDCamera->GetFocalPoint(focalPoint);
                twoDCamera->GetPosition(cameraPostion);
                cameraPostion[0] = cameraPostion[0] - moveStep;
                twoDCamera->SetPosition(cameraPostion);
                focalPoint[0] = focalPoint[0] - moveStep;
                twoDCamera->SetFocalPoint(focalPoint);
                coutDoubleArray(cameraPostion, 3);
                twoDCamera->Modified();
                this->GetInteractor()->Render();
            }
            break;
        }
        
        case '+':
        {
            if(is2DView){
                clippingDistance += rangeStep;
                double clippingRange[2];
                twoDCamera->GetClippingRange(clippingRange);
                clippingRange[0] = clippingRange[0] - rangeStep / 2;
                clippingRange[1] = clippingRange[1] + rangeStep / 2;
                twoDCamera->SetClippingRange(clippingRange);
                this->GetInteractor()->Render();
                
                
                
            }
            break;
        }
        
        case '-':
        {
            if(is2DView){
                double clippingRange[2];
                twoDCamera->GetClippingRange(clippingRange);
                if(clippingDistance > 1.0){
                    clippingDistance -= rangeStep;
                    clippingRange[0] = clippingRange[0] + rangeStep / 2;
                    clippingRange[1] = clippingRange[1] - rangeStep / 2;
                    twoDCamera->SetClippingRange(clippingRange);
                    this->GetInteractor()->Render();
                }

            }
            break;
        }
        


    }



}








void TwoDViewStyle::OnMouseWheelForward()
{
    if(is2DView){
        u_int xBeg = block[0], xEnd = block[1], yBeg = block[2], yEnd = block[3], zBeg = block[4], zEnd = block[5];
        double cameraPostion = zEnd + dFromCamera2BlockEnd;
        vtk_sp(vtkCamera, camera) = ren->GetActiveCamera();
        double position[3];
        double focalPoint[3];
        double clippingRange[2];
        camera->GetPosition(position);
        camera->GetFocalPoint(focalPoint);
        camera->GetClippingRange(clippingRange);
        double distance = camera->GetDistance();
        double clipStart = clippingRange[0];
        double clipEnd = clippingRange[1];
        if(clipEnd > dFromCamera2BlockEnd + zEnd - zBeg){
            cout<<"The end"<<endl;
        }else{
            clipStart += clippingDistance;
            clipEnd = clipStart + clippingDistance;
            
            double focalPointZ = cameraPostion - (clipStart + clipEnd) / 2;
            camera->SetClippingRange(clipStart, clipEnd);
            twoDCamera->SetFocalPoint(focalPoint[0], focalPoint[1], focalPointZ);
            camera->Modified();
            sliceTransform->Translate(0, 0, -clippingDistance);
            sliceTransform->Update();
            sliceOutlineActor->Modified();
            //double *zRange = sliceOutlineActor->GetZRange();
            //double *actorPostion = sliceOutlineActor->GetCenter();
            //coutDoubleArray(zRange, 2);
            
            
            //camera->GetPosition(position);
            //camera->GetFocalPoint(focalPoint);
            //camera->GetClippingRange(clippingRange);
            //coutDoubleArray(position, 3);
            //coutDoubleArray(focalPoint, 3);
            //coutDoubleArray(clippingRange, 2);
            ren->Render();
            renBack->Render();
            this->GetInteractor()->Render();
            
        }
    
    }else{
        vtkInteractorStyleTrackballCamera::OnMouseWheelForward();
    }
}

void TwoDViewStyle::OnMouseWheelBackward()
{
    if(is2DView){
        u_int xBeg = block[0], xEnd = block[1], yBeg = block[2], yEnd = block[3], zBeg = block[4], zEnd = block[5];
        double cameraPostion = zEnd + dFromCamera2BlockEnd;
        vtk_sp(vtkCamera, camera) = ren->GetActiveCamera();
        double position[3];
        double focalPoint[3];
        double clippingRange[2];
        camera->GetPosition(position);
        camera->GetFocalPoint(focalPoint);
        camera->GetClippingRange(clippingRange);
        double distance = camera->GetDistance();
        double clipStart = clippingRange[0];
        double clipEnd = clippingRange[1];
        if(clipStart < dFromCamera2BlockEnd){
            cout<<"The Start"<<endl;
        }else{
            clipStart -= clippingDistance;
            clipEnd = clipStart + clippingDistance;
            double focalPointZ = cameraPostion - (clipStart + clipEnd) / 2;
            camera->SetClippingRange(clipStart, clipEnd);
            twoDCamera->SetFocalPoint(focalPoint[0], focalPoint[1], focalPointZ);
            camera->Modified();
            //double *zRange = sliceOutlineActor->GetZRange();
            sliceTransform->Translate(0, 0, clippingDistance);
            sliceTransform->Update();
            sliceOutlineActor->Modified();
            //double *actorPostion = sliceOutlineActor->GetCenter();
            //coutDoubleArray(zRange, 2);
            ren->Render();
            renBack->Render();
            this->GetInteractor()->Render();
            //camera->GetPosition(position);
            //camera->GetFocalPoint(focalPoint);
            //camera->GetClippingRange(clippingRange);
            //coutDoubleArray(position, 3);
            //coutDoubleArray(focalPoint, 3);
            //coutDoubleArray(clippingRange, 2);
        }
    }else{
        vtkInteractorStyleTrackballCamera::OnMouseWheelBackward();
    }
}

void TwoDViewStyle::SetImageBlock( u_int xBeg, u_int xEnd, u_int yBeg, u_int yEnd, u_int zBeg, u_int zEnd )
{
    block = new u_int[6];
    block[0] = xBeg;
    block[1] = xEnd;
    block[2] = yBeg;
    block[3] = yEnd;
    block[4] = zBeg;
    block[5] = zEnd;
    
    
    
    
    
    
}

void TwoDViewStyle::SetImageBlock( u_int arg[6] )
{
    block = new u_int[6];
    block[0] = arg[0];
    block[1] = arg[1];
    block[2] = arg[2];
    block[3] = arg[3];
    block[4] = arg[4];
    block[5] = arg[5];
    
    
   
}

void TwoDViewStyle::Set2dCamera()
{
    double clippingStart = dFromCamera2BlockEnd - clippingDistance / 2;
    double clippingEnd = clippingStart + clippingDistance;
    
    u_int xBeg = block[0], xEnd = block[1], yBeg = block[2], yEnd = block[3], zBeg = block[4], zEnd = block[5];
    u_int width = xEnd - xBeg + 1;
    u_int height = yEnd - yBeg + 1;
    double cameraPostion = zEnd + dFromCamera2BlockEnd;
    double focalPointZ = cameraPostion - (clippingStart + clippingEnd) / 2;
    parallelScale = (yEnd - yBeg) / 2 + 100;
    twoDCamera->SetParallelScale(parallelScale);
    twoDCamera->SetPosition((xBeg + xEnd) / 2, (yBeg + yEnd) / 2, cameraPostion);
    twoDCamera->SetClippingRange(clippingStart, clippingEnd);
    twoDCamera->SetFocalPoint((xBeg + xEnd) / 2, (yBeg + yEnd) / 2, focalPointZ);
    
    sliceTransform = vtk_new(vtkTransform);
    sliceTransform->Translate(xBeg, yBeg, focalPointZ);
    vtk_spnew(vtkOutlineSource, sliceSource);
    sliceSource->SetBounds(0, width - 1, 0, height - 1, 0, 0.1);
    vtk_spnew(vtkPolyDataMapper, sliceMapper);
    sliceMapper->SetInput(sliceSource->GetOutput());
    sliceOutlineActor->SetMapper(sliceMapper);
    sliceOutlineActor->SetUserTransform(sliceTransform);
    
    sliceOutlineActor->GetProperty()->SetColor(1.0, 0.0, 0.0);
    sliceOutlineActor->Modified();
    //double *actorPostion = sliceOutlineActor->GetCenter();
    //double *zRange = sliceOutlineActor->GetZRange();
    //coutDoubleArray(zRange, 2);
    //double focalPoint[3];
    //twoDCamera->GetFocalPoint(focalPoint);
    //coutDoubleArray(focalPoint, 3);
    
    
    
    
    this->GetInteractor()->Render();

}

void TwoDViewStyle::OnMouseMove()
{
    if(is2DView){
        if(isIn2dZoomMode){
            //int *mouseX, *mouseY;
            //this->GetInteractor()->GetMousePosition(mouseX, mouseY);
            
        
        }
    }else{
        vtkInteractorStyleTrackballCamera::OnMouseMove();
    }
}


void TwoDViewStyle::OnLeftButtonDown()
{
    if(is2DView && isInDrawMode){
        double focalPoint[3];
        twoDCamera->GetFocalPoint(focalPoint);
        double sliceZ = focalPoint[2];
        int eventPosition[2];
        this->GetInteractor()->GetEventPosition(eventPosition);
        ren->SetDisplayPoint(eventPosition[0], eventPosition[1], 0);
        ren->DisplayToWorld();
        double worldPoint[4];
        ren->GetWorldPoint(worldPoint);
        double pickPoint[3] = {worldPoint[0], worldPoint[1], sliceZ};
        if(isDrawHasStartPoint){
            if(drawOldPoint){
                vtk_spnew(vtkPoints, vertPoints);
                vtk_spnew(vtkCellArray, vertCells);
                vtk_spnew(vtkPolyData, vertPoly);
                vtk_spnew(vtkPolyDataMapper, vertMapper);
                vtk_spnew(vtkPoints, linePoints);
                vtk_spnew(vtkCellArray, lineCells);
                vtk_spnew(vtkPolyData, linePoly);
                vtk_spnew(vtkPolyDataMapper, lineMapper);
                vtk_spnew(vtkAppendPolyData, vertAppender);
                vtk_spnew(vtkAppendPolyData, lineAppender);
                vertPoints->InsertNextPoint(pickPoint[0], pickPoint[1], pickPoint[2]);
                vertCells->InsertNextCell(1);
                vertCells->InsertCellPoint(0);
                vertPoly->SetPoints(vertPoints);
                vertPoly->SetVerts(vertCells);
                vtkPolyDataMapper *oldVertMapper = vtkPolyDataMapper::SafeDownCast(drawVertActor->GetMapper());
                vtkPolyData *oldVertPoly = oldVertMapper->GetInput();
                vtk_spnew(vtkPolyDataMapper, newVertMapper);
                vertAppender->SetInput(oldVertPoly);
                vertAppender->AddInput(vertPoly);
                newVertMapper->SetInputConnection(vertAppender->GetOutputPort());
                newVertMapper->Update();
                newVertMapper->Modified();
                
                linePoints->InsertNextPoint(drawOldPoint[0], drawOldPoint[1], drawOldPoint[2]);
                linePoints->InsertNextPoint(pickPoint[0], pickPoint[1], pickPoint[2]);
                lineCells->InsertNextCell(2);
                lineCells->InsertCellPoint(0);
                lineCells->InsertCellPoint(1);
                linePoly->SetPoints(linePoints);
                linePoly->SetLines(lineCells);
                vtkPolyDataMapper  *oldLineMapper = vtkPolyDataMapper::SafeDownCast(drawLineActor->GetMapper());
                vtkPolyData *oldLinePoly = oldLineMapper->GetInput();
                vtk_spnew(vtkPolyDataMapper, newLineMapper);
                lineAppender->SetInput(oldLinePoly);
                lineAppender->AddInput(linePoly);
                newLineMapper->SetInputConnection(lineAppender->GetOutputPort());
                
                drawLineActor->SetMapper(newLineMapper);
                drawVertActor->SetMapper(newVertMapper);
                
                drawOldPoint[0] = pickPoint[0];
                drawOldPoint[1] = pickPoint[1];
                drawOldPoint[2] = pickPoint[2];
                
                this->GetInteractor()->Render();
                
            }
        }else{
            if(drawOldPoint){

            }else{
                drawOldPoint = new double[3];
            }
            isDrawHasStartPoint = true;
            drawOldPoint[0] = pickPoint[0];
            drawOldPoint[1] = pickPoint[1];
            drawOldPoint[2] = pickPoint[2];
            vtk_spnew(vtkPoints, vertPoints);
            vtk_spnew(vtkCellArray, vertCells);
            vtk_spnew(vtkPolyData, vertPoly);
            vtk_spnew(vtkPolyDataMapper, vertMapper);
            vtk_spnew(vtkPoints, linePoints);
            vtk_spnew(vtkCellArray, lineCells);
            vtk_spnew(vtkPolyData, linePoly);
            vtk_spnew(vtkPolyDataMapper, lineMapper);
            vertPoints->InsertNextPoint(pickPoint[0], pickPoint[1], pickPoint[2]);
            vertCells->InsertNextCell(1);
            vertCells->InsertCellPoint(0);
            vertPoly->SetPoints(vertPoints);
            vertPoly->SetVerts(vertCells);
            vertMapper->SetInput(vertPoly);
            drawVertActor->SetMapper(vertMapper);
            
            linePoints->InsertNextPoint(drawOldPoint[0], drawOldPoint[1], drawOldPoint[2]);
            linePoints->InsertNextPoint(pickPoint[0], pickPoint[1], pickPoint[2]);
            lineCells->InsertNextCell(2);
            lineCells->InsertCellPoint(0);
            lineCells->InsertCellPoint(1);
            linePoly->SetPoints(linePoints);
            linePoly->SetLines(lineCells);
            lineMapper->SetInput(linePoly);
            drawLineActor->SetMapper(lineMapper);
            
            
            
            this->GetInteractor()->Render(); 
        }
        
        
        
        
        
        
    }else{
        vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
    }

}



void TwoDViewStyle::OnLeftButtonUp()
{
    if(is2DView){
        

    }else{
        vtkInteractorStyleTrackballCamera::OnLeftButtonUp();
    }
}


void TwoDViewStyle::OnRightButtonDown()
{
    if(is2DView){
        isIn2dZoomMode = true;
    }else{
        vtkInteractorStyleTrackballCamera::OnRightButtonDown();
    }
}

void TwoDViewStyle::OnRightButtonUp()
{
    if(is2DView){
        isIn2dZoomMode = false;

    }else{
        vtkInteractorStyleTrackballCamera::OnRightButtonUp();
    }
}


void TwoDViewStyle::OnMiddleButtonDown()
{
    if(is2DView){
        isIn2dMoveMode = true;
    }else{
        vtkInteractorStyleTrackballCamera::OnMiddleButtonDown();
    }
}


void TwoDViewStyle::OnMiddleButtonUp()
{
    if(is2DView){
        isIn2dMoveMode = false;

    }else{
        vtkInteractorStyleTrackballCamera::OnMiddleButtonUp();
    }
}

void TwoDViewStyle::OnKeyPress()
{
    char *keySym = this->GetInteractor()->GetKeySym();
    string keyString(keySym);
    //cout<<keyString<<endl;
    if(keyString.compare("Up") == 0){
        if(isIn2dZoomMode){
            double curParallelScale = twoDCamera->GetParallelScale();
            curParallelScale *= zoomRatio;
            if(curParallelScale < 1){
                cout<<"Can not be larger!"<<endl;
            }else{
                twoDCamera->SetParallelScale(curParallelScale);
                this->GetInteractor()->Render();
            }
        }else if(isIn2dMoveMode){
            double cameraPostion[3];
            double focalPoint[3];
            twoDCamera->GetFocalPoint(focalPoint);
            twoDCamera->GetPosition(cameraPostion);
            cameraPostion[1] = cameraPostion[1] - moveStep;
            twoDCamera->SetPosition(cameraPostion);
            focalPoint[1] = focalPoint[1] - moveStep;
            twoDCamera->SetFocalPoint(focalPoint);
            coutDoubleArray(cameraPostion, 3);
            twoDCamera->Modified();
            this->GetInteractor()->Render();
        }
    }else if(keyString.compare("Down") == 0){
        if(isIn2dZoomMode){
            double curParallelScale = twoDCamera->GetParallelScale();
            curParallelScale /= zoomRatio;
            if(curParallelScale > 2000){
                cout<<"Can not be smaller!"<<endl;
            }else{
                twoDCamera->SetParallelScale(curParallelScale);
                this->GetInteractor()->Render();
            }
        }else if(isIn2dMoveMode){
            double cameraPostion[3];
            double focalPoint[3];
            twoDCamera->GetFocalPoint(focalPoint);
            twoDCamera->GetPosition(cameraPostion);
            cameraPostion[1] = cameraPostion[1] + moveStep;
            focalPoint[1] = focalPoint[1] + moveStep;
            twoDCamera->SetFocalPoint(focalPoint);
            twoDCamera->SetPosition(cameraPostion);
            coutDoubleArray(cameraPostion, 3);



            twoDCamera->Modified();
            this->GetInteractor()->Render();
        }
    }else if(keyString.compare("Left") == 0){
        if(isIn2dMoveMode){
            double cameraPostion[3];
            double focalPoint[3];
            twoDCamera->GetFocalPoint(focalPoint);
            twoDCamera->GetPosition(cameraPostion);
            cameraPostion[0] = cameraPostion[0] + moveStep;
            twoDCamera->SetPosition(cameraPostion);
            focalPoint[0] = focalPoint[0] + moveStep;
            twoDCamera->SetFocalPoint(focalPoint);
            coutDoubleArray(cameraPostion, 3);
            twoDCamera->Modified();
            this->GetInteractor()->Render();
        }
    }else if(keyString.compare("Right") == 0){
        if(isIn2dMoveMode){
            double cameraPostion[3];
            double focalPoint[3];
            twoDCamera->GetFocalPoint(focalPoint);
            twoDCamera->GetPosition(cameraPostion);
            cameraPostion[0] = cameraPostion[0] - moveStep;
            twoDCamera->SetPosition(cameraPostion);
            focalPoint[0] = focalPoint[0] - moveStep;
            twoDCamera->SetFocalPoint(focalPoint);
            coutDoubleArray(cameraPostion, 3);
            twoDCamera->Modified();
            this->GetInteractor()->Render();
        }
    }
}

