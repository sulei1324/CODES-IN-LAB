#include "qtvtktracer.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qtVtkTracer w;
    vtk_spnew(vtkInteractorStyleTrackballCamera, cameraStyle);
    vtk_spnew(vtkActor, actor);
    vtk_spnew(vtkPolyDataMapper, mapper);
    vtk_spnew(vtkSphereSource, source);
    vtk_spnew(vtkOrientationMarkerWidget, marker);
    vtk_spnew(vtkAxesActor, axes);
    vtk_spnew(vtkImageTracerWidget, tracer);
    vtk_spnew(vtkCallbackCommand, com);
    vtk_spnew(vtkRenderer, ren);
    vtk_spnew(vtkRenderWindowInteractor, iren);
    source->SetRadius(10.0);
    mapper->SetInput(source->GetOutput());
    actor->SetMapper(mapper);
    ren->AddActor(actor);
    w.ui.qvtkWidget->GetRenderWindow()->AddRenderer(ren);
    //ui.qvtkWidget->GetRenderWindow()->SetInteractor(iren);
    tracer->SetViewProp(actor);
    cout<<w.ui.qvtkWidget->GetInteractor()->GetClassName()<<endl;
    tracer->SetInteractor(w.ui.qvtkWidget->GetInteractor());

    tracer->On();
    cout<<"   dddd"<<tracer->GetInteraction()<<endl;
    tracer->InteractionOff();
    cout<<tracer->GetInteraction()<<endl;
    tracer->InteractionOn();
    cout<<tracer->GetInteraction()<<endl;
    w.show();
    return a.exec();
}
