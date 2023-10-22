#ifndef WIDGET_H
#define WIDGET_H
#include<thread>
#include <QWidget>
#include<QTcpSocket>
#include"qqcontact.h"
#include<QUdpSocket>
#include<mutex>
#include<QSet>
#include"global.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();


private slots:
    void on_sign_up_clicked();

    void on_log_on_clicked();
private:
    Ui::Widget *ui;
public:
    QTcpSocket *log_on;
    qqContact* qq_contact;

    bool data_initial;//用来开启客户端对服务器界面的请求,区分不同的数据
     QByteArray ui_data;
    bool first_initial;//用来接受服务器新登录好友信息
    QByteArray ui_data_;//用来接受服务器新登录好友界面
    qint32 data_length;//初始化界面数据长度
    QString myname;
};
#endif // WIDGET_H
