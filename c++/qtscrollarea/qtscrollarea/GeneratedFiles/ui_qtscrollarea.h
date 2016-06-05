/********************************************************************************
** Form generated from reading UI file 'qtscrollarea.ui'
**
** Created: Fri Sep 4 11:19:31 2015
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTSCROLLAREA_H
#define UI_QTSCROLLAREA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QScrollArea>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_qtscrollareaClass
{
public:
    QWidget *centralWidget;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QLabel *label;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *qtscrollareaClass)
    {
        if (qtscrollareaClass->objectName().isEmpty())
            qtscrollareaClass->setObjectName(QString::fromUtf8("qtscrollareaClass"));
        qtscrollareaClass->resize(801, 555);
        centralWidget = new QWidget(qtscrollareaClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(90, 50, 621, 421));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 619, 419));
        label = new QLabel(scrollAreaWidgetContents);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 621, 421));
        scrollArea->setWidget(scrollAreaWidgetContents);
        qtscrollareaClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(qtscrollareaClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 801, 23));
        qtscrollareaClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(qtscrollareaClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        qtscrollareaClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(qtscrollareaClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        qtscrollareaClass->setStatusBar(statusBar);

        retranslateUi(qtscrollareaClass);

        QMetaObject::connectSlotsByName(qtscrollareaClass);
    } // setupUi

    void retranslateUi(QMainWindow *qtscrollareaClass)
    {
        qtscrollareaClass->setWindowTitle(QApplication::translate("qtscrollareaClass", "qtscrollarea", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("qtscrollareaClass", "TextLabel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class qtscrollareaClass: public Ui_qtscrollareaClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTSCROLLAREA_H
