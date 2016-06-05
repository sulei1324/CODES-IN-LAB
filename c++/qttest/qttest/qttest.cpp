#include "qttest.h"

qttest::qttest(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
{
    ui.setupUi(this);
    timer1 = new QTimer(this);
    time = new QTime();
    text_list = new QList<QString>();
    timer1->setInterval(100);
    //lock1 = new omp_lock_t();
    //omp_init_lock(lock1);
    showed_num = 0;
    connect(timer1, SIGNAL(timeout()), this, SLOT(showTime()));
    connect(this, SIGNAL(textListChanged()), this, SLOT(showText1()));
}

void qttest::showText1(){
    int l = text_list->length();
    QString showed_text;
    if(showed_num < l){
        showed_text = text_list->at(showed_num);
        ++showed_num;
    }
    ui.textBrowser->append(showed_text);
}



void qttest::appendTextList(QString &s1){
    text_list->append(s1);
    emit textListChanged();
}

qttest::~qttest()
{
    //omp_destroy_lock(lock1);
    //delete lock1;
    delete timer1;
    delete time;
    delete text_list;
}

void qttest::on_pushButton_clicked(){
    timer1->start();
    time->start();
    Thread1 *t1 = new Thread1();
    t1->setWidget(this);
    t1->start();
    
}

void qttest::showTime(){
    int time_e = time->elapsed();
    ui.lcdNumber->display(time_e/1000);
}


void Thread1::run(){
     //omp_lock_t lock1;
     //omp_init_lock(&lock1);
#pragma omp parallel for num_threads(8)
    for(int i = 1; i < 100; ++i){
        QTest::qSleep(1000);
        //omp_set_lock(&lock1);
        int j = omp_get_thread_num();
        QString s;
        s.setNum(j);
        q->appendTextList(s);
        qDebug()<<s;
        //omp_unset_lock(&lock1);
    }
    //omp_destroy_lock(&lock1);
}