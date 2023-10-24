#ifndef GROUP_CONTACT_H
#define GROUP_CONTACT_H
#include<QTime>
#include <QWidget>
#include<QTcpSocket>
#include<QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include<QCloseEvent>
namespace Ui {
class group_contact;
}

class group_contact : public QWidget
{
    Q_OBJECT

public:
    explicit group_contact(QString myname,QString group__count,QTcpSocket*tcp,QWidget *parent = nullptr);
    ~group_contact();
    void view(const QByteArray &message);
    void addMessage(const QString &nickname, const QString &message);
private slots:
    void on_send_clicked();
   void closeEvent(QCloseEvent *event) override;
private:
   QString mine_name;
   QString group_count;
    QTcpSocket *tcp_;
    Ui::group_contact *ui;
};

#endif // GROUP_CONTACT_H
