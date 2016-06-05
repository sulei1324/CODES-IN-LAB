#ifndef QT2FILESCHECK_H
#define QT2FILESCHECK_H

#include <QtGui/QMainWindow>
#include <QString>
#include "ui_qt2filescheck.h"

class qt2filesCheck : public QMainWindow
{
    Q_OBJECT

public:
    qt2filesCheck(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~qt2filesCheck();


public slots:
    void checkFilesIn2File();
    void saveResult();

    

private:
    Ui::qt2filesCheckClass ui;
    QString result; 
};

#endif // QT2FILESCHECK_H
