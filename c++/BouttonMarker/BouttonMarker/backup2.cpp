//vtkSmartPointer<vtkPoints> points = areaPicker->GetClipPoints();
//vtkSmartPointer<vtkCellArray> polyCells = vtkSmartPointer<vtkCellArray>::New();
//polyCells->InsertNextCell(4);
//polyCells->InsertCellPoint(3);
//polyCells->InsertCellPoint(7);
//polyCells->InsertCellPoint(5);
//polyCells->InsertCellPoint(1);
//double p[3];
//points->GetPoint(0, p);
//cout<<p[0]<<" "<<p[1]<<" "<<p[2]<<endl;
//points->GetPoint(2, p);
//cout<<p[0]<<" "<<p[1]<<" "<<p[2]<<endl;
//points->GetPoint(4, p);
//cout<<p[0]<<" "<<p[1]<<" "<<p[2]<<endl;
//points->GetPoint(6, p);
//cout<<p[0]<<" "<<p[1]<<" "<<p[2]<<endl;
//vtkSmartPointer<vtkPolyData> poly = vtkSmartPointer<vtkPolyData>::New();
//poly->SetPoints(points);
//poly->SetPolys(polyCells);
//vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
//mapper->SetInput(poly);
//vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
//actor->SetMapper(mapper);
//actor->GetProperty()->SetOpacity(0.4);




//void TestMoveCommand::Execute( vtkObject *caller, unsigned long eventId, void *callData )
//{
//    vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkRenderWindowInteractor::SafeDownCast(caller);
//    vtkSmartPointer<vtkRenderer> ren = iren->GetRenderWindow()->GetRenderers()->GetFirstRenderer();
//    vtkSmartPointer<vtkAreaPicker> areaPicker = vtkSmartPointer<vtkAreaPicker>::New();
//    areaPicker->AreaPick(0, 0, iren->GetRenderWindow()->GetSize()[0], iren->GetRenderWindow()->GetSize()[1], ren);
//    vtkSmartPointer<vtkPlane> planeNear = vtkSmartPointer<vtkPlane>::New();
//    areaPicker->GetFrustum()->GetPlane(4, planeNear);
//    double origin[3];
//    double normal[3];
//    planeNear->GetOrigin(origin);
//    planeNear->GetNormal(normal);
//    int *eventPosition = iren->GetEventPosition();
//    if(*ptrDrawModeFlag){
//        //cout<<"Start To Draw!"<<endl;
//        //cout<<"-----------------------"<<endl;
//        //cout<<eventPosition[0]<<" "<<eventPosition[1]<<endl;
//        ren->SetDisplayPoint(eventPosition[0], eventPosition[1], 1);
//        ren->DisplayToWorld();
//        double worldPosition[4];
//        ren->GetWorldPoint(worldPosition);
//        double tmp[3];
//        tmp[0] = worldPosition[0];
//        tmp[1] = worldPosition[1];
//        tmp[2] = worldPosition[2];
//        double proPosition[3];
//        planeNear->ProjectPoint(tmp, proPosition);
//        //cout<<worldPosition[0]<<" "<<worldPosition[1]<<" "<<worldPosition[2]<<" "<<worldPosition[3]<<endl;
//        if(! *ptrMovingFlag){
//            //cout<<"sss"<<endl;
//            *ptrMovingFlag = true;
//            startPoint[0] = proPosition[0];
//            startPoint[1] = proPosition[1];
//            startPoint[2] = proPosition[2];
//            //cout<<startPoint[0]<<" "<<startPoint[1]<<" "<<startPoint[2]<<" "<<startPoint[3]<<endl;
//        }else{
//            endPoint = &proPosition[0];
//            if(startPoint && endPoint){
//                //cout<<startPoint[0]<<" "<<startPoint[1]<<" "<<startPoint[2]<<" "<<startPoint[3]<<endl;
//                //cout<<endPoint[0]<<" "<<endPoint[1]<<" "<<endPoint[2]<<" "<<endPoint[3]<<endl;
//                vtkSmartPointer<vtkPoints> points1 = vtkSmartPointer<vtkPoints>::New();
//                points1->InsertNextPoint(startPoint[0], startPoint[1], startPoint[2]);
//                points1->InsertNextPoint(endPoint[0], endPoint[1], endPoint[2]);
//                vtkSmartPointer<vtkCellArray> lineCells = vtkSmartPointer<vtkCellArray>::New();
//                lineCells->InsertNextCell(2);
//                lineCells->InsertCellPoint(0);
//                lineCells->InsertCellPoint(1);
//                vtkSmartPointer<vtkPolyData> linePoly = vtkSmartPointer<vtkPolyData>::New();
//                linePoly->SetPoints(points1);
//                linePoly->SetLines(lineCells);
//                appendFilter->AddInput(linePoly);
//                appendFilter->Update();
//                //drawActor->SetMapper(drawMapper);
//
//            }
//            startPoint[0] = endPoint[0];
//            startPoint[1] = endPoint[1];
//            startPoint[2] = endPoint[2];
//        }
//        //cout<<"*************************"<<endl;
//        iren->Render();
//    }else{
//        //cout<<"Can Not Draw!"<<endl;
//    }
//
//
//}


//vtkSmartPointer<vtkActor> drawActor = vtkSmartPointer<vtkActor>::New();
//vtkSmartPointer<vtkPolyDataMapper> drawMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
//vtkSmartPointer<vtkPolyData> drawPoly = vtkSmartPointer<vtkPolyData>::New();
//drawActor->SetMapper(drawMapper);
//vtkSmartPointer<vtkAppendPolyData> appendFilter = vtkSmartPointer<vtkAppendPolyData>::New();
//appendFilter->SetInput(drawPoly);
//drawMapper->SetInputConnection(appendFilter->GetOutputPort());


//tc->SetCollection(actors);
//tc->SetCellPicker(cpicker);
//tc->SetRenderer(ren);
//vtkSmartPointer<vtkCubeSource> cube1 = vtkSmartPointer<vtkCubeSource>::New();
//cube1->SetBounds(-renderSize, renderSize, -renderSize, renderSize, -renderSize, renderSize);
//cube1->SetCenter(0.0, 0.0, 0.0);
//vtkSmartPointer<vtkPolyDataMapper> cube1Mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
//cube1Mapper->SetInput(cube1->GetOutput());
//vtkSmartPointer<vtkActor> cube1Actor = vtkSmartPointer<vtkActor>::New();
//cube1Actor->SetMapper(cube1Mapper);
//cube1Actor->GetProperty()->SetOpacity(0.3);
//vtkSmartPointer<vtkImageTracerWidget> imTracerWidget = vtkSmartPointer<vtkImageTracerWidget>::New();
//imTracerWidget->SetInteractor(iren);
//imTracerWidget->SetViewProp(cube1Actor);
//ren->AddActor(cube1Actor);