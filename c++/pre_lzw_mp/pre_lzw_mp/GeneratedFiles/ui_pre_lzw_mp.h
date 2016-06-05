/********************************************************************************
** Form generated from reading UI file 'pre_lzw_mp.ui'
**
** Created: Tue Oct 27 21:08:01 2015
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRE_LZW_MP_H
#define UI_PRE_LZW_MP_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_pre_lzw_mpClass
{
public:
    QWidget *centralWidget;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton;
    QLabel *label;
    QLineEdit *lineEdit_3;
    QLabel *label_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *pre_lzw_mpClass)
    {
        if (pre_lzw_mpClass->objectName().isEmpty())
            pre_lzw_mpClass->setObjectName(QString::fromUtf8("pre_lzw_mpClass"));
        pre_lzw_mpClass->resize(600, 400);
        centralWidget = new QWidget(pre_lzw_mpClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(10, 10, 450, 30));
        lineEdit_2 = new QLineEdit(centralWidget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(10, 50, 450, 30));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setEnabled(false);
        pushButton->setGeometry(QRect(470, 10, 80, 30));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(560, 50, 30, 30));
        lineEdit_3 = new QLineEdit(centralWidget);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(470, 50, 80, 30));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 100, 570, 250));
        pre_lzw_mpClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(pre_lzw_mpClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        pre_lzw_mpClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(pre_lzw_mpClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        pre_lzw_mpClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(pre_lzw_mpClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        pre_lzw_mpClass->setStatusBar(statusBar);

        retranslateUi(pre_lzw_mpClass);

        QMetaObject::connectSlotsByName(pre_lzw_mpClass);
    } // setupUi

    void retranslateUi(QMainWindow *pre_lzw_mpClass)
    {
        pre_lzw_mpClass->setWindowTitle(QApplication::translate("pre_lzw_mpClass", "pre_lzw_mp", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("pre_lzw_mpClass", "PushButton", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("pre_lzw_mpClass", "/10", 0, QApplication::UnicodeUTF8));
        label_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class pre_lzw_mpClass: public Ui_pre_lzw_mpClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRE_LZW_MP_H
