#include "mainwindow.h"

#include <QApplication>
#include "musicmenu.h"
#include "onlineplayer.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;//控制显示
    w.show();

//    MusicMenu w;
//    w.show();


    return a.exec();
}
