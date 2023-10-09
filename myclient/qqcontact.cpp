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
    connect(socket,&QTcpSocket::readyRead,[&](){
          QString add_friend=ui->jiahaoyou->text();
        QByteArray date=socket->readAll();
        QJsonDocument  newDocument = QJsonDocument::fromJson(date);
           QJsonObject   newObject = newDocument.object();
           int case_x=newObject.value("type").toInt();
         if(case_x==20){
             QString xx=newObject.value("value").toString();
             QMessageBox *message=new QMessageBox();
             message->setText(xx);
         }
         else if(case_x==21){
             QString xx=newObject.value("value").toString();
             QMessageBox *message=new QMessageBox();
             message->setText(xx);
         }
                                                                  qDebug()<<date;
         return;
    });
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
