    //int point_num = 10;
    //vtkSmartPointer<vtkPoints> ps2 = vtkSmartPointer<vtkPoints>::New();
    //for(int i = 0; i < point_num; ++i){
    //    double px = vtkMath::Random(0, point_num);
    //    double py = vtkMath::Random(0, point_num);
    //    double pz = vtkMath::Random(0, point_num);
    //    cout<<px<<" "<<py<<" "<<pz<<endl;
    //    ps2->InsertNextPoint(px, py, pz);
    //}
    //vtkSmartPointer<vtkPolyData> pd2 = vtkSmartPointer<vtkPolyData>::New();
    //vtkSmartPointer<vtkCellArray> ca2 = vtkSmartPointer<vtkCellArray>::New();
    //vtkSmartPointer<vtkUnsignedCharArray> ca2_data = vtkSmartPointer<vtkUnsignedCharArray>::New();
    //ca2_data->SetNumberOfComponents(3);
    //ca2_data->SetNumberOfTuples(point_num);
    //for(int i = 0; i < point_num; ++i){
    //    vtkSmartPointer<vtkVertex> tmp_vert = vtkSmartPointer<vtkVertex>::New();
    //    tmp_vert->GetPointIds()->SetNumberOfIds(1);
    //    tmp_vert->GetPointIds()->SetId(0, i);
    //    ca2->InsertNextCell(tmp_vert);
    //    ca2_data->SetTuple3(i, 255, 0, 0);
    //}
    //pd2->SetVerts(ca2);
    //pd2->SetPoints(ps2);
    //pd2->GetCellData()->SetScalars(ca2_data);
    //pd2->Update();
    //cout<<pd2->GetNumberOfPoints()<<" "<<pd2->GetNumberOfCells()<<endl;
    //vtkSmartPointer<vtkPolyDataMapper> pdm2 = vtkSmartPointer<vtkPolyDataMapper>::New();
    //pdm2->SetScalarModeToUseCellData();
    //pdm2->SetInput(pd2);
    //vtkSmartPointer<vtkActor> a2 = vtkSmartPointer<vtkActor>::New();
    //a2->SetMapper(pdm2);
    ////a2->GetProperty()->SetColor(1.0, 1.0, 1.0);
    //a2->GetProperty()->SetPointSize(10.0);
    //vtkSmartPointer<vtkRenderer> r1 = vtkSmartPointer<vtkRenderer>::New();
    //vtkSmartPointer<vtkRenderWindow> rw1 = vtkSmartPointer<vtkRenderWindow>::New();
    //vtkSmartPointer<vtkRenderWindowInteractor> rwi1 = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    //vtkSmartPointer<vtkInteractorStyleTrackballCamera> istc = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    //vtkSmartPointer<TestCommand> tc = vtkSmartPointer<TestCommand>::New();
    //vtkSmartPointer<vtkCellPicker> cp = vtkSmartPointer<vtkCellPicker>::New();
    //vtkSmartPointer<vtkPointPicker> pp = vtkSmartPointer<vtkPointPicker>::New();
    //cp->SetPickFromList(1);
    //cp->AddPickList(a2);
    //rw1->SetSize(400, 400);
    //cp->SetTolerance(1 / 80.0);
    //tc->SetCellPicker(cp);
    //tc->SetRenderer(r1);
    //tc->SetPointerPicker(pp);
    //tc->SetPointsPolyData(pd2);
    //
    ////vtkSmartPointer<vtkImageData> images = vtkSmartPointer<vtkImageData>::New();
    //int extent = 10;
    ////images->SetExtent(-extent, extent, -extent, extent, -extent, extent);
    ////images->SetScalarTypeToUnsignedChar();
    ////images->SetNumberOfScalarComponents(1);
    ////for(int i = -extent; i <= extent; ++i){
    ////    for(int j = -extent; j <= extent; ++j){
    ////        for(int k = -extent; k <= extent; ++k){
    ////            images->SetScalarComponentFromDouble(i, j, k, 0, 255);
    ////        }
    ////    }
    ////}
    ////vtkSmartPointer<vtkImageDataGeometryFilter> idgf = vtkSmartPointer<vtkImageDataGeometryFilter>::New();
    ////idgf->SetInput(images);
    ////vtkSmartPointer<vtkPolyDataMapper> pdm = vtkSmartPointer<vtkPolyDataMapper>::New();
    ////pdm->SetInput(idgf->GetOutput());
    ////vtkSmartPointer<vtkActor> a = vtkSmartPointer<vtkActor>::New();
    ////a->SetMapper(pdm);
    //
    //vtkSmartPointer<vtkCubeSource> cube = vtkSmartPointer<vtkCubeSource>::New();
    //cube->SetBounds(-extent, extent, -extent, extent, -extent, extent);
    //cube->SetCenter(0, 0, 0);
    //vtkSmartPointer<vtkPolyDataMapper> pdm = vtkSmartPointer<vtkPolyDataMapper>::New();
    //pdm->SetInput(cube->GetOutput());
    //vtkSmartPointer<vtkActor> a = vtkSmartPointer<vtkActor>::New();
    //a->SetMapper(pdm);    
    //a->GetProperty()->SetOpacity(0.1);
    //
    //
    //vtkSmartPointer<TestImagePathCommand> tipc = vtkSmartPointer<TestImagePathCommand>::New();
    //tipc->SetActor(a);
    //tipc->SetRenderer(r1);
    //tipc->SetPickedActor(a2);
    //tipc->SetCellPicker(cp);
    //tipc->SetInteractor(rwi1);
    //tipc->SetPointsPolyData(pd2);
    //
    //
    ////itw->SetViewProp(a2);
    ////vtkSmartPointer<vtkImageCanvasSource2D> ic2d = vtkSmartPointer<vtkImageCanvasSource2D>::New();
    ////vtkSmartPointer<vtkImageActor> ia = vtkSmartPointer<vtkImageActor>::New();
    ////ic2d->SetScalarTypeToUnsignedChar();
    ////ic2d->SetNumberOfScalarComponents(1);
    ////ic2d->SetExtent(0, 399, 0, 399, 0, 0);
    ////ic2d->SetDrawColor(255, 255, 255);
    ////ic2d->FillBox(0, 399, 0, 399);
    ////ic2d->Update();
    ////ia->SetInput(ic2d->GetOutput());
    ////ia->SetOpacity(0);
    ////r1->AddActor(ia);
    //
    //
    //
    ////vtkSmartPointer<vtkImageTracerWidget> itw = vtkSmartPointer<vtkImageTracerWidget>::New();
    ////itw->SetInteractor(rwi1);
    ////itw->SetViewProp(a);
    ////itw->GetLineProperty()->SetLineWidth(3);
    ////itw->AutoCloseOn();
    ////itw->AddObserver(vtkCommand::EndInteractionEvent, tipc);
    //
    //
    //
    //vtkSmartPointer<vtkActor> moved_actor = vtkSmartPointer<vtkActor>::New();
    //if(moved_actor){
    //    cout<<"ddd"<<endl;
    //}
    //
    //
    //
    //vtkSmartPointer<TestAddNodeCommand> tanc = vtkSmartPointer<TestAddNodeCommand>::New();
    //tanc->SetCellPicker(cp);
    //tanc->SetPointsPolyData(pd2);
    //tanc->SetRenderer(r1);
    //bool picked = false;
    //vtkIdType picked_pointId = -1;
    //bool is_in_move_mode = false;
    //tanc->SetPickFlag(&picked, &picked_pointId, moved_actor);
    //vtkSmartPointer<TestMove> tm = vtkSmartPointer<TestMove>::New();
    //tm->SetPickFlag(&picked, &picked_pointId);
    //tm->SetRenderer(r1);
    //vtkSmartPointer<TestLeftButtonRelease> tlbr = vtkSmartPointer<TestLeftButtonRelease>::New();
    //tlbr->SetPickFlag(&picked, &picked_pointId);

    //
    //
    //
    //vtkSmartPointer<TestStyleKeyPressCommand> tskpc = vtkSmartPointer<TestStyleKeyPressCommand>::New();
    //tskpc->SetMoveMode(&is_in_move_mode);
    //tskpc->SetMovedActor(moved_actor);
    //
    //
    //istc->AddObserver(vtkCommand::KeyPressEvent, tskpc);
    //rwi1->AddObserver(vtkCommand::LeftButtonPressEvent, tanc);
    ////rwi1->AddObserver(vtkCommand::MouseMoveEvent, tm);
    ////rwi1->AddObserver(vtkCommand::LeftButtonReleaseEvent, tlbr);
    //rwi1->SetInteractorStyle(istc);
    //r1->AddActor(a2);
    //r1->AddActor(a);
    //rw1->AddRenderer(r1);
    //rwi1->SetRenderWindow(rw1);
    //rw1->Render();
    ////itw->On();
    //rwi1->Initialize();
    //rwi1->Start();