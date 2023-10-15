#ifndef GROUPCREATE_H
#define GROUPCREATE_H

#include <QWidget>
#include<QString>
#include"myheadlable.h"
#include<QTcpSocket>
namespace Ui {
class groupcreate;
}

class groupcreate : public QWidget
{
    Q_OBJECT

public:
    explicit groupcreate(QTcpSocket*tcp=nullptr,QWidget *parent = nullptr);
    ~groupcreate();

private slots:
    void on_send_clicked();

private:
    Ui::groupcreate *ui;
    QString imagepath;
     myheadlable *head_label;
    QTcpSocket *tcp_;
};

#endif // GROUPCREATE_H
