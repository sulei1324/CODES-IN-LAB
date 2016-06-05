/********************************************************************************
** Form generated from reading UI file 'qttest.ui'
**
** Created: Fri May 6 14:20:50 2016
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTTEST_H
#define UI_QTTEST_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTextBrowser>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_qttestClass
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QLCDNumber *lcdNumber;
    QTextBrowser *textBrowser;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *qttestClass)
    {
        if (qttestClass->objectName().isEmpty())
            qttestClass->setObjectName(QString::fromUtf8("qttestClass"));
        qttestClass->resize(600, 400);
        centralWidget = new QWidget(qttestClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(40, 60, 121, 41));
        lcdNumber = new QLCDNumber(centralWidget);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        lcdNumber->setGeometry(QRect(20, 160, 241, 71));
        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(290, 40, 291, 281));
        qttestClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(qttestClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        qttestClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(qttestClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        qttestClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(qttestClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        qttestClass->setStatusBar(statusBar);

        retranslateUi(qttestClass);

        QMetaObject::connectSlotsByName(qttestClass);
    } // setupUi

    void retranslateUi(QMainWindow *qttestClass)
    {
        qttestClass->setWindowTitle(QApplication::translate("qttestClass", "qttest", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("qttestClass", "PushButton", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class qttestClass: public Ui_qttestClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTTEST_H
