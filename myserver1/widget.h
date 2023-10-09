#ifndef WIDGET_H
#define WIDGET_H
#include<QList>
#include <QWidget>
#include<QTcpServer>
#include"chat.h"
#include"tcpserver.h"
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
    void on_listen_socket_clicked();


protected:
    void client_sockt_come();// slot function

    void on_listen_register_come();

private:
    Ui::Widget *ui;

    tcpServer *listen_socket;

     QTcpServer *listen_register_socket;
    chat *chatwidget;
};
#endif // WIDGET_H
