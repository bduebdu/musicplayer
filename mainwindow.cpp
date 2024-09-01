#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>
#include <QIcon>
#include <QPushButton>
#include <QDebug>
#include <QPicture>
#include <QPixmap>
#include <QFileDialog>
#include <customlabel.h>
#include <QHostAddress>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMessageBox>
#include "musicmenu.h"
#include "stdShared.h"
MainWindow::MainWindow(QWidget *parent):
     QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_client(new ClientSocket(this))

{
    ui->setupUi(this);
    //设置标题
    setWindowTitle("dog");
    //设置窗口图标
    QIcon picIcon(":/photo/dog.jpg");
    setWindowIcon(picIcon);
    //初始化设置头像
    ui->headImg->setHeadImage(":/photo/1.jpg");
   //信号和槽
    connect(ui->regisBtn,&QPushButton::clicked,this,&MainWindow::handleRegisSlot);
    connect(ui->loginBtn,&QPushButton::clicked,this,&MainWindow::handleLoginSlot);

    m_client->connectToServer("192.168.159.131",8080);
    connect(m_client,&ClientSocket::connectSuccessed,this,&MainWindow::handleConnectedSlot);
    connect(m_client,&ClientSocket::dataReceived,this,&MainWindow::handleDataSlot);

}
//处理完成数据
void MainWindow::handleDataSlot(const QByteArray & data)
{
    qDebug()<<"data:"<<data<<endl;
    //1.解析json字符串
    QJsonDocument document = QJsonDocument::fromJson(data);
    if(document.isObject()==false)
    {
        qDebug()<<"document parse is not object"<<endl;
        return;
    }
    //2.将document对象转成json对象
    QJsonObject jsonObj = document.object();
    //3.取值
    int type = jsonObj["type"].toInt();
    QString result = jsonObj["result"].toString();
    if(type == REGISTER)//注册
    {
        if(result == "success")
        {
            QMessageBox::information(this,"注册","注册成功");
        }
        else
        {
            QString reason = jsonObj["reason"].toString();
            QMessageBox::information(this,"注册",reason);
        }

    }
    else if (type == LOGIN)//登录
    {
        if(result == "success")
        {
            QMessageBox::information(this,"登录","登录成功");
            //成功则跳转到登录界面
            MusicMenu * musicInterface = new MusicMenu(m_client);
            musicInterface->show();

            this->hide();//隐藏当前窗口（登录）
        }
        else
        {
            QString reason = jsonObj["reason"].toString();
            QMessageBox::information(this,"登录",reason);
        }
    }
}

void MainWindow::handleConnectedSlot()
{
    qDebug()<<"connect success"<<endl;
}
//处理信号的槽函数
void MainWindow::handleRegisSlot()
{
    qDebug()<<"注册"<<endl;
    QString username = ui->accountInfo->text();
    QString passwd = ui->passwdInfo->text();
    qDebug()<<"username:"<<username<<"passwd:"<<passwd<<endl;
    //创建json对象
    QJsonObject jsonObj;
    //设置keyvalue
    jsonObj["type"] = REGISTER;
    jsonObj["username"] = username;
    jsonObj["passwd"] = passwd;
    //创建document对象
    QJsonDocument document(jsonObj);
    //发送信息到服务器
    m_client->writeData(document.toJson());
}

void MainWindow::handleLoginSlot()
{
    qDebug()<<"登录"<<endl;
    QString username = ui->accountInfo->text();
    QString passwd = ui->passwdInfo->text();
    qDebug()<<"username:"<<username<<"passwd:"<<passwd<<endl;
    //创建json对象
    QJsonObject jsonObj;
    //设置keyvalue
    jsonObj["type"] = LOGIN;
    jsonObj["username"] = username;
    jsonObj["passwd"] = passwd;
    //创建document对象
    QJsonDocument document(jsonObj);
    //发送信息到服务器
    m_client->writeData(document.toJson());

}

MainWindow::~MainWindow()
{
    delete ui;
}



