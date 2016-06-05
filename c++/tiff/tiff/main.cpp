#include "stdafx.h"
#include "mostdReader.h"



void main(){
    u_int roi[] = {4800 + 4550, 4800 + 4550 + 1000, 5591 + 10180, 5591 + 10180 + 800, 852, 1250};
    cout<<sizeof(roi) / 4<<endl;
    Mostd d("G:\\sulei\\workplace\\vs\\tiff\\tiff\\test.mostd", 16);
    if(d.loadMostd()){
        cout<<"Load Succeed!"<<endl;
    }
    if(d.setROI(roi)){
        cout<<"Set Succeed!"<<endl;
    }else{
        cout<<"Set Failed!"<<endl;
    }
    d.loadImages();
    char c('e');
    cin.get();
}