#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include<QTcpServer>
class tcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit tcpServer(QObject *parent = nullptr);

signals:

public slots:
    void    incomingConnection(qintptr handle) override;

};

#endif // TCPSERVER_H
