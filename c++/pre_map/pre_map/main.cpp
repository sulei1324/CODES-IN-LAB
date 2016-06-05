#include "pre_map.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    pre_map w;
    w.show();
    return a.exec();
}
