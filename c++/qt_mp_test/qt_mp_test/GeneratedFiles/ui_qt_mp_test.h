/********************************************************************************
** Form generated from reading UI file 'qt_mp_test.ui'
**
** Created: Tue Oct 27 22:20:00 2015
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QT_MP_TEST_H
#define UI_QT_MP_TEST_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_qt_mp_testClass
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *qt_mp_testClass)
    {
        if (qt_mp_testClass->objectName().isEmpty())
            qt_mp_testClass->setObjectName(QString::fromUtf8("qt_mp_testClass"));
        qt_mp_testClass->resize(600, 400);
        centralWidget = new QWidget(qt_mp_testClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(200, 40, 201, 61));
        qt_mp_testClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(qt_mp_testClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        qt_mp_testClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(qt_mp_testClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        qt_mp_testClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(qt_mp_testClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        qt_mp_testClass->setStatusBar(statusBar);

        retranslateUi(qt_mp_testClass);

        QMetaObject::connectSlotsByName(qt_mp_testClass);
    } // setupUi

    void retranslateUi(QMainWindow *qt_mp_testClass)
    {
        qt_mp_testClass->setWindowTitle(QApplication::translate("qt_mp_testClass", "qt_mp_test", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("qt_mp_testClass", "PushButton", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class qt_mp_testClass: public Ui_qt_mp_testClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QT_MP_TEST_H
