#ifndef IMAGECHANGE_H
#define IMAGECHANGE_H

#include<QString>
#include<QByteArray>
#include<QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include<QFile>
#include<QImage>
#include<QTcpSocket>
#include<qquser.h>
/*toBase64 Qstring*/
class imagechange
{
public:
   QByteArray operator()(QString & imgfile);
    QImage  byte_to_qimage(QByteArray& imagebyte);

    QString image_postfix(QImage&);
     //bool send_user_image(QByteArray &imagedata,QTcpSocket& user_soket);
//     bool send_groups_image(QByteArray &imagedata,QTcpSocket& user_soket);
     
     QString get_imagepath(qqUser& qq);
};

#endif // IMAGECHANGE_H
