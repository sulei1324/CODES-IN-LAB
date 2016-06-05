#include "averagefilterqt.h"
#include <QtGui/QApplication>
#include <iostream>
#include "opencv2/opencv.hpp"
#include <QDir>

using namespace std;
using namespace cv;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AverageFilterQt w;
    w.show();
    return a.exec();
}


