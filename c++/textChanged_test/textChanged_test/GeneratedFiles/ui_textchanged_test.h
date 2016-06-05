/********************************************************************************
** Form generated from reading UI file 'textchanged_test.ui'
**
** Created: Fri Oct 23 20:49:04 2015
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEXTCHANGED_TEST_H
#define UI_TEXTCHANGED_TEST_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_textChanged_testClass
{
public:
    QWidget *centralWidget;
    QLineEdit *lineEdit;
    QLabel *label;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *textChanged_testClass)
    {
        if (textChanged_testClass->objectName().isEmpty())
            textChanged_testClass->setObjectName(QString::fromUtf8("textChanged_testClass"));
        textChanged_testClass->resize(600, 400);
        centralWidget = new QWidget(textChanged_testClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(200, 30, 113, 20));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(150, 90, 211, 151));
        textChanged_testClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(textChanged_testClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        textChanged_testClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(textChanged_testClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        textChanged_testClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(textChanged_testClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        textChanged_testClass->setStatusBar(statusBar);

        retranslateUi(textChanged_testClass);

        QMetaObject::connectSlotsByName(textChanged_testClass);
    } // setupUi

    void retranslateUi(QMainWindow *textChanged_testClass)
    {
        textChanged_testClass->setWindowTitle(QApplication::translate("textChanged_testClass", "textChanged_test", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("textChanged_testClass", "TextLabel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class textChanged_testClass: public Ui_textChanged_testClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEXTCHANGED_TEST_H
