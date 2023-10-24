#include "group_contact.h"
#include "ui_group_contact.h"

group_contact::group_contact(QString myname,QString group__count,QTcpSocket*tcp,QWidget *parent) :
    QWidget(parent),
    mine_name(myname),
    group_count(group__count),
    tcp_(tcp),
    ui(new Ui::group_contact)
{
    ui->setupUi(this);
}

group_contact::~group_contact()
{
    delete ui;
}

void group_contact::on_send_clicked()
{
         QString message=ui->lineEdit->text();
         addMessage(mine_name,message);
         ui->lineEdit->clear();

}
void    group_contact::addMessage(const QString &nickname, const QString &message) {
    // 获取当前时间
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString timeStr = currentDateTime.toString("hh:mm:ss");
    // 构建要添加的消息，应用富文本格式
    QString newMessage ="<font color='green'>" + nickname + "</font> ";
    newMessage += "<font color='blue'>" + timeStr + "</font><br>";
    newMessage += "<font color='black'>" + message + "</font>";
    // 使用富文本格式追加消息到聊天框
   ui->textEdit->insertHtml("<br>" + newMessage + "<br>");

     QJsonObject jsonObject;
     jsonObject["type"]="6";
     jsonObject["group_count"]=group_count;
     jsonObject["message"]=newMessage;

     QJsonDocument jsonDocument(jsonObject);
     QByteArray jsonData = jsonDocument.toJson();
     tcp_->write(jsonData);

}
void   group_contact:: view(const QByteArray &message){
    ui->textEdit->insertHtml(QString::fromUtf8(message));
}
void group_contact::closeEvent(QCloseEvent *event) {
    // 阻止窗口关闭
    event->ignore();

    // 隐藏窗口而不是关闭
    hide();
}
