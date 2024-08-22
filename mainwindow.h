#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include "clientsocket.h"
#include <QByteArray>

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    //处理信号的槽函数
    void handleRegisSlot();
    void handleLoginSlot();
    void handleConnectedSlot();//处理连接成功
    void handleDataSlot(const QByteArray & data);//处理数据

private:
    Ui::MainWindow *ui;
    ClientSocket * m_client;//网络通信
};
#endif // MAINWINDOW_H
