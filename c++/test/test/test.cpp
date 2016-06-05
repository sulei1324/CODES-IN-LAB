// test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>
using namespace std;

void main(){
    std::vector<int> a(10);
    std::vector<int>::iterator it = a.begin();
    int i = 1;
    for(it = a.begin(); it != a.end(); ++it){
        *it = i;
        ++i;
    }    
    it = a.begin();
    it += 4;
    std::vector<int> b(a.begin(), it + 1);
    std::vector<int> c(it, a.end());
/*    for(it = b.begin(); it != b.end(); ++it){
        cout<<*it<<endl;
    }
    cout<<"---------------------"<<endl;
    for(it = c.begin(); it != c.end(); ++it){
        cout<<*it<<endl;
    }       */ 
    it  = a.erase(it);
    cout<<*it<<endl;
    a.insert(it, 5);
    for(it = a.begin(); it != a.end(); ++it){
        cout<<*it<<endl;
    }    
    double *g = 0;
    if(g){
    }else{
        cout<<"eeeeeeeesss"<<endl;
    }
    cin.get();
    
    
}