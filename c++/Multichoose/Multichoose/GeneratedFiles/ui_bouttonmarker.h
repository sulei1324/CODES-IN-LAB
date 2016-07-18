/********************************************************************************
** Form generated from reading UI file 'bouttonmarker.ui'
**
** Created: Wed Jun 8 11:05:26 2016
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BOUTTONMARKER_H
#define UI_BOUTTONMARKER_H

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

QT_BEGIN_NAMESPACE

class Ui_BouttonMarkerClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *BouttonMarkerClass)
    {
        if (BouttonMarkerClass->objectName().isEmpty())
            BouttonMarkerClass->setObjectName(QString::fromUtf8("BouttonMarkerClass"));
        BouttonMarkerClass->resize(600, 400);
        menuBar = new QMenuBar(BouttonMarkerClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        BouttonMarkerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(BouttonMarkerClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        BouttonMarkerClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(BouttonMarkerClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        BouttonMarkerClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(BouttonMarkerClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        BouttonMarkerClass->setStatusBar(statusBar);

        retranslateUi(BouttonMarkerClass);

        QMetaObject::connectSlotsByName(BouttonMarkerClass);
    } // setupUi

    void retranslateUi(QMainWindow *BouttonMarkerClass)
    {
        BouttonMarkerClass->setWindowTitle(QApplication::translate("BouttonMarkerClass", "BouttonMarker", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class BouttonMarkerClass: public Ui_BouttonMarkerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BOUTTONMARKER_H
