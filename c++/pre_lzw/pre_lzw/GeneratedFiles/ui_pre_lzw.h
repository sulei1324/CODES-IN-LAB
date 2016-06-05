/********************************************************************************
** Form generated from reading UI file 'pre_lzw.ui'
**
** Created: Sat Oct 24 16:23:31 2015
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRE_LZW_H
#define UI_PRE_LZW_H

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

class Ui_pre_lzwClass
{
public:
    QWidget *centralWidget;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QLabel *label;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *pre_lzwClass)
    {
        if (pre_lzwClass->objectName().isEmpty())
            pre_lzwClass->setObjectName(QString::fromUtf8("pre_lzwClass"));
        pre_lzwClass->resize(600, 400);
        centralWidget = new QWidget(pre_lzwClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(20, 10, 400, 30));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setEnabled(false);
        pushButton->setGeometry(QRect(440, 10, 90, 30));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 99, 500, 221));
        lineEdit_2 = new QLineEdit(centralWidget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(20, 50, 400, 30));
        lineEdit_3 = new QLineEdit(centralWidget);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(440, 50, 90, 30));
        pre_lzwClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(pre_lzwClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        pre_lzwClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(pre_lzwClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        pre_lzwClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(pre_lzwClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        pre_lzwClass->setStatusBar(statusBar);

        retranslateUi(pre_lzwClass);

        QMetaObject::connectSlotsByName(pre_lzwClass);
    } // setupUi

    void retranslateUi(QMainWindow *pre_lzwClass)
    {
        pre_lzwClass->setWindowTitle(QApplication::translate("pre_lzwClass", "pre_lzw", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("pre_lzwClass", "PushButton", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class pre_lzwClass: public Ui_pre_lzwClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRE_LZW_H
