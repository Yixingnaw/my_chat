#ifndef CLASSHANDLE_H
#define CLASSHANDLE_H
#include <QThreadPool>
#include <QObject>
#include<QTcpSocket>
#include<QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
class classHandle : public QRunnable
{

public:
      classHandle(qintptr socketDescriptor);
void run() override;
   QString     get_ip_address(QTcpSocket * &socket);


public slots:

private:
   qintptr socket_Descriptor;
   std::mutex mutex;
   std::mutex mutex_rb;
   int image_count;            //the image send counts;
   int groups_image_count;

};

#endif // CLASSHANDLE_H
