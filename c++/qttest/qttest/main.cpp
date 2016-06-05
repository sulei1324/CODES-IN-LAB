#include "qttest.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qttest w;
    w.show();
    cout<<"sss"<<endl;
    return a.exec();
}
