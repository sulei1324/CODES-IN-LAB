#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <cstring>
using namespace std;


//void main(){
//    FILE *file1;
//    char buffer[512];
//    size_t get_size;
//    char c;
//    file1 = fopen("G115.docx", "r");
//    while(true){
//        get_size = fread(buffer, 1, 512, file1);
//        cout<<get_size<<endl;
//        if(get_size != 512){
//            break;
//        }
//
//    }
//    cin>>c;
//
//
//}


//int main(){
//    fstream file1;
//    char buffer[512];
//    char c;
//    cout<<sizeof(char)<<endl;
//    file1.open("22.tar", ios::in  | ios::binary);
//    file1.seekg(0, ios::end);
//    string::size_type file_size = file1.tellg();
//    cout<<file_size<<endl;
//    file1.seekg(0, ios::beg);
//    for(;;){
//        file1.read(buffer, 512);
//        cout<<file1.gcount()<<endl;
//        cout<<file1.tellg()<<endl;
//        cout<<buffer<<endl;
//        if(file1.eof()){
//            break;
//        }
//
//    }
//    file1.close();
//    cin>>c;
//    return 0;
//}
