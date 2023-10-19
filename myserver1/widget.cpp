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
#include "imagechangge.h"
#include<QDir>
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
         hide();

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
windwows
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

         // while(listen_register_socket->waitForNewConnection(-1))break;
            new_client=listen_register_socket->nextPendingConnection();


            QObject:: connect(new_client, &QTcpSocket::disconnected, [&](){
                 // 断开信号触发时，删除 QTcpSocket 对象
                   new_client-> deleteLater();
             });
          if (new_client && new_client->state() == QAbstractSocket::ConnectedState)
         {                                                                                  qDebug()<<" 开始注册";

              connect(new_client,&QTcpSocket::readyRead,this,[=](){
                  // 当有新连接时，从套接
                  QByteArray receivedData = new_client->readAll();                          

                int json_size=(int)  receivedData[96];
                    QByteArray json_json=receivedData.left(json_size);
              QJsonDocument      newDocument=QJsonDocument::fromJson(json_json);
               QJsonObject       newObject=newDocument.object();
                    QByteArray imageData=receivedData.mid(100);
               
                                                                                         //  qDebug()<<receivedData;


             // 获取JSON对象中的值
                QString     nike_name = newObject.value("nikename").toString();
                        QString    pass_word=newObject.value("password").toString();
              QImage photo;
               bool bool_image=true;
         try{       photo=       imagechange().byte_to_qimage(imageData);}
                        catch (QString& x){
                            qDebug()<<"image read erro";
                            bool_image=false;
                        }

             // new_client->waitForReadyRead();
              QString user_name;
              //cun ru shu ju ku;
           do{
              std::shared_ptr<std::string> username =generateRandomAccount();

             user_name=(*username).c_str();
              db.executeQuery("select * from users where username like "+user_name);       //qDebug()<<"shu  ju zhao chenggong mei you zhaodao shuju";

              }while(db.query.next());

               
              // 获取当前工作目录
              QString currentDir = QDir::currentPath();
                QString houzhui;
              // 使用相对路径
              if(!bool_image)
                     houzhui=".jpg";
              else {
                 houzhui= imagechange().image_postfix(photo);
              }
              QString relativePath = "image/"+ user_name+houzhui; // 以当前工作目录为起点的相对路径
              // 将相对路径转换为绝对路径
              QString absolutePath = QDir(currentDir).filePath(relativePath);
                photo.save(absolutePath);
                std::mutex mutex;
             std::lock_guard<std::mutex> lock(mutex);
        db.executeQuery( "INSERT INTO users (password, username, nickname,avatar_url) VALUES ('" + pass_word + "', '" + user_name + "', '" + nike_name + "','"+absolutePath+"');");
                                                                                           qDebug()<<"注册成功";
      
                                                                                           QJsonObject echo_json;

              echo_json["username"]=user_name;
              QJsonDocument echojosodocument(echo_json);
              QByteArray ss=echojosodocument.toJson();
              new_client->write(ss);
                                                                                                                 //  qDebug()<<"bie gao wo le";
              });
 return;}
          return;

}



