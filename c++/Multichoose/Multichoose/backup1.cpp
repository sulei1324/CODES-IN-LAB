 //   int point_num = 100;
 //   int actor_num = 20;
 //   vtkSmartPointer<vtkActorCollection> actors = vtkSmartPointer<vtkActorCollection>::New();
 //   vtkSmartPointer<vtkRenderer> ren = vtkSmartPointer<vtkRenderer>::New();
 //   vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
 //   vtkSmartPointer<vtkInteractorStyleTrackballCamera> is_trackball = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
 //   renWin->SetSize(600, 600);
 //   vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
 //   vtkSmartPointer<vtkCellPicker> cpicker = vtkSmartPointer<vtkCellPicker>::New();
 //   cpicker->SetTolerance(1 / 80.0);
 //   renWin->AddRenderer(ren);
 //   iren->SetRenderWindow(renWin);
 //   vtkSmartPointer<vtkAssembly> ass = vtkSmartPointer<vtkAssembly>::New();
 //   for(int i = 0; i < actor_num; ++i){
 //       vtkSmartPointer<vtkActor> actor_i = vtkSmartPointer<vtkActor>::New();
 //       vtkSmartPointer<vtkPolyDataMapper> mapper_i = vtkSmartPointer<vtkPolyDataMapper>::New();
 //       vtkSmartPointer<vtkPolyData> poly_i = vtkSmartPointer<vtkPolyData>::New();
 //       vtkSmartPointer<vtkPoints> points_i = vtkSmartPointer<vtkPoints>::New();
 //       vtkSmartPointer<vtkCellArray> cells_i = vtkSmartPointer<vtkCellArray>::New();
 //       points_i->SetNumberOfPoints(point_num);
 //       for(int j = 0; j < point_num; ++j){
 //           double tmp_x = vtkMath::Random(-100, 100);
 //           double tmp_y = vtkMath::Random(-100, 100);
 //           double tmp_z = vtkMath::Random(-100, 100);
 //           //cout<<tmp_x<<" "<<tmp_y<<" "<<tmp_z<<endl;
 //           points_i->SetPoint(j, tmp_x, tmp_y, tmp_z);
 //       }
 //       for(vtkIdType j = 0; j < point_num; ++j){
 //           if(j >= 0){
 //               vtkSmartPointer<vtkVertex> tmp_line = vtkSmartPointer<vtkVertex>::New();
 //               //tmp_line->GetPointIds()->SetId(0, j - 1);
 //               tmp_line->GetPointIds()->SetId(0, j);
 //               cells_i->InsertNextCell(tmp_line);
 //           }
 //           //vtkSmartPointer<TestVertex> tmp_vert = vtkSmartPointer<TestVertex>::New();
 //           //tmp_vert->setActorId(i);
 //           //tmp_vert->GetPointIds()->SetNumberOfIds(1);
 //           //tmp_vert->GetPointIds()->SetId(0, j);
 //           //cells_i->InsertNextCell(tmp_vert);
 //       }
 //       //cout<<cells_i->GetNumberOfCells()<<endl;
 //       double tmp_r = vtkMath::Random(0, 1);
 //       double tmp_g = vtkMath::Random(0, 1);
 //       double tmp_b = vtkMath::Random(0, 1);
 //       poly_i->SetPoints(points_i);
 //       poly_i->SetVerts(cells_i);
 //       poly_i->Update();
 //       
 ///*       if(i == 1){
 //           vtkSmartPointer<vtkTransform> trans = vtkSmartPointer<vtkTransform>::New();
 //           vtkSmartPointer<vtkTransformFilter> transfilter = vtkSmartPointer<vtkTransformFilter>::New();
 //           trans->Identity();
 //           trans->Scale(0.1, 0.1, 0.1);
 //           transfilter->SetTransform(trans);
 //           transfilter->SetInput(poly_i);
 //           mapper_i->SetInputConnection(transfilter->GetOutputPort());
 //       }*/
 //       mapper_i->SetInput(poly_i);
 //       actor_i->SetMapper(mapper_i);
 //       actor_i->GetProperty()->SetColor(tmp_r, tmp_g, tmp_b);
 //       actor_i->GetProperty()->SetPointSize(25.0);
 //       actors->AddItem(actor_i);
 //       ren->AddActor(actor_i);
 //       //if(i == 1){
 //       //    vtkSmartPointer<vtkTransform> trans = vtkSmartPointer<vtkTransform>::New();
 //       //    vtkSmartPointer<vtkTransformFilter> transfilter = vtkSmartPointer<vtkTransformFilter>::New();
 //       //    trans->Identity();
 //       //    trans->Scale(6.0, 6.0, 10.0);
 //       //    transfilter->SetTransform(trans);
 //       //    transfilter->SetInput(actor_i->GetMapper()->GetInput());
 //       //    actor_i->GetMapper()->SetInputConnection(transfilter->GetOutputPort());
 //       //    actor_i->GetMapper()->Update();
 //       //}
 //       
 //       
 //       
 //   }
 //   vtkSmartPointer<vtkIdTypeArray> array1 = vtkSmartPointer<vtkIdTypeArray>::New();
 //   vtkSmartPointer<vtkIdTypeArray> array2 = vtkSmartPointer<vtkIdTypeArray>::New();
 //   array1->SetNumberOfComponents(1);
 //   array1->InsertNextTuple1(11111);
 //   array2->SetNumberOfComponents(1);
 //   array2->InsertNextTuple1(100);
 //   array2->InsertNextTuple1(101);
 //   vtkSmartPointer<vtkActor> a1 = vtkSmartPointer<vtkActor>::New();
 //   vtkSmartPointer<vtkActor> a2 = vtkSmartPointer<vtkActor>::New();
 //   vtkSmartPointer<vtkActorCollection> as = vtkSmartPointer<vtkActorCollection>::New();
 //   as->AddItem(a1);
 //   as->AddItem(a2);
 //   cout<<as->IsItemPresent(a2)<<endl;
 //   as->RemoveItem(a1);
 //   cout<<as->IsItemPresent(a2)<<endl;
 //   //std::map<vtkSmartPointer<vtkActor>, vtkSmartPointer<vtkIdTypeArray>> map1;
 //   //map1[a1] = array1;
 //   //map1[a2] = array2;
 //   //cout<<map1.find(a1)->second->GetTuple1(0)<<endl;
 //   //ass->SetVisibility(false);
 //   vtkSmartPointer<TestCommand> tc = vtkSmartPointer<TestCommand>::New();
 //   tc->SetCollection(actors);
 //   tc->SetCellPicker(cpicker);
 //   tc->SetRenderer(ren);
 //   ren->Modified();
 //   ren->Render();
 //   cout<<ren->GetNumberOfPropsRendered()<<endl;
 //   cout<<actors->GetNumberOfItems()<<endl;
 //   //cout<<ren->GetActors()->GetNumberOfItems()<<endl;
 //   iren->SetInteractorStyle(is_trackball);
 //   iren->AddObserver(vtkCommand::LeftButtonPressEvent, tc);
 //   renWin->Render();
 //   iren->Initialize();
 //   iren->Start();