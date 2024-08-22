#include "clientsocket.h"
#include <QHostAddress>
ClientSocket::ClientSocket(QObject *parent) : QObject(parent)
{
    m_socket = new QTcpSocket(this);

    connect(m_socket,&QTcpSocket::connected,[this]()
    {
        emit connectSuccessed();//发射信号
    });

    connect(m_socket,&QTcpSocket::readyRead,this,&ClientSocket::handleReadSlot);

}
//处理读数据
void ClientSocket::handleReadSlot()
{
    m_buffer.append(m_socket->readAll());
    while(m_buffer.size()>=sizeof(size_t))
    {
        size_t size;
        memcpy(&size,m_buffer.data(),sizeof (size_t));
        if(m_buffer.size()<size +sizeof(size_t))
        {
            break;
        }
        //发送信号
        emit dataReceived(m_buffer.mid(sizeof(size_t),size));
        m_buffer.remove(0,sizeof(size_t)+size);
    }

}

//连接服务器
void ClientSocket::connectToServer(const QString & ip,qint16 port)
{
    m_ip = ip;
    m_port = port;

    m_socket->connectToHost(QHostAddress(ip),port);

}
//解决粘包
int ClientSocket::writeData(const QByteArray & data)
{
    size_t len = data.size();
//    qDebug() << "len:" << len << endl;

    //1.先发送数据包大小
    m_socket->write((const char *)&len,sizeof(len));
    //2.再发送数据包内容
    m_socket->write(data);

}

ClientSocket::~ClientSocket()
{

}

