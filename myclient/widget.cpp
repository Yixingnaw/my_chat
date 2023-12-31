#include "widget.h"
#include "ui_widget.h"
#include"signup.h"
#include<QHostAddress>
#include<QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include<QByteArray>
#include<QMessageBox>
#include"qqcontact.h"
#include"friendchatwoker.h"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    log_on=new QTcpSocket();

    data_initial=false;
   first_initial=false;
   group_initial=false;
   // qq_contact->hide();
    connect(log_on,&QTcpSocket::readyRead,[&](){

        QByteArray date=log_on->readAll();
         QJsonDocument  newDocument;
          QJsonObject   newObject;
          if(data_initial&&!group_initial){
              ui_data.append(date);
             if(ui_data.size()<bytesToInt(ui_data.left(4))){//  读完请求界面的数据
                 return ;
             }
           //  if(bytesToInt(ui_data.mid(4,4))==43){ data_initial=false      ;return ;}//第一ge登录
             qint32 length_json= bytesToInt(  ui_data.mid(4,4));
             QByteArray data=ui_data.mid(8,length_json);
             newDocument = QJsonDocument::fromJson(data);
             newObject = newDocument.object();
      }else if (data_initial&&group_initial) {
             group_ui_data.append(date);
             int x=group_ui_data.size();
             int jjk= bytesToInt(group_ui_data.left(4));
             if(group_ui_data.size()<bytesToInt(group_ui_data.left(4))){//  读完请求界面的数据
                 return ;
             }
             if(bytesToInt(group_ui_data.mid(4,4))==43){           data_initial=false;group_initial=false     ;return ;}
             qint32 length_json= bytesToInt( group_ui_data.mid(4,4));
             QByteArray data=group_ui_data.mid(8,length_json);
             newDocument = QJsonDocument::fromJson(data);
             newObject = newDocument.object();
}
          else if(!data_initial&&!first_initial)  {   // 得到请求界面的数据
              newDocument = QJsonDocument::fromJson(date);
              newObject = newDocument.object();

          }else  if(!data_initial&&first_initial){

              ui_data_.append(date);            
             if(ui_data_.size()<bytesToInt(ui_data_.left(4))){//  读完请求界面的数据
                 return ;
             }     qint32 length_json= bytesToInt(  ui_data_.mid(4,4));
             QByteArray data=ui_data_.mid(8,length_json);
             newDocument = QJsonDocument::fromJson(data);
             newObject = newDocument.object();
}

           QString typeString = newObject.value("type").toString();
           // 确保 "type" 字段的值确实是一个整数的字符串表示
           bool conversionOk;
           int case_x = typeString.toInt(&conversionOk);                                                         //bug int case_x=newObject.value("type").toInt();
           switch (case_x) {

           case 0:{
               QString xx=newObject.value("value").toString();
               QMessageBox *message=new QMessageBox();
               message->show();
               message->setText(xx);
           }break;
           case 1:{//success in //bind udp
                //获取自己的头像
               myname=newObject.value("name").toString();
             //请求界面初始化
               data_initial=true;
                    QJsonObject jsonObject;
                    jsonObject["type"]="3";
                     QJsonDocument jsonDocument(jsonObject);
                     QByteArray jsonData = jsonDocument.toJson();
                     log_on->write(jsonData);
                       qq_contact=new qqContact(myname,log_on);
               hide();
                 qq_contact->show();
           }break;
           case 10:{
               QString xx=newObject.value("value").toString();
               QMessageBox *message=new QMessageBox();
                 message->show();
               message->setText(xx);
           }break;
           case 11:{
               QString xx=newObject.value("value").toString();
               QMessageBox *message=new QMessageBox();
                 message->show();
               message->setText(xx);
           }break;
           case 20:{
               QString xx=newObject.value("value").toString();
               QMessageBox *message=new QMessageBox();
                 message->show();
               message->setText(xx);
           }break;
           case 30:{ //收到服务器更新请求的回应
                        first_initial=true;//准备更新好友界面
                        QJsonObject jsonObject;
                        jsonObject["type"]="8";
                         QJsonDocument jsonDocument(jsonObject);
                         QByteArray jsonData = jsonDocument.toJson();
                         log_on->write(jsonData);

           }break;
           case 31:{//用来接受服务器新登录好友界面
                       first_initial=false;
                       QByteArray image__data=ui_data_.mid(8+bytesToInt(ui_data_.mid(4,4)));

                        QJsonArray jsonArray=newObject["value"].toArray();
                        // 将 JSON 数组转换为 JSON 文档
                        QJsonDocument jsonDoc(jsonArray);
                        // 将 JSON 文档转换为 QByteArray
                        QByteArray byteArray = jsonDoc.toJson();

                          qq_contact->initial_friend_ui(byteArray,image__data);
                          qq_contact->update();
                             ui_data_.clear();// 每次数据都应该更新
           }break;

           case 40:{

           }break;
           case 41:{
               //服务器界面初始化
              QByteArray image__data=ui_data.mid(8+bytesToInt(ui_data.mid(4,4)));
               QJsonArray jsonArray=newObject["value"].toArray();
               // 将 JSON 数组转换为 JSON 文档
               QJsonDocument jsonDoc(jsonArray);
               // 将 JSON 文档转换为 QByteArray
               QByteArray byteArray = jsonDoc.toJson();
                 qq_contact->initial_friend_ui(byteArray,image__data);
                 qq_contact->update();
                 //请求群界面初始化
                 QJsonObject jsonObject;
                 jsonObject["type"]="5";
                  QJsonDocument jsonDocument(jsonObject);
                  QByteArray jsonData = jsonDocument.toJson();
                  log_on->write(jsonData);

                    group_initial=true;
           }break;
           case 50:{


           }break;
           case  51:{// 群界面初始化
               //start group界面初始化
              QByteArray image__data=group_ui_data.mid(8+bytesToInt(group_ui_data.mid(4,4)));
               QJsonArray jsonArray=newObject["value"].toArray();
               QJsonDocument jsonDoc(jsonArray);
               QByteArray byteArray = jsonDoc.toJson();
                 qq_contact->initial_group_ui(byteArray,image__data);
                 qq_contact->update();
               data_initial=false;
               group_initial=false;
           }break;
           case 60:{


           }break;
           case 61:{//接受群消息
              QString group_count=newObject.value("group_count").toString();
              QString message=newObject.value("message").toString();
              qq_contact->qqcontact_on_read_group_message(group_count,message);

           }break;
           case 70:{
               QString xx=newObject.value("value").toString();
               QMessageBox *message=new QMessageBox();
                 message->show();
               message->setText(xx);
           }break;
           case 71:{
               QString xx=newObject.value("group_count").toString();
               QMessageBox *message=new QMessageBox();
                 message->show();
               message->setText(xx);
           }break;
           default:break;

}      return ;
    });
    connect(log_on,&QTcpSocket::disconnected,[=]{
        QMessageBox *newss=new QMessageBox();
        newss->setText("not found server,client will quit");
    });
}

Widget::~Widget()
{
    delete ui;
    log_on->deleteLater();
}


void Widget::on_sign_up_clicked()
{

    signUp *sign_up=new signUp;
    sign_up->show();
    return;
}

void Widget::on_log_on_clicked()
{
    log_on->connectToHost(QHostAddress("127.0.0.1"),9998);
    QString username=ui->user_input->text();
    QString password=ui->password_input->text();
    QJsonObject jsonObject;
    jsonObject["type"]="0";
    jsonObject["username"] = username;
    jsonObject["password"] = password;

    // 将 JSON 对象转换为 JSON 文档
    QJsonDocument jsonDocument(jsonObject);

    // 将 JSON 文档转换为字节数组
    QByteArray jsonData = jsonDocument.toJson();

    // 发送 JSON 数据
    log_on->write(jsonData);
    log_on->waitForBytesWritten();

}

