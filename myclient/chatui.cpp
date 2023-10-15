#include "chatui.h"
#include "ui_chatui.h"

chatUi::chatUi(QTcpSocket* sock,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chatUi)
{
    ui->setupUi(this);
    tcp=sock;
}

chatUi::~chatUi()
{
    delete ui;
}
