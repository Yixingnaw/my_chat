#ifndef QQCONTACT_H
#define QQCONTACT_H
#include<QUdpSocket>
#include <QWidget>
#include<QTcpSocket>
#include<QListWidgetItem>
#include<unordered_map>
#include"qquser.h"
#include"groupcreate.h"
#include<QHostAddress>
#include<mutex>
#include<QJsonArray>
#include"imagechange.h"
#include"global.h"
namespace Ui {
class qqContact;
}

class qqContact : public QWidget
{
    Q_OBJECT

public:
    explicit qqContact(QTcpSocket * xx=nullptr,QWidget *parent = nullptr);
    ~qqContact();


private slots:
    void on_add_friend_clicked();

    void on_listWidget_currentRowChanged(int currentRow);
    void on_friends_itemClicked(QListWidgetItem *item);
    void on_group_create_clicked();

   //void readPendingDatagrams();
   void on_add_group_clicked();

//   void on_friends_itemDoubleClicked(QListWidgetItem *item);
   
public:
    groupcreate *newgroup;
     QTcpSocket *socket;
     Ui::qqContact *ui;
     QImage user_head;
     QUdpSocket *udpSocket;
     std::unordered_map<qqUser,QImage*> friends;//
     std::mutex mutex_friend;

     QSet<QString> ip_frined;  //记录好友界面数
     std::mutex mutex_groups;  //、记录群界面数

//function
public:
       void  initial_friend_ui(const QByteArray& x,const QByteArray& imagedata);
  //not complete     QSet<QString>
};

#endif // QQCONTACT_H
