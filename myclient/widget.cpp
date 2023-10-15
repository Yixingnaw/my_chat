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
    qq_contact=new qqContact(log_on);


   // qq_contact->hide();
    connect(log_on,&QTcpSocket::readyRead,[&](){

        QByteArray date=log_on->readAll();
        QJsonDocument  newDocument = QJsonDocument::fromJson(date);
           QJsonObject   newObject = newDocument.object();
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
               qq_contact->show();

               hide();
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
           case 30:{

           }break;
           case 31:{

           }break;

           case 40:{

           }break;
           case 41:{

           }break;
           case 50:{

           }break;
           case  51:{

           }break;
           case 60:{

           }break;
           case 61:{

           }break;
           case 70:{
               QString xx=newObject.value("value").toString();
               QMessageBox *message=new QMessageBox();
                 message->show();
               message->setText(xx);
           }break;
           case 71:{
               QString xx=newObject.value("value").toString();
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

