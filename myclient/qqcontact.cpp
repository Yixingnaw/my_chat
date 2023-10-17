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

qqContact::qqContact(QTcpSocket *xx,QWidget *parent) :

    QWidget(parent),
    socket(xx),
    ui(new Ui::qqContact)
{
    ui->setupUi(this);
     udpSocket = new QUdpSocket(this);
     udpSocket->bind(QHostAddress::Any, 12345);
    //  connect(udpSocket, &QUdpSocket::readyRead, this, &qqContact::readPendingDatagrams);


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
      qDebug()<<"woaini";
}

void qqContact::on_group_create_clicked()
{
           groupcreate*      new_groupcreate=new  groupcreate(socket);
           new_groupcreate->show();

           return;

}
//udp套接字处理
/*
void qqContact ::readPendingDatagrams() {
         while (udpSocket->hasPendingDatagrams()) {
                    QByteArray datagram;
                    QHostAddress senderAddress;
                    quint16 senderPort;
                    datagram.resize(udpSocket->pendingDatagramSize());
                    udpSocket->readDatagram(datagram.data(), datagram.size(), &senderAddress, &senderPort);
                 //保存连接的好友id，根据id判断是否需要开启一个线程

                    int case_x;
                    switch (case_x) {

                    case 0:
                    {

                    }break;
                    case 1:
                    {

                    }break;

                    default:break;
             }

     }

}*/


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

        }
    }

}
}
