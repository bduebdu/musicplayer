/********************************************************************************
** Form generated from reading UI file 'musicmenu.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MUSICMENU_H
#define UI_MUSICMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MusicMenu
{
public:
    QWidget *centralwidget;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_3;
    QWidget *widget;
    QLabel *albumLabel;
    QPushButton *prevBtn;
    QPushButton *playBtn;
    QPushButton *nextBtn;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout;
    QLabel *currentTime;
    QSlider *processBar;
    QLabel *totalTime;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *switchModeBtn;
    QPushButton *volumeBtn;
    QPushButton *post_lrc_Btn;
    QPushButton *collectBtn;
    QListWidget *musicList;
    QLabel *lyricLabel;
    QLineEdit *searchMusic;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MusicMenu)
    {
        if (MusicMenu->objectName().isEmpty())
            MusicMenu->setObjectName(QString::fromUtf8("MusicMenu"));
        MusicMenu->resize(1042, 592);
        QFont font;
        font.setPointSize(10);
        MusicMenu->setFont(font);
        centralwidget = new QWidget(MusicMenu);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        widget_3 = new QWidget(centralwidget);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        widget_3->setGeometry(QRect(20, 430, 991, 96));
        horizontalLayout_3 = new QHBoxLayout(widget_3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        widget = new QWidget(widget_3);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(371, 78));
        widget->setMaximumSize(QSize(371, 78));
        albumLabel = new QLabel(widget);
        albumLabel->setObjectName(QString::fromUtf8("albumLabel"));
        albumLabel->setGeometry(QRect(9, 9, 60, 60));
        albumLabel->setMinimumSize(QSize(60, 60));
        albumLabel->setMaximumSize(QSize(60, 60));
        prevBtn = new QPushButton(widget);
        prevBtn->setObjectName(QString::fromUtf8("prevBtn"));
        prevBtn->setGeometry(QRect(121, 9, 60, 60));
        prevBtn->setMinimumSize(QSize(60, 60));
        prevBtn->setMaximumSize(QSize(60, 60));
        playBtn = new QPushButton(widget);
        playBtn->setObjectName(QString::fromUtf8("playBtn"));
        playBtn->setGeometry(QRect(187, 9, 60, 60));
        playBtn->setMinimumSize(QSize(60, 60));
        playBtn->setMaximumSize(QSize(60, 60));
        nextBtn = new QPushButton(widget);
        nextBtn->setObjectName(QString::fromUtf8("nextBtn"));
        nextBtn->setGeometry(QRect(253, 9, 60, 60));
        nextBtn->setMinimumSize(QSize(60, 60));
        nextBtn->setMaximumSize(QSize(60, 60));

        horizontalLayout_3->addWidget(widget);

        widget_4 = new QWidget(widget_3);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        widget_4->setMinimumSize(QSize(331, 78));
        widget_4->setMaximumSize(QSize(331, 16777215));
        horizontalLayout = new QHBoxLayout(widget_4);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        currentTime = new QLabel(widget_4);
        currentTime->setObjectName(QString::fromUtf8("currentTime"));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        currentTime->setFont(font1);

        horizontalLayout->addWidget(currentTime);

        processBar = new QSlider(widget_4);
        processBar->setObjectName(QString::fromUtf8("processBar"));
        processBar->setOrientation(Qt::Orientation::Horizontal);

        horizontalLayout->addWidget(processBar);

        totalTime = new QLabel(widget_4);
        totalTime->setObjectName(QString::fromUtf8("totalTime"));
        totalTime->setMaximumSize(QSize(16777215, 60));
        totalTime->setFont(font1);

        horizontalLayout->addWidget(totalTime);


        horizontalLayout_3->addWidget(widget_4);

        widget_2 = new QWidget(widget_3);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        switchModeBtn = new QPushButton(widget_2);
        switchModeBtn->setObjectName(QString::fromUtf8("switchModeBtn"));
        switchModeBtn->setMinimumSize(QSize(60, 60));
        switchModeBtn->setMaximumSize(QSize(60, 60));

        horizontalLayout_2->addWidget(switchModeBtn);

        volumeBtn = new QPushButton(widget_2);
        volumeBtn->setObjectName(QString::fromUtf8("volumeBtn"));
        volumeBtn->setMinimumSize(QSize(60, 60));
        volumeBtn->setMaximumSize(QSize(60, 60));

        horizontalLayout_2->addWidget(volumeBtn);

        post_lrc_Btn = new QPushButton(widget_2);
        post_lrc_Btn->setObjectName(QString::fromUtf8("post_lrc_Btn"));
        post_lrc_Btn->setMinimumSize(QSize(60, 60));
        post_lrc_Btn->setMaximumSize(QSize(60, 60));

        horizontalLayout_2->addWidget(post_lrc_Btn);

        collectBtn = new QPushButton(widget_2);
        collectBtn->setObjectName(QString::fromUtf8("collectBtn"));
        collectBtn->setMinimumSize(QSize(60, 60));
        collectBtn->setMaximumSize(QSize(60, 60));

        horizontalLayout_2->addWidget(collectBtn);


        horizontalLayout_3->addWidget(widget_2);

        musicList = new QListWidget(centralwidget);
        musicList->setObjectName(QString::fromUtf8("musicList"));
        musicList->setGeometry(QRect(560, 30, 391, 311));
        lyricLabel = new QLabel(centralwidget);
        lyricLabel->setObjectName(QString::fromUtf8("lyricLabel"));
        lyricLabel->setGeometry(QRect(240, 370, 571, 41));
        lyricLabel->setFont(font1);
        searchMusic = new QLineEdit(centralwidget);
        searchMusic->setObjectName(QString::fromUtf8("searchMusic"));
        searchMusic->setGeometry(QRect(70, 30, 241, 31));
        MusicMenu->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MusicMenu);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1042, 27));
        MusicMenu->setMenuBar(menubar);
        statusbar = new QStatusBar(MusicMenu);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MusicMenu->setStatusBar(statusbar);

        retranslateUi(MusicMenu);

        QMetaObject::connectSlotsByName(MusicMenu);
    } // setupUi

    void retranslateUi(QMainWindow *MusicMenu)
    {
        MusicMenu->setWindowTitle(QCoreApplication::translate("MusicMenu", "MainWindow", nullptr));
        albumLabel->setText(QString());
        prevBtn->setText(QString());
        playBtn->setText(QString());
        nextBtn->setText(QString());
        currentTime->setText(QCoreApplication::translate("MusicMenu", "00:00", nullptr));
        totalTime->setText(QCoreApplication::translate("MusicMenu", "04:21", nullptr));
        switchModeBtn->setText(QString());
        volumeBtn->setText(QString());
        post_lrc_Btn->setText(QString());
        collectBtn->setText(QString());
        lyricLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MusicMenu: public Ui_MusicMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MUSICMENU_H
