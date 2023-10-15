#ifndef FRIENDCHATWOKER_H
#define FRIENDCHATWOKER_H
#include"chatui.h"
#include <QObject>
#include<QThread>
#include<QUdpSocket>
class friendChatWoker : public QObject
{
    Q_OBJECT
public:
    explicit friendChatWoker(QObject *parent = nullptr);
   //  void dofriendChatWork();
signals:

    //     void resultReady(const QString &result);
private:

     QUdpSocket *ucp_friedchat;
     chatUi * friend_chat;
};

class friendChatController : public QObject
{
    Q_OBJECT
    QThread *workerThread;
    public:

   friendChatController() {
        friendChatWoker *worker = new friendChatWoker;
        workerThread=new QThread();
        worker->moveToThread(workerThread);
        //把线程的finished信号和object的deleteLater槽连接，这个信号槽必须连接，否则会内存泄漏
       // connect(workerThread, &QThread::finished, worker, &QObject::deleteLater);
      //  connect(this, &friendChatController ::operate, worker, &friendChatWoker ::dofriendChatWork);
      //  connect(worker, &friendChatWoker::resultReady, this, &friendChatController::handleResults);
        workerThread->start();
    }
   ~friendChatController() {
      //  workerThread->quit();
        //workerThread->wait();
    }
public slots:
   // void handleResults(const QString &);

signals:
   // void operate(const QString &);
};

#endif // FRIENDCHATWOKER_H
