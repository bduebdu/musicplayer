/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <customlabel.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QLineEdit *accountInfo;
    QLabel *label;
    QWidget *widget_2;
    QLineEdit *passwdInfo;
    QLabel *label_2;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *loginBtn;
    QSpacerItem *horizontalSpacer;
    QPushButton *regisBtn;
    QSpacerItem *horizontalSpacer_2;
    customLabel *headImg;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1072, 627);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        widget_4 = new QWidget(centralwidget);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        widget_4->setGeometry(QRect(210, 210, 641, 331));
        verticalLayout = new QVBoxLayout(widget_4);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget = new QWidget(widget_4);
        widget->setObjectName(QString::fromUtf8("widget"));
        accountInfo = new QLineEdit(widget);
        accountInfo->setObjectName(QString::fromUtf8("accountInfo"));
        accountInfo->setGeometry(QRect(150, 20, 451, 40));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 10, 91, 56));
        QFont font;
        font.setPointSize(20);
        label->setFont(font);
        label->setLayoutDirection(Qt::LeftToRight);
        label->setOpenExternalLinks(false);

        verticalLayout->addWidget(widget);

        widget_2 = new QWidget(widget_4);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        passwdInfo = new QLineEdit(widget_2);
        passwdInfo->setObjectName(QString::fromUtf8("passwdInfo"));
        passwdInfo->setGeometry(QRect(150, 20, 451, 40));
        QFont font1;
        font1.setPointSize(9);
        passwdInfo->setFont(font1);
        label_2 = new QLabel(widget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 10, 111, 55));
        label_2->setFont(font);

        verticalLayout->addWidget(widget_2);

        widget_3 = new QWidget(widget_4);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        horizontalLayout = new QHBoxLayout(widget_3);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        loginBtn = new QPushButton(widget_3);
        loginBtn->setObjectName(QString::fromUtf8("loginBtn"));
        loginBtn->setFont(font);

        horizontalLayout->addWidget(loginBtn);

        horizontalSpacer = new QSpacerItem(20, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        regisBtn = new QPushButton(widget_3);
        regisBtn->setObjectName(QString::fromUtf8("regisBtn"));
        regisBtn->setFont(font);

        horizontalLayout->addWidget(regisBtn);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addWidget(widget_3);

        headImg = new customLabel(centralwidget);
        headImg->setObjectName(QString::fromUtf8("headImg"));
        headImg->setGeometry(QRect(470, 50, 125, 125));
        headImg->setMinimumSize(QSize(125, 125));
        headImg->setMaximumSize(QSize(125, 125));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1072, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        QWidget::setTabOrder(passwdInfo, loginBtn);
        QWidget::setTabOrder(loginBtn, regisBtn);
        QWidget::setTabOrder(regisBtn, accountInfo);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        accountInfo->setText(QString());
        label->setText(QCoreApplication::translate("MainWindow", "\350\264\246\345\217\267:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\345\257\206\347\240\201:", nullptr));
        loginBtn->setText(QCoreApplication::translate("MainWindow", "\347\231\273\345\275\225", nullptr));
        regisBtn->setText(QCoreApplication::translate("MainWindow", "\346\263\250\345\206\214", nullptr));
        headImg->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
