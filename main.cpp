#include "mainwindow.h"

#include <QApplication>
#include "musicmenu.h"
#include "onlineplayer.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

//    MusicMenu w;
//    w.show();


    return a.exec();
}
