#ifndef SIGNUP_H
#define SIGNUP_H

#include <QWidget>
#include<QTcpSocket>
#include<QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
namespace Ui {
class signUp;
}
class  sginUpSocket:public QObject
{
       Q_OBJECT
public:
    sginUpSocket();
    ~sginUpSocket();

public:
    QTcpSocket sign_up;


public slots:


signals:



};
class signUp : public QWidget
{
    Q_OBJECT

public:
    explicit signUp(QWidget *parent = nullptr);
    ~signUp();

private slots:
    void on_pushButton_clicked();

private:
    Ui::signUp *ui;


};




#endif // SIGNUP_H
