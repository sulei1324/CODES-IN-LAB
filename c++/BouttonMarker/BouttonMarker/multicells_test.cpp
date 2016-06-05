//#include "bouttonmarker.h"
//#include "TestStyle.h"
//
//
//
//int main(int argc, char *argv[])
//{
//    int point_num = 1000;
//    int actor_num = 50;
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
//    for(int i = 0; i < actor_num; ++i){
//        vtkSmartPointer<vtkActor> actor_i = vtkSmartPointer<vtkActor>::New();
//        vtkSmartPointer<vtkPolyDataMapper> mapper_i = vtkSmartPointer<vtkPolyDataMapper>::New();
//        vtkSmartPointer<vtkPolyData> poly_i = vtkSmartPointer<vtkPolyData>::New();
//        vtkSmartPointer<vtkPoints> points_i = vtkSmartPointer<vtkPoints>::New();
//        vtkSmartPointer<vtkCellArray> cells_i = vtkSmartPointer<vtkCellArray>::New();
//        points_i->SetNumberOfPoints(point_num);
//        for(int j = 0; j < point_num; ++j){
//            double tmp_x = vtkMath::Random(-10000, 10000);
//            double tmp_y = vtkMath::Random(-10000, 10000);
//            double tmp_z = vtkMath::Random(-10000, 10000);
//            //cout<<tmp_x<<" "<<tmp_y<<" "<<tmp_z<<endl;
//            points_i->SetPoint(j, tmp_x, tmp_y, tmp_z);
//        }
//        for(vtkIdType j = 0; j < point_num; ++j){
//            vtkSmartPointer<TestVertex> tmp_vert = vtkSmartPointer<TestVertex>::New();
//            tmp_vert->setActorId(i);
//            tmp_vert->GetPointIds()->SetNumberOfIds(1);
//            tmp_vert->GetPointIds()->SetId(0, j);
//            cells_i->InsertNextCell(tmp_vert);
//        }
//        //cout<<cells_i->GetNumberOfCells()<<endl;
//        double tmp_r = vtkMath::Random(0, 1);
//        double tmp_g = vtkMath::Random(0, 1);
//        double tmp_b = vtkMath::Random(0, 1);
//        poly_i->SetPoints(points_i);
//        poly_i->SetVerts(cells_i);
//        poly_i->Update();
//        mapper_i->SetInput(poly_i);
//        actor_i->SetMapper(mapper_i);
//        actor_i->GetProperty()->SetColor(tmp_r, tmp_g, tmp_b);
//        actor_i->GetProperty()->SetPointSize(5.0);
//        actors->AddItem(actor_i);
//        ren->AddActor(actor_i);
//        
//    }
//    vtkSmartPointer<TestCommand> tc = vtkSmartPointer<TestCommand>::New();
//    tc->SetCollection(actors);
//    tc->SetCellPicker(cpicker);
//    tc->SetRenderer(ren);
//    cout<<ren->GetActors()->GetNumberOfItems()<<endl;
//    iren->SetInteractorStyle(is_trackball);
//    iren->AddObserver(vtkCommand::LeftButtonPressEvent, tc);
//    renWin->Render();
//    iren->Initialize();
//    iren->Start();
//    
//    
//}
//
//
//#include "TestStyle.h"
//
//
//
//void TestStyle::OnLeftButtonDown(){
//    qDebug()<<"sss";
//}
//
//TestStyle* TestStyle::New(){
//    return new TestStyle();
//}
//
//TestCommand::TestCommand(){
//
//}
//
//TestCommand *TestCommand::New(){
//    return new TestCommand();
//}
//
//void TestCommand::Execute(vtkObject *caller, unsigned long eventId, void *callData){
//    cout<<caller->GetClassName()<<endl;
//    vtkRenderWindowInteractor *rwi = vtkRenderWindowInteractor::SafeDownCast(caller);
//    int chooseMode = rwi->GetAltKey();
//    char *key = rwi->GetKeySym();
//    //if(key){
//    //    string s_key(key);
//    //    cout<<s_key<<endl;
//    //    rwi->SetKeySym("");
//    //    rwi->Modified();
//    //    rwi->Render();
//    //}
//    int *clicked_position;
//    if(chooseMode){
//        cout<<"Start To Pick"<<endl;
//        clicked_position = rwi->GetEventPosition();
//        cout<<"x: "<<clicked_position[0]<<" y: "<<clicked_position[1]<<endl;
//        cell_picker->Pick(clicked_position[0], clicked_position[1], 0.0, ren);
//        //point_picker->Pick(clicked_position[0], clicked_position[1], 0.0, ren);
//        cout<<"Picked Cell Id: "<<cell_picker->GetCellId()<<endl;     
//        //vtkIdType point_id = point_picker->GetPointId();
//        vtkIdType cell_id = cell_picker->GetCellId();
//        if(cell_id != -1){
//            vtkSmartPointer<vtkActor> picked_actor = cell_picker->GetActor();
//            vtkSmartPointer<vtkPolyData> picked_poly = vtkPolyData::SafeDownCast(picked_actor->GetMapper()->GetInput());
//            picked_poly->BuildLinks();
//            picked_poly->DeleteCell(cell_id);
//            picked_poly->RemoveDeletedCells();
//            picked_poly->DeleteLinks();
//        }
//        
//        
//        //vtkIdType point_id1 = cell_picker->GetPointId();       
//        //cout<<"Picked Point: "<<point_id1<<endl;
//    //    if(cell_id != -1){
//    //        //vtkVertex *p1 = vtkVertex::SafeDownCast(co->GetItemAsObject(cell_id));
//    //        //cout<<p1->s_id<<endl;
//    //        //cout<<points_poly_data->GetNumberOfPoints()<<endl;
//    //        cout<<"start to delete......"<<endl;
//    //        cout<<points_poly_data->GetNumberOfCells()<<endl;
//    //        points_poly_data->BuildLinks();
//    //        points_poly_data->DeleteCell(cell_id);
//    //        points_poly_data->RemoveDeletedCells();
//    //        //co->RemoveItem(cell_id);
//    //        //cout<<cells_poly_data->GetNumberOfCells()<<endl;
//    //        cout<<points_poly_data->GetNumberOfCells()<<endl;;
//    //        cout<<points_poly_data->GetNumberOfPoints()<<endl;
//    //        points_poly_data->Update();
//    //        rwi->Render();
//    //    }   
//    }
//}
//
////TestSegmentPoints::TestSegmentPoints(){
////}
////TestSegmentPoints::~TestSegmentPoints(){
////}
//vtkStandardNewMacro(TestVtkPoint);
//TestVtkPoint::TestVtkPoint(){
//}
//TestVtkPoint::~TestVtkPoint(){
//}
////TestVtkPoint *TestVtkPoint::New(){
////    return new TestVtkPoint();
////}
//
//
//void TestImagePathCommand::Execute(vtkObject *caller, unsigned long eventId, void *callData){
//    cout<<"sss"<<endl;
//    int *ep = rwi->GetEventPosition();
//    cout<<ep[0]<<" "<<ep[1]<<endl;
//    vtkImageTracerWidget *imageTracer = vtkImageTracerWidget::SafeDownCast(caller);
//    vtkSmartPointer<vtkPolyData> path_data = vtkSmartPointer<vtkPolyData>::New();
//    cell_picker->Pick(ep[0], ep[1], 0, renderer);
//    if(cell_picker->GetCellId()!=-1){
//        cout<<cell_picker->GetCellId()<<endl;
//    }
//    
//    imageTracer->GetPath(path_data);
//    int point_num = path_data->GetNumberOfPoints();
//    int x_min = 1000, x_max = -1000, y_min = 1000, y_max = -1000;
//    for(int i = 0; i < point_num; ++i){
//        double *p = path_data->GetPoints()->GetPoint(i);
//        //cout<<p[0]<<" "<<p[1]<<" "<<p[2]<<endl;
//        renderer->SetWorldPoint(p[0], p[1], p[2], 1.0);
//        renderer->WorldToDisplay();
//        double *dp = renderer->GetDisplayPoint();
//        //cout<<dp[0]<<" "<<dp[1]<<" "<<dp[2]<<endl;
//        if(dp[0] < x_min){
//            x_min = dp[0];
//        }
//        if(dp[0] > x_max){
//            x_max = dp[0];
//        }
//       if(dp[1] < y_min){
//            y_min = dp[1];
//        }
//        if(dp[1] > y_max){
//            y_max = dp[1];
//        }
//    }
//    cout<<x_min<<" "<<x_max<<" "<<y_min<<" "<<y_max<<endl;
//    int xi_min = static_cast<int>(x_min);
//    int xi_max = static_cast<int>(x_max);
//    int yi_min = static_cast<int>(y_min);
//    int yi_max = static_cast<int>(y_max);
//    vector<vtkIdType>  ids;
//    for(int x = xi_min; x < xi_max; ++x){
//        for(int y = yi_min; y < yi_max; ++y){
//            cell_picker->Pick(x, y, 0, renderer);
//            vtkIdType cell_id = cell_picker->GetCellId();
//            if(cell_id!=-1){
//                ids.push_back(cell_id);
//                //ids.push_back(cell_id);
//            }
//        }
//    }
//    sort(ids.begin(), ids.end());
//    vector<vtkIdType>::iterator x = unique(ids.begin(), ids.end());
//    ids.erase(x, ids.end());
//    if(!ids.empty()){
//        cout<<"start to delete......"<<endl;
//        for(int i = 0; i < ids.size(); ++i){
//            vtkIdType cell_id = ids[i];
//            cout<<cell_id<<endl;
//            points_poly_data->GetCellData()->GetScalars()->SetTuple3(cell_id, 0, 255, 0);
//            //cout<<points_poly_data->GetNumberOfCells()<<endl;
//            //points_poly_data->BuildLinks();
//            //points_poly_data->DeleteCell(cell_id);
//            //points_poly_data->RemoveDeletedCells();            
//            //cout<<points_poly_data->GetNumberOfCells()<<endl;;
//            ////cout<<points_poly_data->GetNumberOfPoints()<<endl;
//            points_poly_data->GetCellData()->GetScalars()->Modified();
//            points_poly_data->GetCellData()->Update();
//            points_poly_data->Update();
//            rwi->Render();             
//        }
//        points_poly_data->BuildLinks();
//        for(int i = 0; i < ids.size(); ++i){
//            vtkIdType cell_id = ids[i];
//            cout<<cell_id<<endl;
//            //points_poly_data->GetCellData()->GetScalars()->SetTuple3(cell_id, 0, 255, 0);
//            //cout<<points_poly_data->GetNumberOfCells()<<endl;
//            points_poly_data->DeleteCell(cell_id);               
//            //cout<<points_poly_data->GetNumberOfCells()<<endl;;
//            ////cout<<points_poly_data->GetNumberOfPoints()<<endl;
//            //points_poly_data->GetCellData()->GetScalars()->Modified();
//            //points_poly_data->GetCellData()->Update();
//         
//        }
//        points_poly_data->RemoveDeletedCells();
//        points_poly_data->DeleteLinks();   
//        points_poly_data->Update();
//        rwi->Render();            
//    }
//    cout<<"eeeee"<<endl;
//}
//
//
//
//void TestMove::Execute(vtkObject *caller, unsigned long eventId, void *callDada){
//    vtkRenderWindowInteractor *rwi = vtkRenderWindowInteractor::SafeDownCast(caller);
//    int *ep = rwi->GetEventPosition();
//    vtkSmartPointer<vtkPointPicker> wpp = vtkSmartPointer<vtkPointPicker>::New();
//    if(rwi->GetAltKey()){
//        //cout<<*picked_ptr<<" "<<*picked_pointId_ptr<<endl;
//        if(*picked_ptr){
//            wpp->Pick(ep[0], ep[1], 0, renderer);
//            double *p = wpp->GetPickPosition();
//            cout<<p[0]<<" "<<p[1]<<" "<<p[2]<<endl;
//           
//        }
//    }
//    //if(rwi->GetControlKey()){
//    //    *picked_ptr = false;
//    //}
//}
//
//void TestAddNodeCommand::Execute(vtkObject *caller, unsigned long eventId, void *callDada){
//    vtkRenderWindowInteractor *rwi = vtkRenderWindowInteractor::SafeDownCast(caller);
//    int *ep = rwi->GetEventPosition();
//    cell_picker->Pick(ep[0], ep[1], 0, renderer);
//    vtkIdType cell_id = cell_picker->GetCellId(); 
//    if(cell_id != -1){
//        *picked_ptr = true;
//        if(*picked_pointId_ptr != -1){
//            double *cur_color = points_poly_data->GetCellData()->GetScalars()->GetTuple(*picked_pointId_ptr);
//            if(static_cast<int>(cur_color[0]) == 255 && static_cast<int>(cur_color[1]) == 0 && static_cast<int>(cur_color[2]) == 0){
//                points_poly_data->GetCellData()->GetScalars()->SetTuple3(*picked_pointId_ptr, 0, 255, 0);
//            }else{
//                points_poly_data->GetCellData()->GetScalars()->SetTuple3(*picked_pointId_ptr, 255, 0, 0);
//            }        
//            points_poly_data->GetCellData()->GetScalars()->Modified();
//        }
//        *picked_pointId_ptr = cell_id;
//        cout<<cell_id<<endl;
//        double *cur_color = points_poly_data->GetCellData()->GetScalars()->GetTuple(cell_id);
//        double *moved_cor = points_poly_data->GetCell(cell_id)->GetPoints()->GetPoint(0);
//
//        //vtkSmartPointer<vtkLine> tmp_line = vtkSmartPointer<vtkLine>::New();
//        //tmp_line->GetPointIds()->SetId(0, 0);
//        //tmp_line->GetPointIds()->SetId(1, 1);
//        //vtkSmartPointer<vtkCellArray> tmp_cellarray = vtkSmartPointer<vtkCellArray>::New();
//        //tmp_cellarray->InsertNextCell(tmp_line);
//        //vtkSmartPointer<vtkPoints> tmp_points = vtkSmartPointer<vtkPoints>::New();
//        //tmp_points->SetNumberOfPoints(2);
//        //tmp_points->InsertNextPoint(1, 1, 1);
//        //tmp_points->InsertNextPoint(0, 0, 0);
//        //moved_line->SetPoints(tmp_points);
//        //moved_line->SetLines(tmp_cellarray);
//        vtkSmartPointer<vtkCubeSource> s = vtkSmartPointer<vtkCubeSource>::New();
//        s->SetCenter(moved_cor[0], moved_cor[1], moved_cor[2]);
//        s->SetXLength(1.0);
//        s->SetYLength(1.0);
//        s->SetZLength(1.0);
//        vtkSmartPointer<vtkPolyDataMapper> tmp_mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
//        tmp_mapper->SetInput(s->GetOutput());
//        if(moved_actor){
//            renderer->RemoveActor(moved_actor);
//        }else{
//            cout<<"qqqq"<<endl;
//        }
//        //moved_actor = vtkSmartPointer<vtkActor>::New();
//        moved_actor->SetMapper(tmp_mapper);
//        moved_actor->GetProperty()->SetColor(255, 255, 0);
//        moved_actor->GetProperty()->SetRepresentationToWireframe();
//        cout<<moved_cor[0]<<" "<<moved_cor[1]<<" "<<moved_cor[2]<<endl;
//        cout<<cur_color[0]<<" "<<cur_color[1]<<" "<<cur_color[2]<<endl;
//        if(static_cast<int>(cur_color[0]) == 255 && static_cast<int>(cur_color[1]) == 0 && static_cast<int>(cur_color[2]) == 0){
//            points_poly_data->GetCellData()->GetScalars()->SetTuple3(cell_id, 0, 255, 0);
//        }else{
//            points_poly_data->GetCellData()->GetScalars()->SetTuple3(cell_id, 255, 0, 0);
//        }
//        points_poly_data->GetCellData()->GetScalars()->Modified();
//        renderer->AddActor(moved_actor);
//        //renderer->ResetCamera();
//        rwi->Render();
//    }
//}
//
//void TestLeftButtonRelease::Execute(vtkObject *caller, unsigned long eventId, void *callData){
//    vtkInteractorStyleTrackballCamera *rwi = vtkInteractorStyleTrackballCamera::SafeDownCast(caller);
//    cout<<"ssss"<<endl;
//    if(*picked_ptr){
//        *picked_ptr = false;
//    }
//}
//
//void TestStyleKeyPressCommand::Execute(vtkObject *caller, unsigned long eventId, void *callData){
//    vtkInteractorStyleTrackballCamera *istc = vtkInteractorStyleTrackballCamera::SafeDownCast(caller);
//    if(moved_actor){
//        cout<<"eeeeeee"<<endl;
//    }else{
//        cout<<"!!!!!!!!!!!!!!!!!!"<<endl;
//    }
//    
//    
//    char *key_sym = istc->GetInteractor()->GetKeySym();
//    cout<<key_sym<<endl;
//    if(strcmp(key_sym, "m") == 0){
//        *move_mode = !(*move_mode);
//        cout<<*move_mode<<endl;
//    
//    }
//    if(*move_mode){
//        if(strcmp(key_sym, "Up") == 0){
//            if(moved_actor){
//                cout<<"ssss"<<endl;
//                moved_actor->AddPosition(0, 1, 0);
//            }
//        }
//        if(strcmp(key_sym, "Down") == 0){
//            if(moved_actor){
//                moved_actor->AddPosition(0, -1, 0);
//            }
//        }
//        if(strcmp(key_sym, "Left") == 0){
//            if(moved_actor){
//                moved_actor->AddPosition(1, 0, 0);
//            }
//        }
//        if(strcmp(key_sym, "Right") == 0){
//            if(moved_actor){
//                moved_actor->AddPosition(-1, 0, 0);
//            }
//        }       
//    }
//    istc->GetInteractor()->Render();
//}
//
//
//vtkStandardNewMacro(TestVertex);
//TestVertex::TestVertex(){
//
//}
//TestVertex::~TestVertex(){
//
//}
//
//
//#ifndef TESTSTYLE_H
//#define TESTSTYLE_H
//
//#include <QtGui/QApplication>
//#include <vtkActor.h>
//#include <vtkSphereSource.h>
//#include <vtkCubeSource.h>
//#include <vtkPolyDataMapper.h>
//#include <vtkRenderer.h>
//#include <vtkRenderWindow.h>
//#include <vtkRenderWindowInteractor.h>
//#include <vtkSmartPointer.h>
//#include <vtkLine.h>
//#include <vtkCellArray.h>
//#include <vtkPoints.h>
//#include <vtkPolyData.h>
//#include <vtkPolyLine.h>
//#include <vtkProperty.h>
//#include <vtkVertex.h>
//#include <vtkInteractorStyleTrackballCamera.h>
//#include <iostream>
//#include <QDebug>
//#include <vtkCommand.h>
//#include <vtkObject.h>
//#include <vtkCellPicker.h>
//#include <vtkPointPicker.h>
//#include <vtkVertex.h>
//#include "vtkObjectFactory.h"
//#include "vtkCell.h"
//#include "vtkCollection.h"
//#include "vtkMath.h"
//#include "vtkImageTracerWidget.h"
//#include "vtkImageActor.h"
//#include "vtkImageData.h"
//#include "vtkImageCanvasSource2D.h"
//#include "vtkImageDataGeometryFilter.h"
//#include "vtkCubeSource.h"
//#include <set>
//#include <algorithm>
//#include <vtkUnsignedCharArray.h>
//#include <vtkCellData.h>
//#include <vtkWorldPointPicker.h>
//#include <vtkActorCollection.h>
//
//
//using namespace std;
//
//
//class TestStyle: public vtkInteractorStyleTrackballCamera{
//public:
//  static TestStyle* New();
//  vtkTypeMacro(TestStyle, vtkInteractorStyleTrackballCamera);
//  virtual void OnLeftButtonDown();
//};
//
//class TestCommand: public vtkCommand{
//public:
//    TestCommand();
//    static TestCommand *New();
//    virtual void Execute(vtkObject *caller, unsigned long eventId, void *callData);
//    void SetCellPicker(vtkSmartPointer<vtkCellPicker> cp){cell_picker = cp;}
//    void SetPointerPicker(vtkSmartPointer<vtkPointPicker> pp){point_picker = pp;}
//    void SetRenderer(vtkSmartPointer<vtkRenderer> r){ren = r;}
//    void SetPointsPolyData(vtkSmartPointer<vtkPolyData> &pd){points_poly_data = pd;}
//    void SetCellsPolyData(vtkSmartPointer<vtkPolyData> &pd){cells_poly_data = pd;}
//    void SetCollection(vtkSmartPointer<vtkActorCollection> &c){co = c;}
//    
//private:
//    vtkSmartPointer<vtkActorCollection> co;
//    vtkSmartPointer<vtkCellPicker> cell_picker;
//    vtkSmartPointer<vtkPointPicker> point_picker;
//    vtkSmartPointer<vtkRenderer> ren;
//    vtkSmartPointer<vtkPolyData> points_poly_data;
//    vtkSmartPointer<vtkPolyData> cells_poly_data;
//};
//
//class TestVtkPoint: public vtkVertex{
//public:
//    vtkTypeMacro(TestVtkPoint, vtkVertex);
//    static TestVtkPoint *New();
//    vtkIdType s_id;
//
//protected:
//    TestVtkPoint();
//    ~TestVtkPoint();
//
//private:
//    TestVtkPoint(const TestVtkPoint&);
//    void operator=(const TestVtkPoint&);
//};
//
//
//class TestImagePathCommand: public vtkCommand{
//public:
//    vtkTypeMacro(TestImagePathCommand, vtkCommand);
//    static TestImagePathCommand *New(){return new TestImagePathCommand;}
//    virtual void Execute(vtkObject *caller, unsigned long eventId, void *callData);
//    void SetActor(vtkSmartPointer<vtkActor> a){actor = a;}
//    void SetRenderer(vtkSmartPointer<vtkRenderer> r){renderer = r;}
//    void SetPickedActor(vtkSmartPointer<vtkActor> a){picked_actor = a;}
//    void SetInteractor(vtkSmartPointer<vtkRenderWindowInteractor> i){rwi = i;}
//    void SetCellPicker(vtkSmartPointer<vtkCellPicker> cp){cell_picker = cp;}
//    void SetPointsPolyData(vtkSmartPointer<vtkPolyData> &pd){points_poly_data = pd;}
//
//private:
//    vtkSmartPointer<vtkActor> actor, picked_actor;
//    vtkSmartPointer<vtkCellPicker> cell_picker;
//    vtkSmartPointer<vtkRenderer> renderer;
//    vtkSmartPointer<vtkRenderWindowInteractor> rwi;
//    vtkSmartPointer<vtkPolyData> points_poly_data;
//};
//
//
//class TestAddNodeCommand: public vtkCommand{
//public:
//    vtkTypeMacro(TestAddNodeCommand, vtkCommand);
//    static TestAddNodeCommand *New(){return new TestAddNodeCommand;}
//    virtual void Execute(vtkObject *caller, unsigned long eventId, void *callData);
//    void SetActor(vtkSmartPointer<vtkActor> a){actor = a;}
//    void SetRenderer(vtkSmartPointer<vtkRenderer> r){renderer = r;}
//    void SetPickedActor(vtkSmartPointer<vtkActor> a){picked_actor = a;}
//    void SetInteractor(vtkSmartPointer<vtkRenderWindowInteractor> i){rwi = i;}
//    void SetCellPicker(vtkSmartPointer<vtkCellPicker> cp){cell_picker = cp;}
//    void SetPointsPolyData(vtkSmartPointer<vtkPolyData> &pd){points_poly_data = pd;}
//    void SetPickFlag(bool *p, vtkIdType *id, vtkSmartPointer<vtkActor> l){picked_ptr = p; picked_pointId_ptr = id; moved_actor = l;}
//private:
//    bool *picked_ptr;
//    vtkSmartPointer<vtkActor> moved_actor;
//    vtkIdType *picked_pointId_ptr;
//    vtkSmartPointer<vtkActor> actor, picked_actor;
//    vtkSmartPointer<vtkCellPicker> cell_picker;
//    vtkSmartPointer<vtkRenderer> renderer;
//    vtkSmartPointer<vtkRenderWindowInteractor> rwi;
//    vtkSmartPointer<vtkPolyData> points_poly_data;
//};
//
//
//class TestMove: public vtkCommand{
//public:
//    vtkTypeMacro(TestMove, vtkCommand);
//    static TestMove *New(){return new TestMove;}
//    virtual void Execute(vtkObject *caller, unsigned long eventId, void *callData);
//    void SetActor(vtkSmartPointer<vtkActor> a){actor = a;}
//    void SetRenderer(vtkSmartPointer<vtkRenderer> r){renderer = r;}
//    void SetPickedActor(vtkSmartPointer<vtkActor> a){picked_actor = a;}
//    void SetInteractor(vtkSmartPointer<vtkRenderWindowInteractor> i){rwi = i;}
//    void SetCellPicker(vtkSmartPointer<vtkCellPicker> cp){cell_picker = cp;}
//    void SetPointsPolyData(vtkSmartPointer<vtkPolyData> &pd){points_poly_data = pd;}
//    void SetPickFlag(bool *p, vtkIdType *id){picked_ptr = p; picked_pointId_ptr = id;}
//private:
//    bool *picked_ptr;
//    vtkIdType *picked_pointId_ptr;
//    vtkSmartPointer<vtkActor> actor, picked_actor;
//    vtkSmartPointer<vtkCellPicker> cell_picker;
//    vtkSmartPointer<vtkRenderer> renderer;
//    vtkSmartPointer<vtkRenderWindowInteractor> rwi;
//    vtkSmartPointer<vtkPolyData> points_poly_data;
//};
//
//
//class TestLeftButtonRelease: public vtkCommand{
//public:
//    vtkTypeMacro(TestLeftButtonRelease, vtkCommand);
//    static TestLeftButtonRelease *New(){return new TestLeftButtonRelease;}
//    virtual void Execute(vtkObject *caller, unsigned long eventId, void *callData);
//    void SetActor(vtkSmartPointer<vtkActor> a){actor = a;}
//    void SetRenderer(vtkSmartPointer<vtkRenderer> r){renderer = r;}
//    void SetPickedActor(vtkSmartPointer<vtkActor> a){picked_actor = a;}
//    void SetInteractor(vtkSmartPointer<vtkRenderWindowInteractor> i){rwi = i;}
//    void SetCellPicker(vtkSmartPointer<vtkCellPicker> cp){cell_picker = cp;}
//    void SetPointsPolyData(vtkSmartPointer<vtkPolyData> &pd){points_poly_data = pd;}
//    void SetPickFlag(bool *p, vtkIdType *id){picked_ptr = p; picked_pointId_ptr = id;}
//private:
//    bool *picked_ptr;
//    vtkIdType *picked_pointId_ptr;
//    vtkSmartPointer<vtkActor> actor, picked_actor;
//    vtkSmartPointer<vtkCellPicker> cell_picker;
//    vtkSmartPointer<vtkRenderer> renderer;
//    vtkSmartPointer<vtkRenderWindowInteractor> rwi;
//    vtkSmartPointer<vtkPolyData> points_poly_data;
//};
//
//
//class TestStyleKeyPressCommand: public vtkCommand{
//public:
//    vtkTypeMacro(TestStyleKeyPressCommand, vtkCommand);
//    static TestStyleKeyPressCommand *New(){return new TestStyleKeyPressCommand;}
//    virtual void Execute(vtkObject *caller, unsigned long eventId, void *callData);
//    void SetMoveMode(bool *m){move_mode = m;}
//    void SetMovedActor(vtkSmartPointer<vtkActor> a){moved_actor = a;}
//
//private:
//    bool *move_mode;
//    vtkSmartPointer<vtkActor> moved_actor;
//};
//
//class TestVertex: public vtkVertex{
//public:
//    vtkTypeMacro(TestVertex, vtkVertex);
//    static TestVertex *New();
//    vtkIdType getActorId(){return actor_id;}
//    void setActorId(vtkIdType id){actor_id = id;}
//    
//protected:
//    TestVertex();
//    ~TestVertex();
//    
//private:
//    vtkIdType actor_id;
//    TestVertex(const TestVertex&);
//    void operator=(const TestVertex&);
//};
//
//
//
//#endif