#include "asyncho.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Asyncho w;
    QString workType("Traceeeeeeeeeeeeeeeee!");
    w.show();
    w.emitImageNeed(workType);
    return a.exec();
}
