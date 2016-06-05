/********************************************************************************
** Form generated from reading UI file 'preprocessor.ui'
**
** Created: Fri Nov 27 15:26:42 2015
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREPROCESSOR_H
#define UI_PREPROCESSOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_preprocessorClass
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QTabWidget *tabWidget;
    QWidget *tab;
    QLineEdit *lineEdit;
    QLabel *label;
    QWidget *tab_5;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QWidget *tab_2;
    QWidget *tab_6;
    QWidget *tab_7;
    QWidget *tab_8;
    QLCDNumber *lcdNumber;
    QProgressBar *progressBar;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *preprocessorClass)
    {
        if (preprocessorClass->objectName().isEmpty())
            preprocessorClass->setObjectName(QString::fromUtf8("preprocessorClass"));
        preprocessorClass->resize(600, 400);
        centralWidget = new QWidget(preprocessorClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(30, 280, 120, 30));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 600, 250));
        tabWidget->setFocusPolicy(Qt::TabFocus);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        lineEdit = new QLineEdit(tab);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(110, 20, 171, 20));
        label = new QLabel(tab);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 20, 91, 16));
        tabWidget->addTab(tab, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        label_2 = new QLabel(tab_5);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 20, 54, 12));
        lineEdit_2 = new QLineEdit(tab_5);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(90, 10, 113, 20));
        tabWidget->addTab(tab_5, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tabWidget->addTab(tab_2, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QString::fromUtf8("tab_6"));
        tabWidget->addTab(tab_6, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName(QString::fromUtf8("tab_7"));
        tabWidget->addTab(tab_7, QString());
        tab_8 = new QWidget();
        tab_8->setObjectName(QString::fromUtf8("tab_8"));
        tabWidget->addTab(tab_8, QString());
        lcdNumber = new QLCDNumber(centralWidget);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        lcdNumber->setGeometry(QRect(190, 280, 221, 30));
        lcdNumber->setSmallDecimalPoint(false);
        lcdNumber->setDigitCount(12);
        lcdNumber->setSegmentStyle(QLCDNumber::Filled);
        lcdNumber->setProperty("value", QVariant(0));
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(440, 280, 140, 30));
        progressBar->setValue(24);
        preprocessorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(preprocessorClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        preprocessorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(preprocessorClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        preprocessorClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(preprocessorClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        preprocessorClass->setStatusBar(statusBar);

        retranslateUi(preprocessorClass);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(preprocessorClass);
    } // setupUi

    void retranslateUi(QMainWindow *preprocessorClass)
    {
        preprocessorClass->setWindowTitle(QApplication::translate("preprocessorClass", "preprocessor", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("preprocessorClass", "\345\220\257\345\212\250", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("preprocessorClass", "\346\211\223\345\214\205\346\226\207\344\273\266\345\244\271\345\234\260\345\235\200", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("preprocessorClass", "\350\247\243\345\216\213", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("preprocessorClass", "TextLabel", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QApplication::translate("preprocessorClass", "\346\213\274\345\233\276", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("preprocessorClass", "\346\212\225\345\275\261", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_6), QApplication::translate("preprocessorClass", "\351\207\215\351\207\207\346\240\267", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_7), QApplication::translate("preprocessorClass", "\345\210\207\347\211\207", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_8), QApplication::translate("preprocessorClass", "\350\207\252\345\212\250", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class preprocessorClass: public Ui_preprocessorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREPROCESSOR_H
