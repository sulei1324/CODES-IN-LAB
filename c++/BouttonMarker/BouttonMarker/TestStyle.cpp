/********************************************************************
	created:	2016/05/26
	created:	26:5:2016   14:35
	filename: 	g:\sulei\workplace\vs\BouttonMarker\BouttonMarker\TestStyle.cpp
	file path:	g:\sulei\workplace\vs\BouttonMarker\BouttonMarker
	file base:	TestStyle
	file ext:	cpp
	author:		Su Lei
	
	purpose:	
*********************************************************************/
#include "TestStyle.h"


void TestStyle::OnLeftButtonDown(){
    qDebug()<<"sss";
}

TestStyle* TestStyle::New(){
    return new TestStyle();
}

TestCommand::TestCommand(){

}

TestCommand *TestCommand::New(){
    return new TestCommand();
}

void TestCommand::Execute(vtkObject *caller, unsigned long eventId, void *callData){
    cout<<caller->GetClassName()<<endl;
    vtkRenderWindowInteractor *rwi = vtkRenderWindowInteractor::SafeDownCast(caller);
    int chooseMode = rwi->GetAltKey();
    char *key = rwi->GetKeySym();
    //if(key){
    //    string s_key(key);
    //    cout<<s_key<<endl;
    //    rwi->SetKeySym("");
    //    rwi->Modified();
    //    rwi->Render();
    //}
    int *clicked_position;
    if(chooseMode){
        cout<<"Start To Pick"<<endl;
        clicked_position = rwi->GetEventPosition();
        cout<<"x: "<<clicked_position[0]<<" y: "<<clicked_position[1]<<endl;
        cell_picker->Pick(clicked_position[0], clicked_position[1], 0.0, ren);
        vtkSmartPointer<vtkWorldPointPicker> world_picker = vtkSmartPointer<vtkWorldPointPicker>::New();
        world_picker->Pick(clicked_position[0], clicked_position[1], 0.0, ren);
        double p[3];
        world_picker->GetPickPosition(p);
        cout<<p[0]<<" "<<p[1]<<" "<<p[2]<<endl;
        
        //point_picker->Pick(clicked_position[0], clicked_position[1], 0.0, ren);
        cout<<"Picked Cell Id: "<<cell_picker->GetCellId()<<endl;     
        //vtkIdType point_id = point_picker->GetPointId();
        vtkIdType cell_id = cell_picker->GetCellId();
        if(cell_id != -1){
            vtkSmartPointer<vtkActor> picked_actor =(cell_picker->GetActor());
            vtkSmartPointer<vtkPolyData> picked_poly = vtkPolyData::SafeDownCast(picked_actor->GetMapper()->GetInput());
            double p1[3];
            picked_poly->GetCell(cell_id)->GetPoints()->GetPoint(0, p1);
            double p2[3];
            picked_poly->GetCell(cell_id)->GetPoints()->GetPoint(1, p2);
            cout<<p1[0]<<" "<<p1[1]<<" "<<p1[2]<<endl;
            cout<<p2[0]<<" "<<p2[1]<<" "<<p2[2]<<endl;   
            
            
            
            //picked_poly->BuildLinks();
            //picked_poly->DeleteCell(cell_id);
            //picked_poly->RemoveDeletedCells();
            //picked_poly->DeleteLinks();
        }
        
        
        //vtkIdType point_id1 = cell_picker->GetPointId();       
        //cout<<"Picked Point: "<<point_id1<<endl;
    //    if(cell_id != -1){
    //        //vtkVertex *p1 = vtkVertex::SafeDownCast(co->GetItemAsObject(cell_id));
    //        //cout<<p1->s_id<<endl;
    //        //cout<<points_poly_data->GetNumberOfPoints()<<endl;
    //        cout<<"start to delete......"<<endl;
    //        cout<<points_poly_data->GetNumberOfCells()<<endl;
    //        points_poly_data->BuildLinks();
    //        points_poly_data->DeleteCell(cell_id);
    //        points_poly_data->RemoveDeletedCells();
    //        //co->RemoveItem(cell_id);
    //        //cout<<cells_poly_data->GetNumberOfCells()<<endl;
    //        cout<<points_poly_data->GetNumberOfCells()<<endl;;
    //        cout<<points_poly_data->GetNumberOfPoints()<<endl;
    //        points_poly_data->Update();
    //        rwi->Render();
    //    }   
    }
}

//TestSegmentPoints::TestSegmentPoints(){
//}
//TestSegmentPoints::~TestSegmentPoints(){
//}
vtkStandardNewMacro(TestVtkPoint);
TestVtkPoint::TestVtkPoint(){
}
TestVtkPoint::~TestVtkPoint(){
}
//TestVtkPoint *TestVtkPoint::New(){
//    return new TestVtkPoint();
//}


void TestImagePathCommand::Execute(vtkObject *caller, unsigned long eventId, void *callData){
    cout<<"sss"<<endl;
    int *ep = rwi->GetEventPosition();
    cout<<ep[0]<<" "<<ep[1]<<endl;
    vtkImageTracerWidget *imageTracer = vtkImageTracerWidget::SafeDownCast(caller);
    vtkSmartPointer<vtkPolyData> path_data = vtkSmartPointer<vtkPolyData>::New();
    cell_picker->Pick(ep[0], ep[1], 0, renderer);
    if(cell_picker->GetCellId()!=-1){
        cout<<cell_picker->GetCellId()<<endl;
    }
    
    imageTracer->GetPath(path_data);
    int point_num = path_data->GetNumberOfPoints();
    int x_min = 1000, x_max = -1000, y_min = 1000, y_max = -1000;
    for(int i = 0; i < point_num; ++i){
        double *p = path_data->GetPoints()->GetPoint(i);
        //cout<<p[0]<<" "<<p[1]<<" "<<p[2]<<endl;
        renderer->SetWorldPoint(p[0], p[1], p[2], 1.0);
        renderer->WorldToDisplay();
        double *dp = renderer->GetDisplayPoint();
        //cout<<dp[0]<<" "<<dp[1]<<" "<<dp[2]<<endl;
        if(dp[0] < x_min){
            x_min = dp[0];
        }
        if(dp[0] > x_max){
            x_max = dp[0];
        }
       if(dp[1] < y_min){
            y_min = dp[1];
        }
        if(dp[1] > y_max){
            y_max = dp[1];
        }
    }
    cout<<x_min<<" "<<x_max<<" "<<y_min<<" "<<y_max<<endl;
    int xi_min = static_cast<int>(x_min);
    int xi_max = static_cast<int>(x_max);
    int yi_min = static_cast<int>(y_min);
    int yi_max = static_cast<int>(y_max);
    vector<vtkIdType>  ids;
    for(int x = xi_min; x < xi_max; ++x){
        for(int y = yi_min; y < yi_max; ++y){
            cell_picker->Pick(x, y, 0, renderer);
            vtkIdType cell_id = cell_picker->GetCellId();
            if(cell_id!=-1){
                ids.push_back(cell_id);
                //ids.push_back(cell_id);
            }
        }
    }
    sort(ids.begin(), ids.end());
    vector<vtkIdType>::iterator x = unique(ids.begin(), ids.end());
    ids.erase(x, ids.end());
    if(!ids.empty()){
        cout<<"start to delete......"<<endl;
        for(int i = 0; i < ids.size(); ++i){
            vtkIdType cell_id = ids[i];
            cout<<cell_id<<endl;
            points_poly_data->GetCellData()->GetScalars()->SetTuple3(cell_id, 0, 255, 0);
            //cout<<points_poly_data->GetNumberOfCells()<<endl;
            //points_poly_data->BuildLinks();
            //points_poly_data->DeleteCell(cell_id);
            //points_poly_data->RemoveDeletedCells();            
            //cout<<points_poly_data->GetNumberOfCells()<<endl;;
            ////cout<<points_poly_data->GetNumberOfPoints()<<endl;
            points_poly_data->GetCellData()->GetScalars()->Modified();
            points_poly_data->GetCellData()->Update();
            points_poly_data->Update();
            rwi->Render();             
        }
        points_poly_data->BuildLinks();
        for(int i = 0; i < ids.size(); ++i){
            vtkIdType cell_id = ids[i];
            cout<<cell_id<<endl;
            //points_poly_data->GetCellData()->GetScalars()->SetTuple3(cell_id, 0, 255, 0);
            //cout<<points_poly_data->GetNumberOfCells()<<endl;
            points_poly_data->DeleteCell(cell_id);               
            //cout<<points_poly_data->GetNumberOfCells()<<endl;;
            ////cout<<points_poly_data->GetNumberOfPoints()<<endl;
            //points_poly_data->GetCellData()->GetScalars()->Modified();
            //points_poly_data->GetCellData()->Update();
         
        }
        points_poly_data->RemoveDeletedCells();
        points_poly_data->DeleteLinks();   
        points_poly_data->Update();
        rwi->Render();            
    }
    cout<<"eeeee"<<endl;
}



void TestMove::Execute(vtkObject *caller, unsigned long eventId, void *callDada){
    vtkRenderWindowInteractor *rwi = vtkRenderWindowInteractor::SafeDownCast(caller);
    int *ep = rwi->GetEventPosition();
    vtkSmartPointer<vtkPointPicker> wpp = vtkSmartPointer<vtkPointPicker>::New();
    if(rwi->GetAltKey()){
        //cout<<*picked_ptr<<" "<<*picked_pointId_ptr<<endl;
        if(*picked_ptr){
            wpp->Pick(ep[0], ep[1], 0, renderer);
            double *p = wpp->GetPickPosition();
            cout<<p[0]<<" "<<p[1]<<" "<<p[2]<<endl;
           
        }
    }
    //if(rwi->GetControlKey()){
    //    *picked_ptr = false;
    //}
}

void TestAddNodeCommand::Execute(vtkObject *caller, unsigned long eventId, void *callDada){
    vtkRenderWindowInteractor *rwi = vtkRenderWindowInteractor::SafeDownCast(caller);
    int *ep = rwi->GetEventPosition();
    cell_picker->Pick(ep[0], ep[1], 0, renderer);
    vtkIdType cell_id = cell_picker->GetCellId(); 
    if(cell_id != -1){
        *picked_ptr = true;
        if(*picked_pointId_ptr != -1){
            double *cur_color = points_poly_data->GetCellData()->GetScalars()->GetTuple(*picked_pointId_ptr);
            if(static_cast<int>(cur_color[0]) == 255 && static_cast<int>(cur_color[1]) == 0 && static_cast<int>(cur_color[2]) == 0){
                points_poly_data->GetCellData()->GetScalars()->SetTuple3(*picked_pointId_ptr, 0, 255, 0);
            }else{
                points_poly_data->GetCellData()->GetScalars()->SetTuple3(*picked_pointId_ptr, 255, 0, 0);
            }        
            points_poly_data->GetCellData()->GetScalars()->Modified();
        }
        *picked_pointId_ptr = cell_id;
        cout<<cell_id<<endl;
        double *cur_color = points_poly_data->GetCellData()->GetScalars()->GetTuple(cell_id);
        double *moved_cor = points_poly_data->GetCell(cell_id)->GetPoints()->GetPoint(0);

        //vtkSmartPointer<vtkLine> tmp_line = vtkSmartPointer<vtkLine>::New();
        //tmp_line->GetPointIds()->SetId(0, 0);
        //tmp_line->GetPointIds()->SetId(1, 1);
        //vtkSmartPointer<vtkCellArray> tmp_cellarray = vtkSmartPointer<vtkCellArray>::New();
        //tmp_cellarray->InsertNextCell(tmp_line);
        //vtkSmartPointer<vtkPoints> tmp_points = vtkSmartPointer<vtkPoints>::New();
        //tmp_points->SetNumberOfPoints(2);
        //tmp_points->InsertNextPoint(1, 1, 1);
        //tmp_points->InsertNextPoint(0, 0, 0);
        //moved_line->SetPoints(tmp_points);
        //moved_line->SetLines(tmp_cellarray);
        vtkSmartPointer<vtkCubeSource> s = vtkSmartPointer<vtkCubeSource>::New();
        s->SetCenter(moved_cor[0], moved_cor[1], moved_cor[2]);
        s->SetXLength(1.0);
        s->SetYLength(1.0);
        s->SetZLength(1.0);
        vtkSmartPointer<vtkPolyDataMapper> tmp_mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
        tmp_mapper->SetInput(s->GetOutput());
        if(moved_actor){
            renderer->RemoveActor(moved_actor);
        }else{
            cout<<"qqqq"<<endl;
        }
        //moved_actor = vtkSmartPointer<vtkActor>::New();
        moved_actor->SetMapper(tmp_mapper);
        moved_actor->GetProperty()->SetColor(255, 255, 0);
        moved_actor->GetProperty()->SetRepresentationToWireframe();
        cout<<moved_cor[0]<<" "<<moved_cor[1]<<" "<<moved_cor[2]<<endl;
        cout<<cur_color[0]<<" "<<cur_color[1]<<" "<<cur_color[2]<<endl;
        if(static_cast<int>(cur_color[0]) == 255 && static_cast<int>(cur_color[1]) == 0 && static_cast<int>(cur_color[2]) == 0){
            points_poly_data->GetCellData()->GetScalars()->SetTuple3(cell_id, 0, 255, 0);
        }else{
            points_poly_data->GetCellData()->GetScalars()->SetTuple3(cell_id, 255, 0, 0);
        }
        points_poly_data->GetCellData()->GetScalars()->Modified();
        renderer->AddActor(moved_actor);
        //renderer->ResetCamera();
        rwi->Render();
    }
}

void TestLeftButtonRelease::Execute(vtkObject *caller, unsigned long eventId, void *callData){
    vtkInteractorStyleTrackballCamera *rwi = vtkInteractorStyleTrackballCamera::SafeDownCast(caller);
    cout<<"ssss"<<endl;
    if(*picked_ptr){
        *picked_ptr = false;
    }
}

void TestStyleKeyPressCommand::Execute(vtkObject *caller, unsigned long eventId, void *callData){
    vtkInteractorStyleTrackballCamera *istc = vtkInteractorStyleTrackballCamera::SafeDownCast(caller);
    if(moved_actor){
        cout<<"eeeeeee"<<endl;
    }else{
        cout<<"!!!!!!!!!!!!!!!!!!"<<endl;
    }
    
    
    char *key_sym = istc->GetInteractor()->GetKeySym();
    cout<<key_sym<<endl;
    if(strcmp(key_sym, "m") == 0){
        *move_mode = !(*move_mode);
        cout<<*move_mode<<endl;
    
    }
    if(*move_mode){
        if(strcmp(key_sym, "Up") == 0){
            if(moved_actor){
                cout<<"ssss"<<endl;
                moved_actor->AddPosition(0, 1, 0);
            }
        }
        if(strcmp(key_sym, "Down") == 0){
            if(moved_actor){
                moved_actor->AddPosition(0, -1, 0);
            }
        }
        if(strcmp(key_sym, "Left") == 0){
            if(moved_actor){
                moved_actor->AddPosition(1, 0, 0);
            }
        }
        if(strcmp(key_sym, "Right") == 0){
            if(moved_actor){
                moved_actor->AddPosition(-1, 0, 0);
            }
        }       
    }
    istc->GetInteractor()->Render();
}


vtkStandardNewMacro(TestVertex);
TestVertex::TestVertex(){

}
TestVertex::~TestVertex(){

}


vtkStandardNewMacro(TestActor);
TestActor::TestActor(){
}
TestActor::~TestActor(){
}


TestKeyCommand::TestKeyCommand(){
}
TestKeyCommand::~TestKeyCommand(){
}


void TestKeyCommand::Execute(vtkObject *caller, unsigned long eventId, void *callData){
    vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkRenderWindowInteractor::SafeDownCast(caller);
    vtkSmartPointer<vtkRenderer> ren = iren->GetRenderWindow()->GetRenderers()->GetFirstRenderer();
    vtkSmartPointer<vtkAreaPicker> areaPicker = vtkSmartPointer<vtkAreaPicker>::New();
    char keyPress = iren->GetKeyCode();
    cout<<keyPress<<endl;
    int eventPosition[2];
    iren->GetEventPosition(eventPosition);
    switch (keyPress)
    {
        case 'a':
        case 'A':
        {
            areaPicker->AreaPick(0, 0, iren->GetRenderWindow()->GetSize()[0], iren->GetRenderWindow()->GetSize()[1], ren);
            cout<<areaPicker->GetProp3Ds()->GetNumberOfItems()<<endl;
            vtkSmartPointer<vtkProp3DCollection> propCollection = areaPicker->GetProp3Ds();
            propCollection->InitTraversal();
            vtkSmartPointer<vtkProp3D> prop3D = propCollection->GetNextProp3D();
            double *propPosition;
            double displayPosition[3];
            while(prop3D){
                propPosition = prop3D->GetCenter();
                cout<<"--------------"<<endl;
                cout<<propPosition[0]<<" "<<propPosition[1]<<" "<<propPosition[2]<<endl;
                ren->SetWorldPoint(propPosition[0], propPosition[1], propPosition[2], 1.0);
                ren->WorldToDisplay();
                ren->GetDisplayPoint(displayPosition);
                cout<<displayPosition[0]<<" "<<displayPosition[1]<<" "<<displayPosition[2]<<endl;
                cout<<"####################"<<endl;
                prop3D = propCollection->GetNextProp3D();
            }
            break;       
        }
        
        case 'B':
        case 'b':
        {
            *ptrDrawFlag = ! (*ptrDrawFlag);
            if(*ptrDrawFlag){
                cout<<"Enter Draw Mode!"<<endl;
            }else{
                cout<<"Leave Draw Mode!"<<endl;
                *ptrMovingFlag = false;
                imageTracer->Off();
            }
            break;
        }
        
        case 'C':
        case 'c':
        {
            if(*ptrDrawFlag){
                
                areaPicker->AreaPick(0, 0, iren->GetRenderWindow()->GetSize()[0], iren->GetRenderWindow()->GetSize()[1], ren);
                cout<<areaPicker->GetFrustum()->GetNumberOfPlanes()<<endl;
                vtkSmartPointer<vtkPoints> points = areaPicker->GetClipPoints();
                vtkSmartPointer<vtkCellArray> polyCells = vtkSmartPointer<vtkCellArray>::New();
                polyCells->InsertNextCell(4);
                polyCells->InsertCellPoint(0);
                polyCells->InsertCellPoint(4);
                polyCells->InsertCellPoint(6);
                polyCells->InsertCellPoint(2);
                double p[3];
                points->GetPoint(0, p);
                cout<<p[0]<<" "<<p[1]<<" "<<p[2]<<endl;
                points->GetPoint(2, p);
                cout<<p[0]<<" "<<p[1]<<" "<<p[2]<<endl;
                points->GetPoint(4, p);
                cout<<p[0]<<" "<<p[1]<<" "<<p[2]<<endl;
                points->GetPoint(6, p);
                cout<<p[0]<<" "<<p[1]<<" "<<p[2]<<endl;
                vtkSmartPointer<vtkPolyData> poly = vtkSmartPointer<vtkPolyData>::New();
                poly->SetPoints(points);
                poly->SetPolys(polyCells);
                vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
                mapper->SetInput(poly);
                vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
                actor->SetMapper(mapper);
                actor->GetProperty()->SetOpacity(0.4);
                //actor->GetProperty()->SetColor(1, 0, 0);
                imageTracer->SetViewProp(actor);

                //imageTracer->GetLineProperty()->SetOpacity(1.0);
                imageTracer->On();
                cout<<imageTracer->GetNumberOfHandles()<<endl;
                ren->AddActor(actor);
                iren->Render();          
            }

            break;
        }
        
        
        case 'D':
        case 'd':
        {
            
        
        
        
        
            break;
        }
        
        
    }
}

void TestMoveCommand::Execute( vtkObject *caller, unsigned long eventId, void *callData )
{
    vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkRenderWindowInteractor::SafeDownCast(caller);
    vtkSmartPointer<vtkRenderer> ren = iren->GetRenderWindow()->GetRenderers()->GetFirstRenderer();
    vtkSmartPointer<vtkAreaPicker> areaPicker = vtkSmartPointer<vtkAreaPicker>::New();
    areaPicker->AreaPick(0, 0, iren->GetRenderWindow()->GetSize()[0], iren->GetRenderWindow()->GetSize()[1], ren);
    int *eventPosition = iren->GetEventPosition();
    if(*ptrDrawModeFlag){
        //cout<<"Start To Draw!"<<endl;
    }else{
        //cout<<"Can Not Draw!"<<endl;
    }
}

TestMoveCommand::TestMoveCommand()
{

}

TestMoveCommand::~TestMoveCommand()
{

}

void TestLeftButtonPressCommand::Execute( vtkObject *caller, unsigned long eventId, void *callData )
{
    vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkRenderWindowInteractor::SafeDownCast(caller);
    
    
}

TestLeftButtonPressCommand::TestLeftButtonPressCommand()
{

}

TestLeftButtonPressCommand::~TestLeftButtonPressCommand()
{

}
