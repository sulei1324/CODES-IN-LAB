/********************************************************************************
** Form generated from reading UI file 'averagefilterqt.ui'
**
** Created: Mon Jul 27 23:02:42 2015
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AVERAGEFILTERQT_H
#define UI_AVERAGEFILTERQT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AverageFilterQtClass
{
public:
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *AverageFilterQtClass)
    {
        if (AverageFilterQtClass->objectName().isEmpty())
            AverageFilterQtClass->setObjectName(QString::fromUtf8("AverageFilterQtClass"));
        AverageFilterQtClass->resize(800, 600);
        centralwidget = new QWidget(AverageFilterQtClass);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 500, 741, 51));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(layoutWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(layoutWidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        horizontalLayout->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(layoutWidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        horizontalLayout->addWidget(pushButton_4);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 0, 771, 461));
        AverageFilterQtClass->setCentralWidget(centralwidget);
        menubar = new QMenuBar(AverageFilterQtClass);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 23));
        AverageFilterQtClass->setMenuBar(menubar);
        statusbar = new QStatusBar(AverageFilterQtClass);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        AverageFilterQtClass->setStatusBar(statusbar);

        retranslateUi(AverageFilterQtClass);

        QMetaObject::connectSlotsByName(AverageFilterQtClass);
    } // setupUi

    void retranslateUi(QMainWindow *AverageFilterQtClass)
    {
        AverageFilterQtClass->setWindowTitle(QApplication::translate("AverageFilterQtClass", "MainWindow", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("AverageFilterQtClass", "OpenImage", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("AverageFilterQtClass", "Filter", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("AverageFilterQtClass", "Switch", 0, QApplication::UnicodeUTF8));
        pushButton_4->setText(QApplication::translate("AverageFilterQtClass", "Save", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("AverageFilterQtClass", "image_area", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AverageFilterQtClass: public Ui_AverageFilterQtClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AVERAGEFILTERQT_H
