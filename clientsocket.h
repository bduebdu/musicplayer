#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QObject>
#include <QString>
#include <QTcpSocket>
class ClientSocket : public QObject
{
    Q_OBJECT
public:
    explicit ClientSocket(QObject *parent = nullptr);
    ~ClientSocket();
    //连接服务器
    void connectToServer(const QString & ip,qint16 port);
    int writeData(const QByteArray & data);

signals:
    void connectSuccessed();
    void dataReceived(const QByteArray & data);

public slots:
    void handleReadSlot();


private:
    QTcpSocket * m_socket;
    QString m_ip;
    qint16 m_port;

    QByteArray m_buffer;//数据缓冲区
};

#endif // CLIENTSOCKET_H
