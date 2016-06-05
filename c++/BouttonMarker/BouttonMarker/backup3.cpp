//#include "bouttonmarker.h"
//#include "TestStyle.h"
//#include <map>
//#include <memory>
//
//void startFunction(vtkObject* caller, long unsigned int eventId, void* clientData, void* callData);
//void endFunction(vtkObject* caller, long unsigned int eventId, void* clientData, void* callData);
//
//
//
//int main(int argc, char *argv[])
//{
//    int point_num = 1;
//    int actor_num = 20;
//    double renderSize = 100;
//    bool drawModeFlag = false;
//    bool movingFlag = false;
//    vtkSmartPointer<vtkActorCollection> actors = vtkSmartPointer<vtkActorCollection>::New();
//    vtkSmartPointer<vtkRenderer> ren = vtkSmartPointer<vtkRenderer>::New();
//    vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
//    vtkSmartPointer<vtkInteractorStyleTrackballCamera> is_trackball = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
//    renWin->SetSize(600, 600);
//    vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
//    vtkSmartPointer<vtkCellPicker> cpicker = vtkSmartPointer<vtkCellPicker>::New();
//    cpicker->SetTolerance(1 / 80.0);
//    renWin->AddRenderer(ren);
//    iren->SetRenderWindow(renWin);
//    vtkSmartPointer<vtkAssembly> ass = vtkSmartPointer<vtkAssembly>::New();
//    for(int i = 0; i < actor_num; ++i){
//        vtkSmartPointer<vtkActor> actor_i = vtkSmartPointer<vtkActor>::New();
//        vtkSmartPointer<vtkPolyDataMapper> mapper_i = vtkSmartPointer<vtkPolyDataMapper>::New();
//        vtkSmartPointer<vtkPolyData> poly_i = vtkSmartPointer<vtkPolyData>::New();
//        vtkSmartPointer<vtkPoints> points_i = vtkSmartPointer<vtkPoints>::New();
//        vtkSmartPointer<vtkCellArray> cells_i = vtkSmartPointer<vtkCellArray>::New();
//        points_i->SetNumberOfPoints(point_num);
//        for(int j = 0; j < point_num; ++j){
//            double tmp_x = vtkMath::Random(-renderSize, renderSize);
//            double tmp_y = vtkMath::Random(-renderSize, renderSize);
//            double tmp_z = vtkMath::Random(-renderSize, renderSize);
//            //cout<<tmp_x<<" "<<tmp_y<<" "<<tmp_z<<endl;
//            points_i->SetPoint(j, tmp_x, tmp_y, tmp_z);
//        }
//        for(vtkIdType j = 0; j < point_num; ++j){
//            if(j >= 0){
//                vtkSmartPointer<vtkVertex> tmp_line = vtkSmartPointer<vtkVertex>::New();
//                //tmp_line->GetPointIds()->SetId(0, j - 1);
//                tmp_line->GetPointIds()->SetId(0, j);
//                cells_i->InsertNextCell(tmp_line);
//            }
//            //vtkSmartPointer<TestVertex> tmp_vert = vtkSmartPointer<TestVertex>::New();
//            //tmp_vert->setActorId(i);
//            //tmp_vert->GetPointIds()->SetNumberOfIds(1);
//            //tmp_vert->GetPointIds()->SetId(0, j);
//            //cells_i->InsertNextCell(tmp_vert);
//        }
//        //cout<<cells_i->GetNumberOfCells()<<endl;
//        double tmp_r = vtkMath::Random(0, 1);
//        double tmp_g = vtkMath::Random(0, 1);
//        double tmp_b = vtkMath::Random(0, 1);
//        poly_i->SetPoints(points_i);
//        poly_i->SetVerts(cells_i);
//        poly_i->Update();
//        if(i == 1){
//            vtkSmartPointer<vtkTransform> trans = vtkSmartPointer<vtkTransform>::New();
//            vtkSmartPointer<vtkTransformFilter> transfilter = vtkSmartPointer<vtkTransformFilter>::New();
//            trans->Identity();
//            trans->Scale(0.1, 0.1, 0.1);
//            transfilter->SetTransform(trans);
//            transfilter->SetInput(poly_i);
//            mapper_i->SetInputConnection(transfilter->GetOutputPort());
//        }
//        mapper_i->SetInput(poly_i);
//        actor_i->SetMapper(mapper_i);
//        actor_i->GetProperty()->SetColor(tmp_r, tmp_g, tmp_b);
//        actor_i->GetProperty()->SetPointSize(25.0);
//        actors->AddItem(actor_i);
//        ren->AddActor(actor_i);   
//    }
//
//    vtkSmartPointer<vtkImageTracerWidget> imageTracer = vtkSmartPointer<vtkImageTracerWidget>::New();
//    imageTracer->SetInteractor(iren);
//    imageTracer->AutoCloseOn();
//    imageTracer->ProjectToPlaneOff();
//
//
//    //vtkSmartPointer<vtkCallbackCommand> startCallback = vtkSmartPointer<vtkCallbackCommand>::New();
//    //startCallback->SetCallback(startFunction);
//    //vtkSmartPointer<vtkCallbackCommand> endCallback = vtkSmartPointer<vtkCallbackCommand>::New();
//    //endCallback->SetCallback(endFunction);
//    //imageTracer->AddObserver(vtkCommand::StartInteractionEvent, startCallback);
//    //imageTracer->AddObserver(vtkCommand::EndInteractionEvent, endCallback);
//
//    vtkSmartPointer<TestKeyCommand> keyCommand = vtkSmartPointer<TestKeyCommand>::New();
//    keyCommand->SetDrawFlag(&drawModeFlag);
//    keyCommand->SetMovingFlag(&movingFlag);
//    keyCommand->SetDrawer(imageTracer);
//
//
//    ren->Modified();
//    ren->Render();
//    iren->SetInteractorStyle(is_trackball);
//    iren->AddObserver(vtkCommand::KeyPressEvent, keyCommand);
//    renWin->Render();
//    //imTracerWidget->On();
//    iren->Initialize();
//    iren->Start();
//}
//
//
//void startFunction(vtkObject* caller, long unsigned int eventId, void* clientData, void* callData){
//    vtkSmartPointer<vtkImageTracerWidget> imageTracer = vtkImageTracerWidget::SafeDownCast(caller);
//    imageTracer->GetLineProperty()->SetOpacity(1.0);
//    imageTracer->GetHandleProperty()->SetOpacity(1.0);
//    imageTracer->GetCurrentRenderer()->Render();
//}
//
//void endFunction(vtkObject* caller, long unsigned int eventId, void* clientData, void* callData){
//    vtkSmartPointer<vtkImageTracerWidget> imageTracer = vtkImageTracerWidget::SafeDownCast(caller);
//    imageTracer->GetLineProperty()->SetOpacity(0.0);
//    imageTracer->GetHandleProperty()->SetOpacity(0.0);
//    imageTracer->GetCurrentRenderer()->Render();
//}