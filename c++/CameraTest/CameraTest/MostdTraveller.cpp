#include "stdafx.h"
#include "MostdTraveller.h"



vtkStandardNewMacro(MostdTraveller);
MostdTraveller::MostdTraveller():
    mostd_(0),
    swc_(0),
    isInTravelMode_(false),
    isInited_(false),
    wholePointNum_(0),
    curPointIndex_(0),
    travelLineIndex_(0),
    distanceFromFocal2Camera(400.0),
    clipHalfDistance(200.0),
    cameraAngel(60.0),
    step_(10.0),
    testMode_(false),
    isLeftMouseDown(false),
    toggleCamera_(false),
    moveVelocity_(30.0)
{
    vol_ = vtk_new(vtkVolume);
    outline_ = vtk_new(vtkActor);
    testActor_ = vtk_new(vtkCameraActor);
    lineActor_ = vtk_new(vtkActor);
    oldMousePoint_ = new int[2];
}

MostdTraveller::~MostdTraveller()
{
    if(oldMousePoint_){
        delete []oldMousePoint_;
    }
}


void MostdTraveller::SetMostd( Mostd *arg )
{
    mostd_ = arg;
    if(mostd_ && swc_){
        isInited_ = true;
    }
}

void MostdTraveller::SetSwc( SwcReader *arg )
{
    swc_ = arg;
    
    travelLine_ = swc_->GetOutput().at(travelLineIndex_);
    SamplePoints(travelLine_, step_);
    wholePointNum_ = static_cast<u_int>(usedLine_.size());
    curPointIndex_ = 0;
    if(mostd_ && swc_){
        isInited_ = true;
    }
}

void MostdTraveller::SetRenderer( vtk_sp(vtkRenderer, arg) )
{
    ren_ = arg;
    ren_->AddActor(vol_);
    ren_->AddActor(outline_);
    ren_->AddActor(testActor_);
    ren_->AddActor(lineActor_);
}

bool MostdTraveller::GetCaremaPosition( double focalPoint[3], double lastFocalPoint[3], double cameraPosition[3] )
{   
    double x2 = focalPoint[0], x1 = lastFocalPoint[0],
               y2 = focalPoint[1], y1 = lastFocalPoint[1],
               z2 = focalPoint[2], z1 = lastFocalPoint[2];
    double deltaX = x2 - x1, deltaY = y2 - y1, deltaZ = z2 - z1;
    //cout<<deltaX<<" "<<deltaY<<" "<<deltaZ<<endl;
    //(k - 1)^2*((x2 - x1)^2 + (y2 - y1)^2 + (z2 - z1)^2) = d^2
    //x = k * (x2 - x1) + x1, y = k * (y2 - y1) + y1, z = k * (z2 - z1) + z1
    double sumOfDelta2 = deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ;
    if(sumOfDelta2 < 0.000000000000001){
        cout<<"Almost the Same Point!!!"<<endl;
        return false;
    }
    bool signX = (deltaX > 0), signY = (deltaY > 0), signZ = (deltaZ > 0);
    double kMinusOne2 = distanceFromFocal2Camera * distanceFromFocal2Camera / sumOfDelta2;
    double k1 = sqrt(kMinusOne2) + 1;
    double k2 = -sqrt(kMinusOne2) + 1;
    double x3 = k1 * deltaX + x1;
    double y3 = k1 * deltaY + y1;
    double z3 = k1 * deltaZ + z1;
    if((((x3 - x2) > 0) == (signX)) && (((y3 - y2) > 0) == (signY)) && (((z3 - z2) > 0) == (signZ))){
        //cout<<"First"<<endl;
        //cout<<x3<<" "<<y3<<" "<<z3<<endl;
        cameraPosition[0] = x3;
        cameraPosition[1] = y3;
        cameraPosition[2] = z3;
        return true;
    }
    double x4 = k2 * deltaX + x1;
    double y4 = k2 * deltaY + y1;
    double z4 = k2 * deltaZ + z1;
    //cout<<"second"<<endl;
    //cout<<x4<<" "<<y4<<" "<<z4<<endl;
    cameraPosition[0] = x3;
    cameraPosition[1] = y3;
    cameraPosition[2] = z3;
    return true;
    
}

bool MostdTraveller::GetViewUp( double focalPoint[3], double lastFocalPoint[3], double viewUp[3] )
{
    double y1 = lastFocalPoint[1], y2 = focalPoint[1], z1 = lastFocalPoint[2], z2 = focalPoint[2];
    viewUp[0] = 0;
    double vectorViewY = y2 - y1, vectorViewZ = z2 - z1;
    double vectorViewY2 = pow(vectorViewY, 2), vectorViewZ2 = pow(vectorViewZ, 2);
    double vectorViewUpZ(0), vectorViewUpY(0);
    if(vectorViewY - 0 < 0.00000000000000001 && vectorViewY - 0 > - 0.00000000000000001){
        if(vectorViewZ > 0 || (vectorViewZ - 0 < 0.00000000000000001 && vectorViewZ - 0 > - 0.00000000000000001)){
            viewUp[1] = 1;    
        }else{
            viewUp[1] = -1;
        }
        viewUp[2] = 0;
        return true;
    }else{
        if(vectorViewY > 0 && vectorViewZ > 0){
            vectorViewUpZ = - sqrt(vectorViewY2 / (vectorViewY2 + vectorViewZ2));
            vectorViewUpY = sqrt(1 - pow(vectorViewUpZ, 2));
        }else if(vectorViewY > 0 && vectorViewZ < 0){
            vectorViewUpZ = - sqrt(vectorViewY2 / (vectorViewY2 + vectorViewZ2));
            vectorViewUpY = - sqrt(1 - pow(vectorViewUpZ, 2));
        }else if(vectorViewY < 0 && vectorViewZ < 0){
            vectorViewUpZ = sqrt(vectorViewY2 / (vectorViewY2 + vectorViewZ2));
            vectorViewUpY = - sqrt(1 - pow(vectorViewUpZ, 2));
        }else if(vectorViewY < 0 && vectorViewZ > 0){
            vectorViewUpZ = sqrt(vectorViewY2 / (vectorViewY2 + vectorViewZ2));
            vectorViewUpY = sqrt(1 - pow(vectorViewUpZ, 2));
        }
    }
    viewUp[1] = vectorViewUpY;
    viewUp[2] = vectorViewUpZ;
    return true;
}

bool MostdTraveller::GetClipRange( double cameraPostion[3], double focalPoint[3], double *clipRange )
{
    double distance2 = vtkMath::Distance2BetweenPoints(cameraPostion, focalPoint);
    double distance1 = sqrt(distance2);
    clipRange[0] = distance1 - 100;
    clipRange[1] = distance1 + 100;
    return true;    
}

void MostdTraveller::SamplePoints( vLine &line, double step )
{
    for(vLine::size_type i = 1; i < line.size(); ++i){
        vPoint point1 = line.at(i - 1);
        vPoint point2 = line.at(i);
        double dPoint1[3] = {point1[1] / 0.3, point1[2] / 0.3, point1[3]};
        double dPoint2[3] = {point2[1] / 0.3, point2[2] / 0.3, point2[3]};
        double d2From2To1 = vtkMath::Distance2BetweenPoints(dPoint2, dPoint1);
        double dFrom2To1 = sqrt(d2From2To1);
        if(dFrom2To1 < 0.0000000000001 && dFrom2To1 > -0.0000000000001){
            usedLine_ = line;
            return;
        }
        double increRatio = step / dFrom2To1;
        u_int increNum = 1 / increRatio;
        for(u_int j = 0; j < increNum; ++j){
            double tmpX = j * increRatio * (dPoint2[0] - dPoint1[0]) + dPoint1[0];
            double tmpY = j * increRatio * (dPoint2[1] - dPoint1[1]) + dPoint1[1];
            double tmpZ = j * increRatio * (dPoint2[2] - dPoint1[2]) + dPoint1[2];
            vPoint tmpPoint;
            tmpPoint<<0, tmpX, tmpY, tmpZ, 0;
            usedLine_.push_back(tmpPoint);
        }
        vPoint tmpPoint;
        tmpPoint<<0, dPoint2[0], dPoint2[1], dPoint2[2], 0;
        usedLine_.push_back(tmpPoint);
    }
    return;   
}

void MostdTraveller::OnChar()
{
    char key = this->GetInteractor()->GetKeyCode();
    switch(key){
        case 't':
        case 'T':
            {
                isInTravelMode_ = ! isInTravelMode_;
                break;
            }

        case 'x':
        case 'X':
            {
                testMode_ = ! testMode_;
                break;

            }
            
        case 'w':
        case 'W':
            {
                if(testMode_ && ! isLeftMouseDown){
                    cameraMoveForward(moveVelocity_);
                }
                break;
            }
            
        case 's':
        case 'S':
            {
                if(testMode_ && !isLeftMouseDown){
                    cameraMoveForward(-moveVelocity_);
                }
                break;
            }    
            
            
        case 'a':
        case 'A':
            {
                if(testMode_ && !isLeftMouseDown){
                    cameraMoveLeftRight(-moveVelocity_);
                }
                break;
            }
        
        case 'd':
        case 'D':
            {
                if(testMode_ && !isLeftMouseDown){
                    cameraMoveLeftRight(moveVelocity_);
                }
                break;
            }
        
            
        case 'q':
        case 'Q':
            {
                if(!toggleCamera_){
                    testCamera_ = ren_->GetActiveCamera();
                    vtk_spnew(vtkCamera, newCamera);
                    ren_->SetActiveCamera(newCamera);
                    ren_->ResetCamera();
                }else{
                    ren_->SetActiveCamera(testCamera_);
                }
                toggleCamera_ = ! toggleCamera_;
                this->GetInteractor()->Render();
                break;

            }    

        default:
            {
                vtkInteractorStyleTrackballCamera::OnChar();
                break;
            }
    }
}


void MostdTraveller::OnKeyPress()
{
    char *key = this->GetInteractor()->GetKeySym();
    string keyString(key);
    if(keyString.compare("Right") == 0){
        if(isInTravelMode_){
            cout<<"Travel Start"<<endl;
            //curPointIndex_ = 0;
            if(curPointIndex_ == wholePointNum_){
                cout<<"Reach the End of Line"<<endl;
                return; 
            }
            //for(; curPointIndex_ < wholePointNum_; ++curPointIndex_){
            cout<<curPointIndex_<<"/"<<wholePointNum_<<endl;
            vtk_spnew(vtkCamera, testCamera);
            vPoint curPoint = usedLine_.at(curPointIndex_);
            double focalPoint[3] = {curPoint[1], curPoint[2], curPoint[3]};
            if(curPointIndex_ == 0){
                oldPoint_ = curPoint;
                ren_->RemoveAllViewProps();
                //continue;
            }else{
                //ren_->RemoveActor(testActor_);
                //cout<<oldPoint_[1]<<" "<<oldPoint_[2]<<" "<<oldPoint_[3]<<endl;
                //cout<<curPoint[1]<<" "<<curPoint[2]<<" "<<curPoint[3]<<endl;
                double lastFocalPoint[3] = {oldPoint_[1], oldPoint_[2], oldPoint_[3]};
                ren_->RemoveActor(lineActor_);
                lineActor_ = vtk_new(vtkActor);
                vtk_spnew(vtkPoints, points);
                vtk_spnew(vtkCellArray, cells);
                points->InsertNextPoint(lastFocalPoint);
                points->InsertNextPoint(focalPoint);
                cells->InsertNextCell(2);
                cells->InsertCellPoint(0);
                cells->InsertCellPoint(1);
                vtk_spnew(vtkPolyData, poly);
                poly->SetPoints(points);
                poly->SetLines(cells);
                vtk_spnew(vtkPolyDataMapper, mapper);
                mapper->SetInput(poly);
                lineActor_->SetMapper(mapper);
                lineActor_->GetProperty()->SetLineWidth(6.0);
                lineActor_->GetProperty()->SetColor(vtkMath::Random(0, 1), vtkMath::Random(0, 1), vtkMath::Random(0, 1));
                ren_->AddActor(lineActor_);
                double cameraPosition[3] = {0, 0, 0};
                double viewUp[3] = {0, 0, 0};
                bool getFlag = GetCaremaPosition(focalPoint, lastFocalPoint, cameraPosition);
                GetViewUp(focalPoint, lastFocalPoint, viewUp);
                if(!getFlag){
                    cout<<"Count Camera Position Error!"<<endl;
                    return;
                }
                coutDoubleArray(cameraPosition, 3);
                coutDoubleArray(lastFocalPoint, 3);
                coutDoubleArray(focalPoint, 3);
                coutDoubleArray(viewUp, 3);
                testCamera->ParallelProjectionOff();
                testCamera->SetViewAngle(40.0);
                testCamera->SetClippingRange(300.0, 500.0);
                testCamera->SetPosition(cameraPosition);
                testCamera->SetFocalPoint(focalPoint);
                testCamera->SetViewUp(viewUp);
                testCamera->Modified();
                testActor_ = vtk_new(vtkCameraActor);
                testActor_->SetCamera(testCamera);
                testActor_->SetVisibility(true);
                testActor_->GetProperty()->SetLineWidth(5.0);
                testActor_->Modified();
                double *bounds = testActor_->GetBounds();
                coutDoubleArray(bounds, 6);
                u_int xBeg = static_cast<u_int>(bounds[0]);
                u_int xEnd = static_cast<u_int>(bounds[1]);
                u_int yBeg = static_cast<u_int>(bounds[2]);
                u_int yEnd = static_cast<u_int>(bounds[3]);
                u_int zBeg = static_cast<u_int>(bounds[4]);
                u_int zEnd = static_cast<u_int>(bounds[5]);
                u_int width = xEnd - xBeg + 1;
                u_int height = yEnd - yBeg + 1;
                u_int thick = zEnd - zBeg + 1;
                u_int imageSize[3] = {width, height, thick};
                if(mostd_->setROI(xBeg, xEnd, yBeg, yEnd, zBeg, zEnd)){
                    if(mostd_->loadImages()){
                        //mostd_->showImages();
                        TestVtkVolume volumeWarpper;
                        volumeWarpper.SetResolution(resolution_);
                        if(bitNum_ == 8){
                            volumeWarpper.SetImages(mostd_->GetImageData8(), imageSize);
                        }else if(bitNum_ == 16){
                            volumeWarpper.SetImages(mostd_->GetImageData16(), imageSize);
                        }
                        if(!volumeWarpper.Update()){
                            cout<<"volume build errro!"<<endl;
                            return;
                        }
                        ren_->RemoveActor(vol_);
                        ren_->RemoveActor(outline_);
                        vol_ = volumeWarpper.GetOutput();
                        outline_ = volumeWarpper.GetOutline();
                    }                                                     
                }
                vtk_spnew(vtkTransform, trans);
                trans->Translate(xBeg, yBeg, zBeg);
                vol_->SetUserTransform(trans);
                outline_->SetUserTransform(trans);
                ren_->AddActor(vol_);
                //ren_->AddActor(outline_);
                //ren_->AddActor(testActor_);

                ren_->SetActiveCamera(testCamera);
                //ren_->ResetCamera();
                cout<<"volume build complete!"<<endl;
            }
            this->GetInteractor()->Render();
            vtk_spnew(vtkWindowToImageFilter, windowShot);
            windowShot->SetInput(this->GetInteractor()->GetRenderWindow());
            vtk_spnew(vtkPNGWriter, pngWriter);

            stringstream stringStream;
            stringStream<<setw(5)<<setfill('0')<<curPointIndex_;
            stringStream<<".png";
            string imageName(stringStream.str());
            cout<<imageName<<endl;
            pngWriter->SetFileName(imageName.c_str());
            pngWriter->SetInput(windowShot->GetOutput());
            pngWriter->Write();  
            oldPoint_ = curPoint;
            ++curPointIndex_; 
            //}

        }else{

        }
    }

}

void MostdTraveller::OnLeftButtonDown()
{
    cout<<"Left Button Down"<<endl;
    isLeftMouseDown = true;
    vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
    vtk_sp(vtkCamera, camera) = ren_->GetActiveCamera();
    double cameraPosition[3];
    double focalPoint[3];
    double viewAngle = camera->GetViewAngle();
    double clipRange[2];
    double viewUp[3];
    camera->GetPosition(cameraPosition);
    camera->GetFocalPoint(focalPoint);
    camera->GetClippingRange(clipRange);
    camera->GetViewUp(viewUp);
    cout<<viewAngle<<endl;
    coutDoubleArray(cameraPosition, 3);
    coutDoubleArray(focalPoint, 3);
    coutDoubleArray(clipRange, 2);
    coutDoubleArray(viewUp, 3);
    int eventPosition[2];
    this->GetInteractor()->GetEventPosition(eventPosition);
    oldMousePoint_[0] = eventPosition[0];
    oldMousePoint_[1] = eventPosition[1];
    cout<<oldMousePoint_[0]<<" "<<oldMousePoint_[1]<<endl;
    
    
}


void MostdTraveller::OnLeftButtonUp()
{
    cout<<"Left Button Up"<<endl;
    isLeftMouseDown = false;
    vtkInteractorStyleTrackballCamera::OnLeftButtonUp();
    vtk_sp(vtkCamera, camera) = ren_->GetActiveCamera();
    double cameraPosition[3];
    double focalPoint[3];
    double viewAngle = camera->GetViewAngle();
    double clipRange[2];
    double viewUp[3];
    double aspect = 4 / 3.0;
    camera->GetPosition(cameraPosition);
    camera->GetFocalPoint(focalPoint);
    camera->GetClippingRange(clipRange);
    camera->GetViewUp(viewUp);
    //cout<<viewAngle<<endl;
    //coutDoubleArray(cameraPosition, 3);
    //coutDoubleArray(focalPoint, 3);
    //coutDoubleArray(clipRange, 2);
    //coutDoubleArray(viewUp, 3);
    if(testMode_){
        double coef[24];
        camera->GetFrustumPlanes(aspect, coef);
        vtk_spnew(vtkPlanes, planes);
        planes->SetFrustumPlanes(coef);
        vtk_spnew(vtkFrustumSource, frustumSource);
        frustumSource->SetPlanes(planes);
        frustumSource->SetShowLines(false);
        vtk_spnew(vtkPolyDataMapper, mapperFrustum);
        mapperFrustum->SetInputConnection(frustumSource->GetOutputPort());
        vtk_spnew(vtkActor, actorFrustum);
        actorFrustum->SetMapper(mapperFrustum);
        actorFrustum->GetProperty()->SetLineWidth(4.0);
        actorFrustum->GetProperty()->SetColor(1.0, 0.0, 0.0);
        actorFrustum->GetProperty()->SetRepresentationToWireframe();
        actorFrustum->Modified();
        double bounds[6];
        actorFrustum->GetBounds(bounds);
        u_int xBeg = static_cast<u_int>(bounds[0]);
        u_int xEnd = static_cast<u_int>(bounds[1]);
        u_int yBeg = static_cast<u_int>(bounds[2]);
        u_int yEnd = static_cast<u_int>(bounds[3]);
        u_int zBeg = static_cast<u_int>(bounds[4]);
        u_int zEnd = static_cast<u_int>(bounds[5]);
        u_int width = xEnd - xBeg + 1;
        u_int height = yEnd - yBeg + 1;
        u_int thick = zEnd - zBeg + 1;
        u_int imageSize[3] = {width, height, thick};
        if(mostd_->setROI(xBeg, xEnd, yBeg, yEnd, zBeg, zEnd)){
            if(mostd_->loadImages()){
                //mostd_->showImages();
                TestVtkVolume volumeWarpper;
                volumeWarpper.SetResolution(resolution_);
                if(bitNum_ == 8){
                    volumeWarpper.SetImages(mostd_->GetImageData8(), imageSize);
                }else if(bitNum_ == 16){
                    volumeWarpper.SetImages(mostd_->GetImageData16(), imageSize);
                }
                if(!volumeWarpper.Update()){
                    cout<<"volume build errro!"<<endl;
                    return;
                }
                //ren_->RemoveActor(vol_);
                //ren_->RemoveActor(outline_);
                //ren_->RemoveActor(testActor_);
                ren_->RemoveAllViewProps();
                vol_ = volumeWarpper.GetOutput();
                outline_ = volumeWarpper.GetOutline();
                cout<<"Volume Render Completed!"<<endl;
            }                                                     
        }
        //ren_->RemoveActor(lineActor_);
        lineActor_ = vtk_new(vtkActor);
        vtk_spnew(vtkPoints, points);
        vtk_spnew(vtkCellArray, cells);
        points->InsertNextPoint(cameraPosition);
        points->InsertNextPoint(focalPoint);
        cells->InsertNextCell(2);
        cells->InsertCellPoint(0);
        cells->InsertCellPoint(1);
        vtk_spnew(vtkPolyData, poly);
        poly->SetPoints(points);
        poly->SetLines(cells);
        vtk_spnew(vtkPolyDataMapper, mapper);
        mapper->SetInput(poly);
        lineActor_->SetMapper(mapper);
        lineActor_->GetProperty()->SetLineWidth(6.0);
        lineActor_->GetProperty()->SetColor(vtkMath::Random(0, 1), vtkMath::Random(0, 1), vtkMath::Random(0, 1));
        ren_->AddActor(lineActor_);
        vtk_spnew(vtkTransform, trans);
        testActor_->GetProperty()->SetLineWidth(5.0);
        testActor_->GetProperty()->SetColor(1.0, 0.0, 0.0);
        trans->Translate(xBeg, yBeg, zBeg);
        vol_->SetUserTransform(trans); 
        outline_->SetUserTransform(trans);
        ren_->AddActor(vol_); 
        //ren_->AddActor(outline_);
        //ren_->AddActor(testActor_);
        this->GetInteractor()->Render();
    }

}

void MostdTraveller::OnMouseWheelForward()
{
    vtkInteractorStyleTrackballCamera::OnMouseWheelForward();
    //if(testMode_){
    //    vtk_sp(vtkCamera, camera) = ren_->GetActiveCamera();
    //    double cameraPosition[3];
    //    double focalPoint[3];
    //    double viewAngle = camera->GetViewAngle();
    //    double clipRange[2];
    //    double viewUp[3];
    //    camera->GetPosition(cameraPosition);
    //    camera->GetFocalPoint(focalPoint);
    //    camera->GetClippingRange(clipRange);
    //    camera->GetViewUp(viewUp);
    //    cout<<viewAngle<<endl;
    //    coutDoubleArray(cameraPosition, 3);
    //    coutDoubleArray(focalPoint, 3);
    //    coutDoubleArray(clipRange, 2);
    //    coutDoubleArray(viewUp, 3);
    //    GetClipRange(cameraPosition, focalPoint, clipRange);
    //    camera->SetClippingRange(clipRange);
    //    
    //}
    //this->GetInteractor()->Render();
    //
    
}

void MostdTraveller::OnMouseWheelBackward()
{
    vtkInteractorStyleTrackballCamera::OnMouseWheelBackward();
    //if(testMode_){
    //    vtk_sp(vtkCamera, camera) = ren_->GetActiveCamera();
    //    double cameraPosition[3];
    //    double focalPoint[3];
    //    double viewAngle = camera->GetViewAngle();
    //    double clipRange[2];
    //    double viewUp[3];
    //    camera->GetPosition(cameraPosition);
    //    camera->GetFocalPoint(focalPoint);
    //    camera->GetClippingRange(clipRange);
    //    camera->GetViewUp(viewUp);
    //    cout<<viewAngle<<endl;
    //    coutDoubleArray(cameraPosition, 3);
    //    coutDoubleArray(focalPoint, 3);
    //    coutDoubleArray(clipRange, 2);
    //    coutDoubleArray(viewUp, 3);
    //    GetClipRange(cameraPosition, focalPoint, clipRange);
    //    camera->SetClippingRange(clipRange);
    //    
    //}
    //this->GetInteractor()->Render();
    
    
}

void MostdTraveller::OnMouseMove()
{
    if(isLeftMouseDown && testMode_){
        int curMousePosition[2];
        this->GetInteractor()->GetEventPosition(curMousePosition);
        vtk_sp(vtkCamera, camera) = ren_->GetActiveCamera();
        int delX = curMousePosition[0] - oldMousePoint_[0];
        int delY = curMousePosition[1] - oldMousePoint_[1];
        double cameraPosition[3];
        double focalPoint[3];
        double viewAngle = camera->GetViewAngle();
        double clipRange[2];
        double viewUp[3];
        camera->GetPosition(cameraPosition);
        camera->GetFocalPoint(focalPoint);
        camera->GetClippingRange(clipRange);
        camera->OrthogonalizeViewUp();
        camera->GetViewUp(viewUp);
        double distance1 = sqrt(vtkMath::Distance2BetweenPoints(cameraPosition, focalPoint));
        if(distance1 > -0.00000000000001 && distance1 < 0.00000000000001){
            return;
        }
        double rotateX = delX * 180.0 / (distance1 * vtkMath::Pi());
        double rotateY = delY * 180.0 / (distance1 * vtkMath::Pi());
        //cout<<"eeeeeeeeee"<<rotateY<<" "<<rotateX<<endl;
        camera->Azimuth(-rotateX);
        camera->Elevation(-rotateY);
        cout<<viewAngle<<endl;
        coutDoubleArray(cameraPosition, 3);
        coutDoubleArray(focalPoint, 3);
        coutDoubleArray(clipRange, 2);
        coutDoubleArray(viewUp, 3);
        GetClipRange(cameraPosition, focalPoint, &clipRange[0]);
        camera->SetClippingRange(clipRange);
        coutDoubleArray(clipRange, 2);
        this->GetInteractor()->Render();
        oldMousePoint_[0] = curMousePosition[0];
        oldMousePoint_[1] = curMousePosition[1];
        cout<<oldMousePoint_[0]<<" "<<oldMousePoint_[1]<<endl;
    }else{
        vtkInteractorStyleTrackballCamera::OnMouseMove();
    }
    
    
}

void MostdTraveller::cameraMoveForward(double step)
{
    cout<<"move forward"<<endl;
    vtk_sp(vtkCamera, camera) = ren_->GetActiveCamera();
    double cameraPosition[3];
    double focalPoint[3];
    double viewAngle = camera->GetViewAngle();
    double clipRange[2];
    double viewUp[3];
    double aspect = 4 / 3.0;
    camera->GetPosition(cameraPosition);
    camera->GetFocalPoint(focalPoint);
    camera->GetClippingRange(clipRange);
    camera->GetViewUp(viewUp);
    //cout<<viewAngle<<endl;
    coutDoubleArray(cameraPosition, 3);
    coutDoubleArray(focalPoint, 3);
    //coutDoubleArray(clipRange, 2);
    //coutDoubleArray(viewUp, 3);
    CalcuForwardCameraPosition(cameraPosition, focalPoint, step);
    coutDoubleArray(cameraPosition, 3);
    coutDoubleArray(focalPoint, 3);
    camera->SetPosition(cameraPosition);
    camera->SetFocalPoint(focalPoint);
    camera->Modified();
    if(testMode_){
        double coef[24];
        camera->GetFrustumPlanes(aspect, coef);
        vtk_spnew(vtkPlanes, planes);
        planes->SetFrustumPlanes(coef);
        vtk_spnew(vtkFrustumSource, frustumSource);
        frustumSource->SetPlanes(planes);
        frustumSource->SetShowLines(false);
        vtk_spnew(vtkPolyDataMapper, mapperFrustum);
        mapperFrustum->SetInputConnection(frustumSource->GetOutputPort());
        vtk_spnew(vtkActor, actorFrustum);
        actorFrustum->SetMapper(mapperFrustum);
        actorFrustum->GetProperty()->SetLineWidth(4.0);
        actorFrustum->GetProperty()->SetColor(1.0, 0.0, 0.0);
        actorFrustum->GetProperty()->SetRepresentationToWireframe();
        actorFrustum->Modified();
        double bounds[6];
        //coutDoubleArray(bounds, 6);
        actorFrustum->GetBounds(bounds);
        coutDoubleArray(bounds, 6);
        u_int xBeg = static_cast<u_int>(bounds[0]);
        u_int xEnd = static_cast<u_int>(bounds[1]);
        u_int yBeg = static_cast<u_int>(bounds[2]);
        u_int yEnd = static_cast<u_int>(bounds[3]);
        u_int zBeg = static_cast<u_int>(bounds[4]);
        u_int zEnd = static_cast<u_int>(bounds[5]);
        u_int width = xEnd - xBeg + 1;
        u_int height = yEnd - yBeg + 1;
        u_int thick = zEnd - zBeg + 1;
        u_int imageSize[3] = {width, height, thick};
        if(mostd_->setROI(xBeg, xEnd, yBeg, yEnd, zBeg, zEnd)){
            if(mostd_->loadImages()){
                //mostd_->showImages();
                TestVtkVolume volumeWarpper;
                volumeWarpper.SetResolution(resolution_);
                if(bitNum_ == 8){
                    volumeWarpper.SetImages(mostd_->GetImageData8(), imageSize);
                }else if(bitNum_ == 16){
                    volumeWarpper.SetImages(mostd_->GetImageData16(), imageSize);
                }
                if(!volumeWarpper.Update()){
                    cout<<"volume build errro!"<<endl;
                    return;
                }
                //ren_->RemoveActor(vol_);
                //ren_->RemoveActor(outline_);
                //ren_->RemoveActor(testActor_);
                ren_->RemoveAllViewProps();
                vol_ = volumeWarpper.GetOutput();
                outline_ = volumeWarpper.GetOutline();
                cout<<"Volume Render Completed!"<<endl;
            }                                                     
        }
        //ren_->RemoveActor(lineActor_);
        //lineActor_ = vtk_new(vtkActor);
        //vtk_spnew(vtkPoints, points);
        //vtk_spnew(vtkCellArray, cells);
        //points->InsertNextPoint(cameraPosition);
        //points->InsertNextPoint(focalPoint);
        //cells->InsertNextCell(2);
        //cells->InsertCellPoint(0);
        //cells->InsertCellPoint(1);
        //vtk_spnew(vtkPolyData, poly);
        //poly->SetPoints(points);
        //poly->SetLines(cells);
        //vtk_spnew(vtkPolyDataMapper, mapper);
        //mapper->SetInput(poly);
        //lineActor_->SetMapper(mapper);
        //lineActor_->GetProperty()->SetLineWidth(6.0);
        //lineActor_->GetProperty()->SetColor(vtkMath::Random(0, 1), vtkMath::Random(0, 1), vtkMath::Random(0, 1));
        //ren_->AddActor(lineActor_);
        vtk_spnew(vtkTransform, trans);
        testActor_->GetProperty()->SetLineWidth(5.0);
        testActor_->GetProperty()->SetColor(1.0, 0.0, 0.0);
        trans->Translate(xBeg, yBeg, zBeg);
        vol_->SetUserTransform(trans); 
        outline_->SetUserTransform(trans);
        ren_->AddActor(vol_); 
        ren_->AddActor(outline_);
        //ren_->AddActor(testActor_);
        this->GetInteractor()->Render();
    }
    
    
    
    
}

void MostdTraveller::CalcuForwardCameraPosition( double position[3], double focal[3], double step )
{
    double x1 = position[0], y1 = position[1], z1 = position[2], x2 = focal[0], y2 = focal[1], z2 = focal[2];
    double k2(0.0), k1(0.0), k0(0.0);
    double d2 = pow((x2 - x1), 2) + pow((y2 - y1), 2) + pow((z2 - z1), 2);
    if(d2 < 0.00000000001 && d2 > -0.00000000001){
        return;
    }
    k2 = pow(step, 2) / d2;
    if(step > 0){
        k1 = sqrt(k2);
    }else{
        k1 = -sqrt(k2);
    }
    k0 = k1 + 1;
    position[0] = k1 * (x2 - x1) + x1;
    position[1] = k1 * (y2 - y1) + y1;
    position[2] = k1 * (z2 - z1) + z1;
    focal[0] = k0 * (x2 - x1) + x1;
    focal[1] = k0 * (y2 - y1) + y1;
    focal[2] = k0 * (z2 - z1) + z1;
}

void MostdTraveller::cameraMoveLeftRight( double step )
{
    cout<<"move left or right"<<endl;
    vtk_sp(vtkCamera, camera) = ren_->GetActiveCamera();
    double cameraPosition[3];
    double focalPoint[3];
    double viewAngle = camera->GetViewAngle();
    double clipRange[2];
    double viewUp[3];
    double aspect = 4 / 3.0;
    camera->GetPosition(cameraPosition);
    camera->GetFocalPoint(focalPoint);
    camera->GetClippingRange(clipRange);
    camera->GetViewUp(viewUp);
    //cout<<viewAngle<<endl;
    coutDoubleArray(cameraPosition, 3);
    coutDoubleArray(focalPoint, 3);
    //coutDoubleArray(clipRange, 2);
    //coutDoubleArray(viewUp, 3);
    CalcuLeftCameraPosition(viewUp, cameraPosition, focalPoint, step);
    coutDoubleArray(cameraPosition, 3);
    coutDoubleArray(focalPoint, 3);
    camera->SetPosition(cameraPosition);
    camera->SetFocalPoint(focalPoint);
    camera->Modified();
    if(testMode_){
        double coef[24];
        camera->GetFrustumPlanes(aspect, coef);
        vtk_spnew(vtkPlanes, planes);
        planes->SetFrustumPlanes(coef);
        vtk_spnew(vtkFrustumSource, frustumSource);
        frustumSource->SetPlanes(planes);
        frustumSource->SetShowLines(false);
        vtk_spnew(vtkPolyDataMapper, mapperFrustum);
        mapperFrustum->SetInputConnection(frustumSource->GetOutputPort());
        vtk_spnew(vtkActor, actorFrustum);
        actorFrustum->SetMapper(mapperFrustum);
        actorFrustum->GetProperty()->SetLineWidth(4.0);
        actorFrustum->GetProperty()->SetColor(1.0, 0.0, 0.0);
        actorFrustum->GetProperty()->SetRepresentationToWireframe();
        actorFrustum->Modified();
        double bounds[6];
        actorFrustum->GetBounds(bounds);
        u_int xBeg = static_cast<u_int>(bounds[0]);
        u_int xEnd = static_cast<u_int>(bounds[1]);
        u_int yBeg = static_cast<u_int>(bounds[2]);
        u_int yEnd = static_cast<u_int>(bounds[3]);
        u_int zBeg = static_cast<u_int>(bounds[4]);
        u_int zEnd = static_cast<u_int>(bounds[5]);
        u_int width = xEnd - xBeg + 1;
        u_int height = yEnd - yBeg + 1;
        u_int thick = zEnd - zBeg + 1;
        u_int imageSize[3] = {width, height, thick};
        if(mostd_->setROI(xBeg, xEnd, yBeg, yEnd, zBeg, zEnd)){
            if(mostd_->loadImages()){
                //mostd_->showImages();
                TestVtkVolume volumeWarpper;
                volumeWarpper.SetResolution(resolution_);
                if(bitNum_ == 8){
                    volumeWarpper.SetImages(mostd_->GetImageData8(), imageSize);
                }else if(bitNum_ == 16){
                    volumeWarpper.SetImages(mostd_->GetImageData16(), imageSize);
                }
                if(!volumeWarpper.Update()){
                    cout<<"volume build errro!"<<endl;
                    return;
                }
                //ren_->RemoveActor(vol_);
                //ren_->RemoveActor(outline_);
                //ren_->RemoveActor(testActor_);
                ren_->RemoveAllViewProps();
                vol_ = volumeWarpper.GetOutput();
                outline_ = volumeWarpper.GetOutline();
                cout<<"Volume Render Completed!"<<endl;
            }                                                     
        }
        //ren_->RemoveActor(lineActor_);
        //lineActor_ = vtk_new(vtkActor);
        //vtk_spnew(vtkPoints, points);
        //vtk_spnew(vtkCellArray, cells);
        //points->InsertNextPoint(cameraPosition);
        //points->InsertNextPoint(focalPoint);
        //cells->InsertNextCell(2);
        //cells->InsertCellPoint(0);
        //cells->InsertCellPoint(1);
        //vtk_spnew(vtkPolyData, poly);
        //poly->SetPoints(points);
        //poly->SetLines(cells);
        //vtk_spnew(vtkPolyDataMapper, mapper);
        //mapper->SetInput(poly);
        //lineActor_->SetMapper(mapper);
        //lineActor_->GetProperty()->SetLineWidth(6.0);
        //lineActor_->GetProperty()->SetColor(vtkMath::Random(0, 1), vtkMath::Random(0, 1), vtkMath::Random(0, 1));
        //ren_->AddActor(lineActor_);
        vtk_spnew(vtkTransform, trans);
        testActor_->GetProperty()->SetLineWidth(5.0);
        testActor_->GetProperty()->SetColor(1.0, 0.0, 0.0);
        trans->Translate(xBeg, yBeg, zBeg);
        vol_->SetUserTransform(trans); 
        outline_->SetUserTransform(trans);
        ren_->AddActor(vol_); 
        //ren_->AddActor(outline_);
        //ren_->AddActor(testActor_);
        this->GetInteractor()->Render();
    }
}

void MostdTraveller::CalcuLeftCameraPosition( double up[3], double position[3], double focal[3], double step )
{
    double x1 = position[0], y1 = position[1], z1 = position[2], x2 = focal[0], y2 = focal[1], z2 = focal[2];
    double upX = up[0], upY = up[1], upZ = up[2], forwardX = x2 - x1, forwardY = y2 - y1, forwardZ = z2 - z1;
    double rightX = forwardY * upZ - upY * forwardZ, rightY = forwardZ * upX - upZ * forwardX, rightZ = forwardX * upY - upX * forwardY;
    double k(0.0), k2(0.0);
    double d2 = rightX * rightX + rightY * rightY + rightZ * rightZ;
    if(d2 < 0.00000000000001 && d2 > - 0.00000000000001){
        return;
    }
    k2 = step * step / d2;
    if(step > 0){
        k = sqrt(k2);
    }else if(step < 0){
        k = -sqrt(k2);
    }
    position[0] = x1 + k * rightX;
    position[1] = y1 + k * rightY;
    position[2] = z1 + k * rightZ;
    focal[0] = x2 + k * rightX;
    focal[1] = y2 + k * rightY;
    focal[2] = z2  + k * rightZ;
    return;  
}
