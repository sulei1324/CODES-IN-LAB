#ifndef TESTCLASS_H
#define TESTCLASS_H
#include "stdafx.h"
class A{
public:
    A();
    ~A();
    void SetTimes(int arg){times = arg;}
    int GetTimes(){return times;}
    
private:
    int times;
    //void operator=(const A &);
};






#endif


