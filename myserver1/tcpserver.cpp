#include "tcpserver.h"
#include<QThreadPool>
#include"classHandle.h"

tcpServer::tcpServer(QObject *parent) : QTcpServer(parent)
{

}


void  tcpServer :: incomingConnection(qintptr handle){

       classHandle *cliney_handle=new classHandle(handle);              //????

       QThreadPool::globalInstance()->start(cliney_handle);


}
