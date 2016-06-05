#include "qtthread.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qtThread w;
    w.show();
    return a.exec();
}
