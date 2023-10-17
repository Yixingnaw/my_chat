#ifndef GLOBAL_H
#define GLOBAL_H
#include<QByteArray>
#include<QDataStream>
extern QByteArray intToBytes(qint32 value);
extern  qint32 bytesToInt(const QByteArray &byteArray) ;
#endif // GLOBAL_H
