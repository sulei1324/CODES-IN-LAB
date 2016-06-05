#include "projecter.h"

projecter::projecter(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
{
    ui.setupUi(this);
    //cv::c
    //cv::Mat image2 = cv::imread("1.bmp", CV_LOAD_IMAGE_COLOR);
    //QString output1, output2, output3, output4;
    //qDebug()<<"sssss";
    //qDebug()<<output1.setNum(image2.cols)<<"  "<<output2.setNum(image2.channels())<<"  "<<output3.setNum(image2.rows)<<"  "<<output4.setNum(image2.type());
    QString image_src("1.jpg");
    QImage *image1 = new QImage(image_src);
    if(image1->load(image_src)){
        ui.label_8->setText("hhhhhh");
        ui.label_8->setPixmap(QPixmap::fromImage(*image1));
    }else{
        //ui.label_8->setText(image_src);
        ui.label_8->setText("eeeee");
    }
    connect(ui.pushButton, SIGNAL(clicked()), SLOT(projectRun()));
    connect(ui.lineEdit, SIGNAL(textChanged(const QString &)), SLOT(lineEdit_changed(const QString &)));
    connect(ui.lineEdit_2, SIGNAL(textChanged(const QString &)), SLOT(lineEdit_2_changed(const QString &)));
    connect(ui.lineEdit_3, SIGNAL(textChanged(const QString &)), SLOT(lineEdit_3_changed(const QString &)));
    connect(ui.lineEdit_4, SIGNAL(textChanged(const QString &)), SLOT(lineEdit_4_changed(const QString &)));
    connect(ui.lineEdit_5, SIGNAL(textChanged(const QString &)), SLOT(lineEdit_5_changed(const QString &)));
    connect(ui.lineEdit_6, SIGNAL(textChanged(const QString &)), SLOT(lineEdit_6_changed(const QString &)));
    connect(ui.lineEdit_7, SIGNAL(textChanged(const QString &)), SLOT(lineEdit_7_changed(const QString &)));
    
}

projecter::~projecter()
{

}


void projecter::projectRun(){
    QString a = "sssss";
    ui.label_8->setText("1111");
   cv::Mat i = cv::imread(".\\Resources\\00001-1-2.tif", CV_LOAD_IMAGE_UNCHANGED);
    //QImage *image1 = new QImage;
    //image1->load(".\\Resources\\00001-1-1.tif");
    //ui.label_8->setPixmap(QPixmap::fromImage(*image1));
    myThread mt;
    mt.run(a);

}

void projecter::lineEdit_changed(const QString &t){
    pre = t;
    ui.label_8->setText(pre);

}


void projecter::lineEdit_2_changed(const QString &t){
    post = t;
    ui.label_8->setText(post);

}

void projecter::lineEdit_3_changed(const QString &t){
    thick_str = t;
    thick = thick_str.toInt();
    ui.label_8->setText(thick_str);

}

void projecter::lineEdit_4_changed(const QString &t){
    begin_str = t;
    begin_z = begin_str.toInt();
    ui.label_8->setText(begin_str);

}

void projecter::lineEdit_5_changed(const QString &t){
    end_str = t;
    end_z = end_str.toInt();
    ui.label_8->setText(end_str);

}

void projecter::lineEdit_6_changed(const QString &t){
    src = t;
    ui.label_8->setText(src);

}

void projecter::lineEdit_7_changed(const QString &t){
    dst = t;
    ui.label_8->setText(dst);

}