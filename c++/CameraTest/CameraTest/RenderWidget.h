#include "stdafx.h"
#ifndef RENDERWIDGET_H
#define RENDERWIDGET_H
#include "TestVtkVolume.h"
#include "MostdTraveller.h"

class SliderCommand: public vtkCommand{
public:
    vtkTypeMacro(SliderCommand, vtkCommand);
    static SliderCommand *New(){return new SliderCommand;}
    void Execute(vtkObject *caller, unsigned long eventId, void *callData);

protected:
    SliderCommand();
    ~SliderCommand();

private:
    SliderCommand(const SliderCommand &);
    void operator=(const SliderCommand &);
};



 



#endif