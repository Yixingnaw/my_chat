#ifndef IMAGECHANGE_H
#define IMAGECHANGE_H
#include<QRegularExpression>
#include<QString>
#include<QByteArray>
#include<QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include<QFile>
#include<QImage>
#include<QIcon>
/*toBase64 Qstring*/
class imagechange
{
public:
   QByteArray operator()(QString & imgfile);
    QImage  byte_to_qimage(QByteArray& imagebyte);

    QString image_postfix(QImage&);
    QIcon get_icon(QString &file_address);
};

#endif // IMAGECHANGE_H
