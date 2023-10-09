#include "widget.h"
#include "ui_widget.h"
#include<QTcpServer>
#include<QString>
#include<QTcpSocket>
#include<QList>
#include"global.h"
#include "ui_chat.h"
#include<QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include<thread>
#include<mutex>
#include"tcpserver.h"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget),chatwidget(new chat())
{
    ui->setupUi(this);
   listen_socket=new tcpServer(this);
   listen_register_socket=new QTcpServer(this);

}

Widget::~Widget()
{
    delete ui;
    delete chatwidget;
}


void Widget::on_listen_socket_clicked()
{

         QString s,s2;
        //  if((s=ui->lis_port->text())==""||(s2=ui->register_2->text())=="")return;
          listen_register_socket->listen(QHostAddress::Any,9999);
          listen_socket->listen(QHostAddress::Any,9998);
   //       connect(listen_socket,&QTcpServer::newConnection,this,&Widget::client_sockt_come);
        connect(listen_register_socket,&QTcpServer::newConnection,this,&Widget::on_listen_register_come);


}

/*void Widget::client_sockt_come()
{
    //listen success dispaly the chatwidget;
    chatwidget->show();

    QTcpSocket* new_client=nullptr;
   new_client=listen_socket->nextPendingConnection();//likely  accept function

   client_sockets.push_back(new_client);
       connect(new_client,&QTcpSocket::readyRead,[=](){
           QString s="";
           //获取IP地址
               QString ip=new_client->peerAddress().toString();
               s+=ip;
               //获取端口号
               qint16 port=new_client->peerPort();
               s+="   ";
               s+=QString::number(port);
            chatwidget->return_ui()->chat_edit->append((s));

            //message
              s= new_client->readAll();
              chatwidget->return_ui()->chat_edit->append((s));

              //zhuan  fa mei tiao xiao xi
              for(auto c:client_sockets){
                  if(c==new_client)continue;
                  c->write(s.toUtf8(),s.toUtf8().size());
              }
       });

       chatwidget-> show_online_numbbers();

}*/

void Widget::on_listen_register_come(){

                                                                                                            //nei cun xie lou
           QTcpSocket* new_client=nullptr;

         // while(listen_register_socket->waitForNewConnection(-1))break;
            new_client=listen_register_socket->nextPendingConnection();


          if (new_client && new_client->state() == QAbstractSocket::ConnectedState)
         {    qDebug()<<"oihdiwsad";

              connect(new_client,&QTcpSocket::readyRead,this,[=](){
                QByteArray  byte_josn =  new_client->readAll();

       QJsonDocument      newDocument = QJsonDocument::fromJson(byte_josn);
                      // 将QJsonDocument转换为JSON对象
                                                       qDebug()<<byte_josn;
        QJsonObject       newObject = newDocument.object();

             // 获取JSON对象中的值
                QString     nike_name = newObject.value("nikename").toString();
                        QString    pass_word=newObject.value("password").toString();

             // new_client->waitForReadyRead();
              QString user_name;
              //cun ru shu ju ku;
           do{
              char* username=  generateRandomAccount();
              user_name=username;
              db.executeQuery("select * from users where username like "+user_name);
               free(username);
              }while(db.query.value(0).toInt());

            //    std::mutex mutex;
            //  std::lock_guard<std::mutex> lock(mutex);
     db.executeQuery( "INSERT INTO users (password, username, nickname) VALUES ('" + pass_word + "', '" + user_name + "', '" + nike_name + "');");


              QJsonObject echo_json;
              echo_json["username"]=user_name;
              QJsonDocument echojosodocument(echo_json);
              QByteArray ss=echojosodocument.toJson();
              new_client->write(ss);
                                                                               qDebug()<<"bie gao wo le";
              });
 return;}

}



