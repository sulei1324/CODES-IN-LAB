#include "preprocessor.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
    //QApplication a(argc, argv);
    //preprocessor w;
    //w.show();
    //return a.exec();
    cv::Mat image;
    image = cv::imread("1.tif", CV_LOAD_IMAGE_UNCHANGED);
    if( ! image.data){
        qDebug()<<"dddd";       
        return -1;
    }
    cv::namedWindow("AAAAA", cv::WINDOW_AUTOSIZE);
    cv::imshow("AAAAA", image);
    cv::waitKey(0);
    return 0;    
}