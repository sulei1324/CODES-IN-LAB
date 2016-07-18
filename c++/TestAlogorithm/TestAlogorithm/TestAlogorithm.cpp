// TestAlogorithm.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <time.h>
#include <iostream>
#include <Windows.h>
#include <vector>
#include <algorithm>
#include "TestClass.h"
#include <memory>
using std::cout;
using std::tr1::shared_ptr;
using std::cin;
using std::endl;
using std::vector;

void funa(){
    
}



int _tmain(int argc, _TCHAR* argv[])
{
    shared_ptr<A> a(new A());
    a->SetTimes(100);l;
    
    shared_ptr<A> b = a;
    cout<<b->GetTimes()<<endl;
    cin.get();
	return 0;
}

