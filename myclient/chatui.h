#ifndef CHATUI_H
#define CHATUI_H

#include <QDialog>
#include "ui_chatui.h"
#include<QDateTime>
#include<QUdpSocket>
#include<QCloseEvent>
namespace Ui {
class chatUi;
}

class chatUi : public QDialog
{
    Q_OBJECT

public:
    explicit chatUi(QString mine,QString other,QUdpSocket *udp_,QWidget *parent = nullptr);
   void addMessage(const QString &nickname, const QString &message);
    ~chatUi();

public:
    QString my_name;
    QString friend_name;
    QUdpSocket *udp_socket;
    Ui::chatUi *ui;
    void closeEvent(QCloseEvent *event);

private slots:
    void on_send_clicked();
};

#endif // CHATUI_H
