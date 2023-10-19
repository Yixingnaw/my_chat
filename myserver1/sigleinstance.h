#ifndef SIGLEINSTANCE_H
#define SIGLEINSTANCE_H

#include <QObject>
#include<QMutex>
#include<QByteArray>
class sigleInstance:public QObject
{
    Q_OBJECT
public:
    sigleInstance();
    sigleInstance(const sigleInstance&)=delete;
   sigleInstance operator=(const sigleInstance&)=delete ;

public slots:


 signals:
    void sendmesssage(QByteArray x);


public: void send(QByteArray x);


};

#endif // SIGLEINSTANCE_H
