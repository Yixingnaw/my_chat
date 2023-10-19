#ifndef MYTCPSOCKT_H
#define MYTCPSOCKT_H

#include <QObject>
#include<QTcpSocket>
#include<QByteArray>
class myTcpSockt:public QTcpSocket
{
    Q_OBJECT
public:
    myTcpSockt();

public slots:
    void getmessage(const QByteArray x);
};

#endif // MYTCPSOCKT_H
