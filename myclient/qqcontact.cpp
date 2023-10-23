#include "qqcontact.h"
#include "ui_qqcontact.h"
#include<QListWidgetItem>
#include<QString>
#include"widget.h"
#include<QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include<QByteArray>
#include<QMessageBox>

qqContact::qqContact(QString name,QTcpSocket *xx,QWidget *parent) :

    QWidget(parent),
    socket(xx),
    ui(new Ui::qqContact),
     my_name(name)
{
    ui->setupUi(this);
     udpSocket = new QUdpSocket(this);
     udpSocket->open(QIODevice::ReadWrite);
     udpSocket->bind(QHostAddress::Any, 12345);

     connect(udpSocket, &QUdpSocket::readyRead, this, &qqContact::readPendingDatagrams);

}

qqContact::~qqContact()
{
    delete ui;

}


void qqContact::on_add_friend_clicked()
{
    QJsonObject jsonObject;
        jsonObject["type"]="1";
        jsonObject["username"]=ui->jiahaoyou->text();
       // jsonObject["mine"]=
        // 将 JSON 对象转换为 JSON 文档
        QJsonDocument jsonDocument(jsonObject);
        // 将 JSON 文档转换为字节数组
        QByteArray jsonData = jsonDocument.toJson();
    // 发送 JSON 数据

   socket->  write(jsonData);
                                                          qDebug()<<"client has send over";
    socket->waitForBytesWritten();

       return;
}

void qqContact::on_listWidget_currentRowChanged(int currentRow)
{

}

void qqContact::on_friends_itemClicked(QListWidgetItem *item)
{
      QString ip;
    if (item) {
           for (auto it = friends_ip.begin(); it != friends_ip.end(); ++it) {
               if (it.value() == item) {
                   ip = it.key();
                   break; // 找到了对应的 key，可以退出循环
               }
           }

           QString nikename=item->text();

           auto it=chat_map.find(ip);
            if(it!=chat_map.end()){
             (*it)->show();

            }

         else{

               QUdpSocket *udp_socket=new QUdpSocket(this);
                  chatUi *fend=new chatUi(my_name,nikename,ip,udp_socket);
                  chat_map.insert(ip,fend);
                  fend->show();
     }


       }
}

void qqContact::on_group_create_clicked()
{
           groupcreate*      new_groupcreate=new  groupcreate(socket);
           new_groupcreate->show();
           return;

}
//udp套接字处理

void qqContact ::readPendingDatagrams() {
         while (udpSocket->hasPendingDatagrams()) {
                    QByteArray datagram;
                    QHostAddress senderAddress;
                    quint16 senderPort;
                    datagram.resize(udpSocket->pendingDatagramSize());
                    udpSocket->readDatagram(datagram.data(), datagram.size(), &senderAddress, &senderPort);
                 //保存连接的好友ip，根据ip判断是否需要开启一个ui
                    QString ip=senderAddress.toString();

                   auto it=chat_map.find(ip);
                    if(it!=chat_map.end()){
                        (*it)->view(datagram);
                       (*it)->show();
                    }

                 else{

                        QHostAddress clientBinaryIP(ip);

                       QUdpSocket *udp_socket=new QUdpSocket(this);            

                          chatUi *fend=new chatUi(my_name,"",ip,udp_socket);
                          chat_map.insert(ip,fend);
                           fend->view(datagram);
                          fend->show();

             }

     }

}


void qqContact::on_add_group_clicked()
{
    QString group_count=ui->jiaqun->text();

    QJsonObject jsonObject;
      jsonObject["type"]="2";
      jsonObject["group_count"] = group_count;

      QJsonDocument jsonDocument(jsonObject);

      QByteArray jsonData = jsonDocument.toJson();
      socket->write(jsonData);
}
void  qqContact:: initial_friend_ui(const QByteArray& jsonbytery,const QByteArray& image_data){
    QJsonDocument receivedDocument = QJsonDocument::fromJson(jsonbytery); //  是接收到的字节数组
     qint32 legth=0;
    if (!receivedDocument.isNull()) {
        if (receivedDocument.isArray()) {
            QJsonArray receivedArray = receivedDocument.array();

            for (int i = 0; i < receivedArray.size(); ++i) {
                QJsonObject jsonObject = receivedArray[i].toObject();

                // 提取用户名和昵称
                QString username = jsonObject["username"].toString();
                QString nickname = jsonObject["nickname"].toString();
                QString photo= jsonObject["photoaddress"].toString();
                QString ip=jsonObject["ip"].toString();
                 // 获得图片数据
                QByteArray img=image_data.mid(legth+4,bytesToInt(image_data.mid(legth,4)));
                legth+=(4+bytesToInt(image_data.mid(legth,4)));
                 QImage img__  ;
                try {
                  img__   =imagechange().byte_to_qimage(img);
                } catch (const QString& x) {
                    qDebug()<<x;

                }
                QPixmap myPixmap = QPixmap::fromImage(img__);
                QIcon myIcon(myPixmap);
                QListWidgetItem *item=new QListWidgetItem(ui->friends);

                item->setText(nickname);
               item->setIcon(myIcon);
               ui->friends->addItem(item);
              friends_ip.insert(ip,item);

        }
    }

}
}
