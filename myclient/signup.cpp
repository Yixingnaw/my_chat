#include "signup.h"
#include "ui_signup.h"
#include<QHostAddress>
#include<QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include<QString>
#include<QByteArray>
#include<QMessageBox>
#include<QDebug>
signUp::signUp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::signUp)
{
    ui->setupUi(this);
}
sginUpSocket::sginUpSocket():sign_up(){

    QObject::connect(&sign_up,  QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::error),this,[&](QAbstractSocket::SocketError socketError){

        QMessageBox * local_message=new QMessageBox();
                local_message->setText("socket error");
                local_message->show();

     } );
    //read json message;
    connect(&sign_up,&QTcpSocket::readyRead,[&]{
        QByteArray  byte_josn =  sign_up.readAll();

            QJsonDocument newDocument = QJsonDocument::fromJson(byte_josn);
            // 将QJsonDocument转换为JSON对象
             QJsonObject newObject = newDocument.object();

             // 获取JSON对象中的值
             QString name = newObject.value("username").toString();

             QMessageBox * local_message=new QMessageBox();
                     local_message->setText(name);
                     local_message->show();
    });
     sign_up.connectToHost(QHostAddress("127.0.0.1"),9999);

}
signUp::~signUp()
{
    delete ui;

}
void signUp::on_pushButton_clicked()
{
    if(ui->nike_name->text()==""||ui->password->text()=="")
    {QMessageBox * local_message=new QMessageBox();
        local_message->setText("please input valied message");
        local_message->show();
     }

    sginUpSocket *sign_up_sockt=new sginUpSocket();//connect 9999 server port/ipv4;
    qDebug()<<"client has connected";
                                                    //  send json message
                                                         // 创建 JSON 对象
           QString nikename=ui->nike_name->text();
           QString password=ui->password->text();
            QJsonObject jsonObject;
            jsonObject["nikename"] = nikename;
            jsonObject["password"] = password;

                                                          // 将 JSON 对象转换为 JSON 文档
            QJsonDocument jsonDocument(jsonObject);

                                                            // 将 JSON 文档转换为字节数组
            QByteArray jsonData = jsonDocument.toJson();

            // 发送 JSON 数据
            sign_up_sockt->sign_up.write(jsonData);
           qDebug()<<"client has send over";

            sign_up_sockt->sign_up.waitForBytesWritten();


}


sginUpSocket::~sginUpSocket(){

}
