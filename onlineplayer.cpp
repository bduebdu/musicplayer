#include "onlineplayer.h"
#include <QMediaPlayer>
#include <QMediaContent>
#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QBuffer>

onlinePlayer::onlinePlayer(QObject *parent) : QObject(parent)
{
    qDebug()<<"start"<<endl;

    QMediaPlayer * player = new QMediaPlayer(this);

    QString musicPath = "D:\\下载\\music\\夜曲.mp3";


    QFileInfo checkInfo(musicPath);
    if(checkInfo.exists()==false)
    {
        qDebug()<<"file not exist"<<checkInfo<<endl;
    }

    QFile file(musicPath);

    if(file.open(QIODevice::ReadOnly)==false)
    {
        qDebug()<<"open QIODevice::ReadOnly"<<endl;
    }

    QByteArray audioData = file.readAll();//音乐数据
    file.close();//关闭文件
#if 1
    //创建一个Qbuffer缓冲区
    QBuffer * buffer = new QBuffer(this);
    buffer->setData(audioData);

    if(buffer->open(QIODevice::ReadOnly)==false)
    {
        qDebug()<<"缓冲区无法打开"<<endl;
    }

#endif
    player->setMedia(QMediaContent(),buffer);

    //播放音乐
    player->play();

}



