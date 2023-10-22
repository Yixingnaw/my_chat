#include "friendchatwoker.h"
#include"chatui.h"


friendChatWoker::friendChatWoker(QObject *parent) : QObject(parent)
{
    //    friend_chat=new chatUi();
         friend_chat->show();
        udp_friedchat=new QUdpSocket(this);


        connect(udp_friedchat, &QUdpSocket::readyRead, this, [this]()
           {
               while (udp_friedchat ->hasPendingDatagrams())
               {
                   QByteArray datagram;
                   datagram.resize(udp_friedchat ->pendingDatagramSize());
                  udp_friedchat ->readDatagram(datagram.data(), datagram.size());


               }
           });
  
   
        //  udp_friedchat  ->bind(QHostAddress::AnyIPv4, port);
        friend_chat->show();

}
