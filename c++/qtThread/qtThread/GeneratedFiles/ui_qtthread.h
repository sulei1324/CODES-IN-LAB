/********************************************************************************
** Form generated from reading UI file 'qtthread.ui'
**
** Created: Sun Oct 25 14:33:54 2015
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTTHREAD_H
#define UI_QTTHREAD_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_qtThreadClass
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QLabel *label;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *qtThreadClass)
    {
        if (qtThreadClass->objectName().isEmpty())
            qtThreadClass->setObjectName(QString::fromUtf8("qtThreadClass"));
        qtThreadClass->resize(600, 400);
        centralWidget = new QWidget(qtThreadClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(180, 50, 201, 41));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(130, 150, 311, 151));
        qtThreadClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(qtThreadClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        qtThreadClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(qtThreadClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        qtThreadClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(qtThreadClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        qtThreadClass->setStatusBar(statusBar);

        retranslateUi(qtThreadClass);

        QMetaObject::connectSlotsByName(qtThreadClass);
    } // setupUi

    void retranslateUi(QMainWindow *qtThreadClass)
    {
        qtThreadClass->setWindowTitle(QApplication::translate("qtThreadClass", "qtThread", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("qtThreadClass", "PushButton", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class qtThreadClass: public Ui_qtThreadClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTTHREAD_H
