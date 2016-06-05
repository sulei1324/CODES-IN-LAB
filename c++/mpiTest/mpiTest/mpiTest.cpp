// mpiTest.cpp : 定义控制台应用程序的入口点。
//

/* 
#include "stdafx.h"
#include <stdio.h>
#include "mpi.h"
 
int main(int argc, char*argv[])
{
       int i=0;
       MPI_Init(&argc,&argv);
       printf("helloworld\n");
       MPI_Finalize();
       

       for(;i<100;i++){
           printf("%d",i);
       }
}
*/

#include "stdafx.h"
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main(int argc, char* argv[]){
    const char* imagename = "00001-1-1.tif";
    Mat img = imread(imagename);
    if(img.empty()){
        fprintf(stderr, "can not load image %s\n", imagename);
        return -1;
    }
    imshow("iamge", img);
    waitKey();
    return 0;

}