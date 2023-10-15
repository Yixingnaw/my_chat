#ifndef IMAGECHANGE_H
#define IMAGECHANGE_H

#include<QString>
#include<QByteArray>
#include<QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include<QFile>
#include<QImage>
/*toBase64 Qstring*/
class imagechange
{
public:
   QByteArray operator()(QString & imgfile);
    QImage  byte_to_qimage(QByteArray& imagebyte);

    QString image_postfix(QImage&);
};

#endif // IMAGECHANGE_H
