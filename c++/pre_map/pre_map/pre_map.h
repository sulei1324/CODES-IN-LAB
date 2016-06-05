#ifndef PRE_MAP_H
#define PRE_MAP_H
#include <QThread>
#include <QtGui/QMainWindow>
#include "ui_pre_map.h"
#include <iostream>
#include <QDebug>
#include <QtGui/QFileDialog>
#include <QString>
#include <QVector>
#include <QDir>
#include <QChar>
#include <QTimer>
#include <QTime>
#include <omp.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <highgui.h>
#include <cv.h>
#include "subbor.h"
#include <QList>
#include <QTest>
using namespace std;

class WorkThread;
class CheckThread;


class pre_map : public QMainWindow
{
    Q_OBJECT

public:
    pre_map(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~pre_map();

private:
    Ui::pre_mapClass ui;
    QString src_dir, dst_dir, image_pre, image_suf;
    uint start_serial, end_serial, pro_thick, thread_num, ball_radius, high_brightness;
    float resize_ratio;
    bool args_checked;
    void checkImageNames(vector<QString> &lostImageNames);
    QTimer *timer1, *timer2;
    QTime *time;
    void go2Work();
    int msg_index;
    vector<QString> *msg_list;
    WorkThread *wt;
    CheckThread *ct;
    omp_lock_t *lock1;
    
private slots:
    void on_actionSrc_triggered();
    void on_actionDst_triggered();
    void on_pushButton_clicked();
    void display_time();
    void display_msg();

};

class CheckThread: public QThread{
public:
    void setArgs(QString src, uint s_serial, uint e_serial, vector<QString> *lost_list, QString pre, QString suf);
    void run();

private:
    QString src_dir, img_pre, img_suf;
    uint start_serial, end_serial;
    vector<QString> *lostImageNames;

};

class WorkThread: public QThread{
public:
    void setWidget(pre_map *in_widget){myWidget = in_widget;}
    void setArgs(QString arg1, QString arg2, QString arg3, QString arg4, uint arg5, uint arg6, uint arg7, uint arg8, float arg9, vector<QString> *arg10, uint arg11, uint arg12);
    void run();

private:
    pre_map *myWidget;
    QString image_pre, image_suf, src_dir, dst_dir;
    uint start_serial, end_serial, pro_thick, thread_num, ball_radius, high_brightness;
    float resize_ratio;
    vector<QString> *msg_list;
};
#endif // PRE_MAP_H
