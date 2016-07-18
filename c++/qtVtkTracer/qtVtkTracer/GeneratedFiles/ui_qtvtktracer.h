/********************************************************************************
** Form generated from reading UI file 'qtvtktracer.ui'
**
** Created: Mon Jun 13 17:37:02 2016
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTVTKTRACER_H
#define UI_QTVTKTRACER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>
#include "QVTKWidget.h"

QT_BEGIN_NAMESPACE

class Ui_qtVtkTracerClass
{
public:
    QWidget *centralWidget;
    QVTKWidget *qvtkWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *qtVtkTracerClass)
    {
        if (qtVtkTracerClass->objectName().isEmpty())
            qtVtkTracerClass->setObjectName(QString::fromUtf8("qtVtkTracerClass"));
        qtVtkTracerClass->resize(605, 415);
        centralWidget = new QWidget(qtVtkTracerClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        qvtkWidget = new QVTKWidget(centralWidget);
        qvtkWidget->setObjectName(QString::fromUtf8("qvtkWidget"));
        qvtkWidget->setGeometry(QRect(0, 10, 611, 421));
        qtVtkTracerClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(qtVtkTracerClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 605, 23));
        qtVtkTracerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(qtVtkTracerClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        qtVtkTracerClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(qtVtkTracerClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        qtVtkTracerClass->setStatusBar(statusBar);

        retranslateUi(qtVtkTracerClass);

        QMetaObject::connectSlotsByName(qtVtkTracerClass);
    } // setupUi

    void retranslateUi(QMainWindow *qtVtkTracerClass)
    {
        qtVtkTracerClass->setWindowTitle(QApplication::translate("qtVtkTracerClass", "qtVtkTracer", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class qtVtkTracerClass: public Ui_qtVtkTracerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTVTKTRACER_H
