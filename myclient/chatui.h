#ifndef CHATUI_H
#define CHATUI_H

#include <QDialog>
#include<QTcpSocket>
namespace Ui {
class chatUi;
}

class chatUi : public QDialog
{
    Q_OBJECT

public:
    explicit chatUi(QTcpSocket *sock=nullptr,QWidget *parent = nullptr);
    ~chatUi();

private:
    Ui::chatUi *ui;
    QTcpSocket *tcp;
};

#endif // CHATUI_H
