#include "projecter.h"
#include <QtGui/QApplication>
#include <QImageReader>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    projecter w;
    w.show();
    qDebug()<<QImageReader::supportedImageFormats();
    return a.exec();
}
