#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QTcpSocket>
#include"qqcontact.h"
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
};
#endif // WIDGET_H
