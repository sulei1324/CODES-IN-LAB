#ifndef PROJECTER_H
#define PROJECTER_H

#include <QtGui/QMainWindow>
#include "ui_projecter.h"
#include <QDebug>
#include "QString"
#include <QThread>
#include "myThread.h"
#include <opencv2\opencv.hpp>
#include <QImage>
#include <QPixmap>
#include <QtPlugin>
//Q_IMPORT_PLUGIN(qjpegd4)


class projecter : public QMainWindow
{
    Q_OBJECT

public:
    projecter(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~projecter();

private slots:
    void projectRun();
    void lineEdit_changed(const QString &);
    void lineEdit_2_changed(const QString &);
    void lineEdit_3_changed(const QString &);
    void lineEdit_4_changed(const QString &);
    void lineEdit_5_changed(const QString &);
    void lineEdit_6_changed(const QString &);
    void lineEdit_7_changed(const QString &);




private:
    Ui::projecterClass ui;
    QString src;
    QString dst;
    QString thick_str;
    QString begin_str;
    QString end_str;
    QString pre;
    QString post;
    int thick;
    int begin_z;
    int end_z;
    

};

#endif // PROJECTER_H
