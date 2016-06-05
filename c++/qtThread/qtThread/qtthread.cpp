#include "qtthread.h"

qtThread::qtThread(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
{
    str_list<<"1111"<<"22222"<<"333"<<"444";
    ui.setupUi(this);
    connect(ui.pushButton, SIGNAL(clicked()), SLOT(do_job()));
}

qtThread::~qtThread()
{

}

void qtThread::do_job(){
    qDebug()<<"hahaha";
    ui.label->setText("navie!!!");
    Mm *mt = new Mm();
    connect(mt, SIGNAL(finished()), mt, SLOT(deleteLater()));
    mt->start();

}

void qtThread::openThread(){
    Mm mt;
    mt.start();
}

void Mm::run(){
    qDebug()<<"too young, too sample!!!";

}