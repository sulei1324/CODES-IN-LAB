#ifndef TESTSTYLE_H
#define TESTSTYLE_H

#include <QtGui/QApplication>
#include <vtkActor.h>
#include <vtkSphereSource.h>
#include <vtkCubeSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkLine.h>
#include <vtkCellArray.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyLine.h>
#include <vtkProperty.h>
#include <vtkVertex.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <iostream>
#include <QDebug>
#include <vtkCommand.h>
#include <vtkObject.h>
#include <vtkCellPicker.h>
#include <vtkPointPicker.h>
#include <vtkVertex.h>
#include "vtkObjectFactory.h"
#include "vtkCell.h"
#include "vtkCollection.h"
#include "vtkMath.h"
#include "vtkImageTracerWidget.h"
#include "vtkImageActor.h"
#include "vtkImageData.h"
#include "vtkImageCanvasSource2D.h"
#include "vtkImageDataGeometryFilter.h"
#include "vtkCubeSource.h"
#include <set>
#include <algorithm>
#include <vtkUnsignedCharArray.h>
#include <vtkCellData.h>
#include <vtkWorldPointPicker.h>
#include <vtkActorCollection.h>
#include <vtkAssembly.h>
#include <vtkTransform.h>
#include <vtkTransformFilter.h>
#include <vtkRendererCollection.h>
#include <vtkAreaPicker.h>
#include <vtkProp3DCollection.h>
#include <vtkProp3D.h>
#include <vtkAppendPolyData.h>
#include <vtkPlanes.h>
#include <vtkPlane.h>
#include <vtkPlaneSource.h>
#include <vtkExtractSelectedFrustum.h>
#include <vtkCallbackCommand.h>
#include <vtkImageData.h>
#include <vtkImageActor.h>
using namespace std;
#define vtk_spnew(type, var) vtkSmartPointer<type> var = vtkSmartPointer<type>::New()
#define vtk_sp(type, var) vtkSmartPointer<type> var
#define vtk_new(type) vtkSmartPointer<type>::New()

class TestStyle: public vtkInteractorStyleTrackballCamera{
public:
  static TestStyle* New();
  vtkTypeMacro(TestStyle, vtkInteractorStyleTrackballCamera);
  virtual void OnLeftButtonDown();
};

class TestCommand: public vtkCommand{
public:
    TestCommand();
    static TestCommand *New();
    virtual void Execute(vtkObject *caller, unsigned long eventId, void *callData);
    void SetCellPicker(vtkSmartPointer<vtkCellPicker> cp){cell_picker = cp;}
    void SetPointerPicker(vtkSmartPointer<vtkPointPicker> pp){point_picker = pp;}
    void SetRenderer(vtkSmartPointer<vtkRenderer> r){ren = r;}
    void SetPointsPolyData(vtkSmartPointer<vtkPolyData> &pd){points_poly_data = pd;}
    void SetCellsPolyData(vtkSmartPointer<vtkPolyData> &pd){cells_poly_data = pd;}
    void SetCollection(vtkSmartPointer<vtkActorCollection> &c){co = c;}
    
private:
    vtkSmartPointer<vtkActorCollection> co;
    vtkSmartPointer<vtkCellPicker> cell_picker;
    vtkSmartPointer<vtkPointPicker> point_picker;
    vtkSmartPointer<vtkRenderer> ren;
    vtkSmartPointer<vtkPolyData> points_poly_data;
    vtkSmartPointer<vtkPolyData> cells_poly_data;
};

class TestVtkPoint: public vtkVertex{
public:
    vtkTypeMacro(TestVtkPoint, vtkVertex);
    static TestVtkPoint *New();
    vtkIdType s_id;

protected:
    TestVtkPoint();
    ~TestVtkPoint();

private:
    TestVtkPoint(const TestVtkPoint&);
    void operator=(const TestVtkPoint&);
};


class TestImagePathCommand: public vtkCommand{
public:
    vtkTypeMacro(TestImagePathCommand, vtkCommand);
    static TestImagePathCommand *New(){return new TestImagePathCommand;}
    virtual void Execute(vtkObject *caller, unsigned long eventId, void *callData);
    void SetActor(vtkSmartPointer<vtkActor> a){actor = a;}
    void SetRenderer(vtkSmartPointer<vtkRenderer> r){renderer = r;}
    void SetPickedActor(vtkSmartPointer<vtkActor> a){picked_actor = a;}
    void SetInteractor(vtkSmartPointer<vtkRenderWindowInteractor> i){rwi = i;}
    void SetCellPicker(vtkSmartPointer<vtkCellPicker> cp){cell_picker = cp;}
    void SetPointsPolyData(vtkSmartPointer<vtkPolyData> &pd){points_poly_data = pd;}

private:
    vtkSmartPointer<vtkActor> actor, picked_actor;
    vtkSmartPointer<vtkCellPicker> cell_picker;
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkRenderWindowInteractor> rwi;
    vtkSmartPointer<vtkPolyData> points_poly_data;
};


class TestAddNodeCommand: public vtkCommand{
public:
    vtkTypeMacro(TestAddNodeCommand, vtkCommand);
    static TestAddNodeCommand *New(){return new TestAddNodeCommand;}
    virtual void Execute(vtkObject *caller, unsigned long eventId, void *callData);
    void SetActor(vtkSmartPointer<vtkActor> a){actor = a;}
    void SetRenderer(vtkSmartPointer<vtkRenderer> r){renderer = r;}
    void SetPickedActor(vtkSmartPointer<vtkActor> a){picked_actor = a;}
    void SetInteractor(vtkSmartPointer<vtkRenderWindowInteractor> i){rwi = i;}
    void SetCellPicker(vtkSmartPointer<vtkCellPicker> cp){cell_picker = cp;}
    void SetPointsPolyData(vtkSmartPointer<vtkPolyData> &pd){points_poly_data = pd;}
    void SetPickFlag(bool *p, vtkIdType *id, vtkSmartPointer<vtkActor> l){picked_ptr = p; picked_pointId_ptr = id; moved_actor = l;}
private:
    bool *picked_ptr;
    vtkSmartPointer<vtkActor> moved_actor;
    vtkIdType *picked_pointId_ptr;
    vtkSmartPointer<vtkActor> actor, picked_actor;
    vtkSmartPointer<vtkCellPicker> cell_picker;
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkRenderWindowInteractor> rwi;
    vtkSmartPointer<vtkPolyData> points_poly_data;
};


class TestMove: public vtkCommand{
public:
    vtkTypeMacro(TestMove, vtkCommand);
    static TestMove *New(){return new TestMove;}
    virtual void Execute(vtkObject *caller, unsigned long eventId, void *callData);
    void SetActor(vtkSmartPointer<vtkActor> a){actor = a;}
    void SetRenderer(vtkSmartPointer<vtkRenderer> r){renderer = r;}
    void SetPickedActor(vtkSmartPointer<vtkActor> a){picked_actor = a;}
    void SetInteractor(vtkSmartPointer<vtkRenderWindowInteractor> i){rwi = i;}
    void SetCellPicker(vtkSmartPointer<vtkCellPicker> cp){cell_picker = cp;}
    void SetPointsPolyData(vtkSmartPointer<vtkPolyData> &pd){points_poly_data = pd;}
    void SetPickFlag(bool *p, vtkIdType *id){picked_ptr = p; picked_pointId_ptr = id;}
private:
    bool *picked_ptr;
    vtkIdType *picked_pointId_ptr;
    vtkSmartPointer<vtkActor> actor, picked_actor;
    vtkSmartPointer<vtkCellPicker> cell_picker;
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkRenderWindowInteractor> rwi;
    vtkSmartPointer<vtkPolyData> points_poly_data;
};


class TestLeftButtonRelease: public vtkCommand{
public:
    vtkTypeMacro(TestLeftButtonRelease, vtkCommand);
    static TestLeftButtonRelease *New(){return new TestLeftButtonRelease;}
    virtual void Execute(vtkObject *caller, unsigned long eventId, void *callData);
    void SetActor(vtkSmartPointer<vtkActor> a){actor = a;}
    void SetRenderer(vtkSmartPointer<vtkRenderer> r){renderer = r;}
    void SetPickedActor(vtkSmartPointer<vtkActor> a){picked_actor = a;}
    void SetInteractor(vtkSmartPointer<vtkRenderWindowInteractor> i){rwi = i;}
    void SetCellPicker(vtkSmartPointer<vtkCellPicker> cp){cell_picker = cp;}
    void SetPointsPolyData(vtkSmartPointer<vtkPolyData> &pd){points_poly_data = pd;}
    void SetPickFlag(bool *p, vtkIdType *id){picked_ptr = p; picked_pointId_ptr = id;}
private:
    bool *picked_ptr;
    vtkIdType *picked_pointId_ptr;
    vtkSmartPointer<vtkActor> actor, picked_actor;
    vtkSmartPointer<vtkCellPicker> cell_picker;
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkRenderWindowInteractor> rwi;
    vtkSmartPointer<vtkPolyData> points_poly_data;
};


class TestStyleKeyPressCommand: public vtkCommand{
public:
    vtkTypeMacro(TestStyleKeyPressCommand, vtkCommand);
    static TestStyleKeyPressCommand *New(){return new TestStyleKeyPressCommand;}
    virtual void Execute(vtkObject *caller, unsigned long eventId, void *callData);
    void SetMoveMode(bool *m){move_mode = m;}
    void SetMovedActor(vtkSmartPointer<vtkActor> a){moved_actor = a;}

private:
    bool *move_mode;
    vtkSmartPointer<vtkActor> moved_actor;
};

class TestVertex: public vtkVertex{
public:
    vtkTypeMacro(TestVertex, vtkVertex);
    static TestVertex *New();
    vtkIdType getActorId(){return actor_id;}
    void setActorId(vtkIdType id){actor_id = id;}
    
protected:
    TestVertex();
    ~TestVertex();
    
private:
    vtkIdType actor_id;
    TestVertex(const TestVertex&);
    void operator=(const TestVertex&);
};

class TestActor: public vtkActor{
public:
    vtkTypeMacro(TestActor, vtkActor);
    static TestActor *New();
    map<vtkIdType, vtkSmartPointer<vtkActor>> picked_map;
    
    
protected:
    TestActor();
    ~TestActor();

private:
    TestActor(const TestActor&);
    void operator=(const TestActor&);
};


class TestKeyCommand: public vtkCommand{
public:
    vtkTypeMacro(TestKeyCommand, vtkCommand);
    static TestKeyCommand *New(){return new TestKeyCommand;}
    void Execute(vtkObject *caller, unsigned long eventId, void *callData);
    void SetDrawFlag(bool *arg){ptrDrawFlag = arg;}
    void SetMovingFlag(bool *arg){ptrMovingFlag = arg;}
    void SetDrawer(vtkSmartPointer<vtkImageTracerWidget> arg){imageTracer = arg;}
    
protected:
    TestKeyCommand();
    ~TestKeyCommand();

private:
    TestKeyCommand(const TestKeyCommand &);
    void operator=(const TestKeyCommand &);
    bool *ptrDrawFlag;
    bool *ptrMovingFlag;
    vtkSmartPointer<vtkImageTracerWidget> imageTracer;
    
};



class TestMoveCommand: public vtkCommand{
public:
    vtkTypeMacro(TestMoveCommand, vtkCommand);
    static TestMoveCommand *New(){return new TestMoveCommand;}
    void Execute(vtkObject *caller, unsigned long eventId, void *callData);
    void SetDrawModeFlag(bool *arg){ptrDrawModeFlag = arg;}
    void SetDrawActor(vtkSmartPointer<vtkActor> arg){drawActor = arg;}
    void SetAppendFilter(vtkSmartPointer<vtkAppendPolyData> arg){appendFilter = arg;}
    void SetMovingFlag(bool *arg){ptrMovingFlag = arg;}
    void SetDrawMapper(vtkSmartPointer<vtkPolyDataMapper> arg){drawMapper = arg;}
    
protected:
    TestMoveCommand();
    ~TestMoveCommand();
    
private:
    TestMoveCommand(const TestMoveCommand &);
    void operator=(const TestMoveCommand &);
    bool *ptrDrawModeFlag;
    bool *ptrMovingFlag;
    vtkSmartPointer<vtkActor> drawActor;
    vtkSmartPointer<vtkAppendPolyData> appendFilter;
    vtkSmartPointer<vtkPolyDataMapper> drawMapper;
    double startPoint[3], *endPoint;
};

class TestLeftButtonPressCommand: public vtkCommand{
public:
    vtkTypeMacro(TestLeftButtonPressCommand, vtkCommand);
    static TestLeftButtonPressCommand *New(){return new TestLeftButtonPressCommand;}
    TestLeftButtonPressCommand();
    ~TestLeftButtonPressCommand();
    void Execute(vtkObject *caller, unsigned long eventId, void *callData);
    
private:
    TestLeftButtonPressCommand(const TestLeftButtonPressCommand &);
    void operator=(const TestLeftButtonPressCommand &);
};

#endif