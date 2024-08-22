#ifndef ONLINEPLAYER_H
#define ONLINEPLAYER_H

#include <QObject>

class onlinePlayer : public QObject
{
    Q_OBJECT
public:
    explicit onlinePlayer(QObject *parent = nullptr);

signals:

};

#endif // ONLINEPLAYER_H
