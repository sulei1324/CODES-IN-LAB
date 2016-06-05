#include "averagefilterqt.h"
#include "qstring.h"
#include "QDebug"

AverageFilterQt::AverageFilterQt(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
{
    ui.setupUi(this);
}

AverageFilterQt::~AverageFilterQt()
{
}

//void AverageFilterQt::on_openButton_clicked(){
//    QString fileName  = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files (*.png *.jpg *.bmp)"));
//    qDebug()<<"filenames: "<<fileName;
//    image = cv::imread(fileName.toAscii().data());
//
//}