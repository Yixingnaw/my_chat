#include "chat.h"
#include "ui_chat.h"
#include"global.h"
#include<QString>
#include<QHostAddress>
chat::chat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chat)
{
    ui->setupUi(this);

}

chat::~chat()
{
    delete ui;
}

/*void chat::show_online_numbbers()const
{
     for(auto ptr:onlineUsers){
           QString s=(ptr.first)->peerAddress().toString();
           s+="  ";
           s+=QString::number((ptr.first)->peerPort());
           ui->online_edit->append(s);
     }


}*/
