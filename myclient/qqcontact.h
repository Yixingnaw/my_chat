#ifndef QQCONTACT_H
#define QQCONTACT_H

#include <QWidget>
#include<QTcpSocket>
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

private:
     QTcpSocket *socket;
     Ui::qqContact *ui;
};

#endif // QQCONTACT_H
