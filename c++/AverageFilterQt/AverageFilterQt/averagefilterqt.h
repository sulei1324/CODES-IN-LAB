#ifndef AVERAGEFILTERQT_H
#define AVERAGEFILTERQT_H

#include <QtGui/QMainWindow>
#include "ui_averagefilterqt.h"
#include <QWidget>
#include <QImage>
#include <QFileDialog>

class AverageFilterQt : public QMainWindow
{
    Q_OBJECT

public:
    AverageFilterQt(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~AverageFilterQt();
    
private slots:
    void on_openButton_clicked();



private:
    Ui::AverageFilterQtClass ui;
};

#endif // AVERAGEFILTERQT_H
