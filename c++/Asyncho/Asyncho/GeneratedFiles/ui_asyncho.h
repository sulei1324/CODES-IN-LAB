/********************************************************************************
** Form generated from reading UI file 'asyncho.ui'
**
** Created: Mon Jul 18 14:57:58 2016
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ASYNCHO_H
#define UI_ASYNCHO_H

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

class Ui_AsynchoClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *AsynchoClass)
    {
        if (AsynchoClass->objectName().isEmpty())
            AsynchoClass->setObjectName(QString::fromUtf8("AsynchoClass"));
        AsynchoClass->resize(600, 400);
        menuBar = new QMenuBar(AsynchoClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        AsynchoClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(AsynchoClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        AsynchoClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(AsynchoClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        AsynchoClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(AsynchoClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        AsynchoClass->setStatusBar(statusBar);

        retranslateUi(AsynchoClass);

        QMetaObject::connectSlotsByName(AsynchoClass);
    } // setupUi

    void retranslateUi(QMainWindow *AsynchoClass)
    {
        AsynchoClass->setWindowTitle(QApplication::translate("AsynchoClass", "Asyncho", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AsynchoClass: public Ui_AsynchoClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ASYNCHO_H
