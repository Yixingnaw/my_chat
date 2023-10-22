#include "chatui.h"
#include "ui_chatui.h"

chatUi::chatUi(QString mine,QString other,QUdpSocket *udp_,QWidget *parent) :
    QDialog(parent),
    my_name(mine),
    friend_name(other),
    udp_socket(udp_),
    ui(new Ui::chatUi)
{
    ui->setupUi(this);
}

chatUi::~chatUi()
{
      delete ui;
}
void    chatUi::addMessage(const QString &nickname, const QString &message) {
    // 获取当前时间
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString timeStr = currentDateTime.toString("hh:mm:ss");

    // 构建要添加的消息，应用富文本格式
    QString newMessage ="<font color='green'>" + nickname + "</font> ";
    newMessage += "<font color='blue'>" + timeStr + "</font><br>";
    newMessage += "<font color='black'>" + message + "</font>";

    // 使用富文本格式追加消息到聊天框

    ui->textEdit->insertHtml(newMessage+"\n");
    udp_socket->write(newMessage.toUtf8());
}

void chatUi::closeEvent(QCloseEvent *event) {
    // 阻止窗口关闭
    event->ignore();

    // 隐藏窗口而不是关闭
    hide();
}

void chatUi::on_send_clicked()
{
    QString text=ui->contact->text();
    addMessage(my_name,text);
}
