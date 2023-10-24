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
#include"chatui.h"
#include"global.h"
#include"friendchatwoker.h"
#include"group_contact.h"
namespace Ui {
class qqContact;
}

class qqContact : public QWidget
{
    Q_OBJECT

public:
    explicit qqContact(QString name,QTcpSocket * xx=nullptr,QWidget *parent = nullptr);
    ~qqContact();


private slots:
    void on_add_friend_clicked();

    void on_listWidget_currentRowChanged(int currentRow);
    void on_friends_itemClicked(QListWidgetItem *item);
    void on_group_create_clicked();

    void readPendingDatagrams();
     void on_add_group_clicked();

//   void on_friends_itemDoubleClicked(QListWidgetItem *item);
   
     void on_listWidget_itemClicked(QListWidgetItem *item);

public:
    groupcreate *newgroup;
     QTcpSocket *socket;
     Ui::qqContact *ui;
     QImage user_head;
     QUdpSocket *udpSocket;
     std::unordered_map<qqUser,QImage*> friends;//
     std::mutex mutex_friend;


     QMap<QString,QListWidgetItem*>  friends_ip;//ip key
     QMap<QString,chatUi*> chat_map;//ip key  记录friend界面数

     QMap<QString,QListWidgetItem*> group_count_; //group_count key
     QMap<QString,group_contact*>group_contact_map;

     std::mutex mutex_groups;
     QString my_name;

//function
public:
       void  initial_friend_ui(const QByteArray& x,const QByteArray& imagedata);
       void   initial_group_ui(const QByteArray& x,const QByteArray& imagedata);
  //not complete     QSet<QString>
        void qqcontact_on_read_group_message(QString group__count,QString message);
};

#endif // QQCONTACT_H
