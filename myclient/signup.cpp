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
#include<QFileDialog>
#include<QLabel>
#include <QSignalMapper>
#include<imagechange.h>
signUp::signUp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::signUp)
{
    ui->setupUi(this);
    head_label=new myheadlable(this);
    head_label-> setText("选择头像");
    head_label->setMinimumSize(100, 100);
    head_label->setStyleSheet("QLabel { background-color: white; border: 1px solid #000; padding: 10px; }");

    head_label->setGeometry(140, 5, 150, 90);


     connect(head_label,&myheadlable::imagepath,[&](const QString &image){
              imagepash=image;
     });
     connect(ui->sign_up,&QPushButton::clicked,this,&signUp:: pushButton_clicked);

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

void signUp:: pushButton_clicked(){
  if(ui->nike_name->text()==""||ui->password->text()==""||imagepash=="")
    {QMessageBox * local_message=new QMessageBox();
        local_message->setText("please input valied message");
        local_message->show();
        return;
     }

    sginUpSocket *sign_up_sockt=new sginUpSocket();//connect 9999 server port/ipv4;
    qDebug()<<"client has connected";
                                                    //  send json message
                                                         // 创建 JSON 对象

           QString nikename=ui->nike_name->text();
           QString password=ui->password->text();
           QByteArray dataPacket;
            dataPacket.append(imagechange()(imagepash));

           QJsonObject jsonObject;
            jsonObject["nikename"] = nikename;
            jsonObject["password"] = password;

         //   QByteArray jsonBytes = QJsonDocument(jsonObject).toJson();

                         // 将 JSON 对象转换为 JSON 文档
      QJsonDocument jsonDocument(jsonObject);

         QByteArray jsonBytes = jsonDocument.toJson();

          int json_size=jsonBytes.size();
          jsonBytes.append(96-json_size,' ');
          jsonBytes.append(4,char(json_size));
          jsonBytes.append(dataPacket);
            sign_up_sockt->sign_up.write(jsonBytes);

           qDebug()<<"client has send over";

            sign_up_sockt->sign_up.waitForBytesWritten();

           QObject:: connect(&sign_up_sockt->sign_up, &QTcpSocket::disconnected, [sign_up_sockt](){
                // 断开信号触发时，删除 QTcpSocket 对象
                sign_up_sockt->sign_up.deleteLater();
            });

}



sginUpSocket::~sginUpSocket(){

}

