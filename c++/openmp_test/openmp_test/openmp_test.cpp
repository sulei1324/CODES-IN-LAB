// openmp_test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <omp.h>
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
int _tmain(int argc, _TCHAR* argv[])

{
    #pragma omp parallel num_threads(4)
    {
        cout<<"hello, "<<omp_get_thread_num()<<endl;
	}
	#pragma omp parallel for num_threads(6) 
	for(int i = 0; i < 3; ++i){
	    cout<<i<<" in "<<omp_get_thread_num()<<endl;
	    int j = 200;
	    for(int k = 0; k < 2; k ++){
	        cout<<j<<" of "<<i<<" "<<omp_get_thread_num()<<endl;
	        j ++;
	    }
	}
	char a(' ');
	cin>>a;
	return 0;
}

