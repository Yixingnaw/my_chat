#include "global.h"
QByteArray intToBytes(qint32 value) {
    QByteArray byteArray;
    QDataStream stream(&byteArray, QIODevice::WriteOnly);
    stream << value;
    return byteArray;
}
// 将 QByteArray 转换为 qint32
qint32 bytesToInt(const QByteArray &byteArray) {
    qint32 value = 0;
    QDataStream stream(byteArray);
    stream >> value;
    return value;
}
