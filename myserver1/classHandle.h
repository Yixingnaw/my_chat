#ifndef CLASSHANDLE_H
#define CLASSHANDLE_H
#include"mytcpsockt.h"
#include <QThreadPool>
#include <QObject>
#include<QTcpSocket>
#include<QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include<QJsonArray>
#include<QHostAddress>
#include<unordered_set>
#include<QTcpSocket>
#include"global.h"
#include"sql.h"
#include"qquser.h"
#include<QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include<algorithm>
#include<QByteArray>
#include<QSqlError>
#include<mutex>
#include<QDir>
#include"imagechangge.h"
#include<QHostAddress>
#include"sigleinstance.h"
#include<QThread>
#include"group.h"
class classHandle :public QRunnable
{

public:
      classHandle(qintptr socketDescriptor);
void run() override;
   QString     get_ip_address(QTcpSocket * socket);


public slots:
    void change(bool);
private:
   qintptr socket_Descriptor;
   bool caohanshu;

   int image_count;            //the image send counts;
   int groups_image_count;

   QByteArray     groupData(QVector<group>&container);

};

#endif // CLASSHANDLE_H
