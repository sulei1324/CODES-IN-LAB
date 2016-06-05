/********************************************************************************
** Form generated from reading UI file 'projecter.ui'
**
** Created: Fri Sep 18 14:56:06 2015
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROJECTER_H
#define UI_PROJECTER_H

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

class Ui_projecterClass
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_5;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *lineEdit_6;
    QLabel *label_6;
    QLineEdit *lineEdit_7;
    QLabel *label_7;
    QLabel *label_8;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *projecterClass)
    {
        if (projecterClass->objectName().isEmpty())
            projecterClass->setObjectName(QString::fromUtf8("projecterClass"));
        projecterClass->resize(600, 400);
        centralWidget = new QWidget(projecterClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(470, 290, 75, 23));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(100, 30, 113, 20));
        lineEdit_2 = new QLineEdit(centralWidget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(100, 70, 113, 20));
        lineEdit_3 = new QLineEdit(centralWidget);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(100, 110, 113, 20));
        lineEdit_4 = new QLineEdit(centralWidget);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(100, 160, 113, 20));
        lineEdit_5 = new QLineEdit(centralWidget);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));
        lineEdit_5->setGeometry(QRect(100, 200, 113, 20));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 30, 54, 12));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 80, 54, 12));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 110, 54, 12));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 160, 54, 12));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(20, 210, 54, 12));
        lineEdit_6 = new QLineEdit(centralWidget);
        lineEdit_6->setObjectName(QString::fromUtf8("lineEdit_6"));
        lineEdit_6->setGeometry(QRect(100, 240, 113, 20));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(20, 250, 54, 12));
        lineEdit_7 = new QLineEdit(centralWidget);
        lineEdit_7->setObjectName(QString::fromUtf8("lineEdit_7"));
        lineEdit_7->setGeometry(QRect(100, 280, 113, 20));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(20, 290, 54, 12));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(300, 40, 251, 201));
        projecterClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(projecterClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        projecterClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(projecterClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        projecterClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(projecterClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        projecterClass->setStatusBar(statusBar);

        retranslateUi(projecterClass);

        QMetaObject::connectSlotsByName(projecterClass);
    } // setupUi

    void retranslateUi(QMainWindow *projecterClass)
    {
        projecterClass->setWindowTitle(QApplication::translate("projecterClass", "projecter", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("projecterClass", "Run", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("projecterClass", "pre", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("projecterClass", "post", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("projecterClass", "thick", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("projecterClass", "begin", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("projecterClass", "end", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("projecterClass", "src", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("projecterClass", "dst", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("projecterClass", "test", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class projecterClass: public Ui_projecterClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJECTER_H
