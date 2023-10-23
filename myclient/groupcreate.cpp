#include "groupcreate.h"
#include "ui_groupcreate.h"
#include"imagechange.h"
#include"QTcpSocket"
groupcreate::groupcreate(QTcpSocket* tcp,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::groupcreate)
{
    ui->setupUi(this);
    tcp_=tcp;
    head_label=new myheadlable(this);
    head_label-> setText("选择头像");
    head_label->setMinimumSize(100, 100);
    head_label->setStyleSheet("QLabel { background-color: white; border: 1px solid #000; padding: 10px; }");
    head_label->setGeometry(140, 5, 150, 90);

    connect(head_label,&myheadlable::imagepath,[&](const QString &image){
             imagepath=image;
    });

}

groupcreate::~groupcreate()
{
    delete ui;
}

void groupcreate::on_send_clicked()
{
    QString groop_name=ui->gropu_name->text();
    QString  groou_describe=ui->lineEdit->text();
    QByteArray dataPacket;
     dataPacket.append(imagechange()(imagepath));
    QJsonObject jsonObject;
    jsonObject["type"] = "7";//  血泪bug数字7,'7';
    jsonObject["groupname"]=groop_name;
    jsonObject["describe"] = groou_describe;
    QJsonDocument jsonDocument(jsonObject);
       QByteArray jsonBytes = jsonDocument.toJson();
        int json_size=jsonBytes.size(); jsonBytes.append(246-json_size,' ');
        jsonBytes.append(4,char(json_size));
        jsonBytes.append(dataPacket);
        tcp_->write(jsonBytes);
        ui->send->setDisabled(false);
                                                                                                qDebug()<<"client has send over";
        return ;       
}
