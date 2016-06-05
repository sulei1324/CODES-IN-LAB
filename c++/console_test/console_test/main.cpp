
#include <QtCore/QCoreApplication>
#include <QtGui/QApplication>
#include <QtGui/QLabel>
#include <iostream>

int main(int argc, char *argv[])
{
     QApplication app(argc, argv);
     QLabel label("ddddd");
     label.show();
     std::cout<<"sss"<<std::endl;
     return app.exec();
}
