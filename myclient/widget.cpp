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
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    log_on=new QTcpSocket();
    connect(log_on,&QTcpSocket::readyRead,[=](){
           QByteArray byte_json=log_on->readAll();
           int x=byte_json.toInt();
           QMessageBox *messagebox1;
           switch (x) {
           case  0:
               messagebox1=new QMessageBox();
              messagebox1->setText("don't have username");
               return;
               break;
           case  1:
               messagebox1=new QMessageBox();
              messagebox1->setText("password error");
               return ;
               break;
           case 2:
               qqContact *qqccontact=new qqContact();
               qqccontact->show();
               return ;
           }return ;


    });
}

Widget::~Widget()
{
    delete ui;
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
