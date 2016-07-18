#ifndef QTVTKTRACER_H
#define QTVTKTRACER_H

#include <QtGui/QMainWindow>
#include "ui_qtvtktracer.h"
#include "vtkOrientationMarkerWidget.h"
#include "vtkSmartPointer.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkSphereSource.h"
#include "vtkActor.h"
#include "vtkPolyDataMapper.h"
#include "vtkProperty.h"
#include "vtkAxesActor.h"
#include "vtkImageTracerWidget.h"
#include "vtkObject.h"
#include "vtkCallbackCommand.h"
#include "vtkRendererCollection.h"
#define vtk_sp(type, arg) vtkSmartPointer<type> arg
#define vtk_spnew(type, arg) vtkSmartPointer<type> arg = vtkSmartPointer<type>::New()
#define vtk_new(type) vtkSmartPointer<type>::New()

class qtVtkTracer : public QMainWindow
{
    Q_OBJECT

public:
    qtVtkTracer(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~qtVtkTracer();

//private:
    Ui::qtVtkTracerClass ui;
};

#endif // QTVTKTRACER_H
