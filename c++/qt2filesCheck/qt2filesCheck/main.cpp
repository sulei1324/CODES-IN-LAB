#include "qt2filescheck.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qt2filesCheck w;
    w.show();
    //QLabel label;
    //label.setText("hello world \n hello hust");
    //label.setGeometry(300, 300, 400, 400);
    //label.show();
    return a.exec();
}
