#include "mytcpsockt.h"

myTcpSockt::myTcpSockt()
{

}
void   myTcpSockt:: getmessage(const QByteArray x){
       write(x);
       qDebug()<<"已经发出了数据"<<x;
}
