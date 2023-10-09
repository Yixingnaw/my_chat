#include"classHandle.h"
#include<QTcpSocket>
#include"global.h"
#include"sql.h"
#include"qquser.h"
#include<QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include<algorithm>
#include<QByteArray>
#include<mutex>
classHandle::classHandle(qintptr socketDescriptor){
    socket_Descriptor=socketDescriptor;
}

void classHandle::run(){

        QTcpSocket socket;
        if (!socket.setSocketDescriptor(socket_Descriptor) ){
            qDebug() << "Failed to set socket descriptor.";
            return;
        }
       qqUser *new_user;
        while (socket.state() == QAbstractSocket::ConnectedState) {
            if (socket.waitForReadyRead()) {

                QByteArray data = socket.readAll();
                 QJsonDocument   newDocument = QJsonDocument::fromJson(data);
                   QJsonObject   newObject = newDocument.object();
                  int case_x=newObject.value("type").toInt();

                  switch (case_x) {
                  case 0:
{
                    QString use_Name=newObject.value("username").toString();
                    QString pass__word=newObject.value("password").toString();


                    if(db.executeQuery("select * from users where username ='"+use_Name+"'and password ='"+pass__word+"'")&&db.query.next()){
                     mutex_rb.lock();
                     QString column1Value = db.query.value(1).toString(); // username
                      QString column2Value =db. query.value(2).toString(); // password
                      QString nickName;
                    db.query.prepare("SELECT nickname FROM users WHERE username = :username");
                    db.query.bindValue(":username", column1Value);
                    if(db.query.exec()&&db.query.next())
                        nickName=db.query.value(0).toString();
                    mutex_rb.unlock();

                  new_user=new qqUser(column1Value,column2Value,nickName);
                     if(!(onlineUsers.find(*new_user)==onlineUsers.end()))
                      {
                         QJsonObject jsonObject;
                            jsonObject["type"]="0";
                            jsonObject["value"]="already online";
                            QJsonDocument jsonDocument(jsonObject);
                               // 将 JSON 文档转换为字节数组
                               QByteArray jsonData = jsonDocument.toJson();
                        socket.write(jsonData);
                                                                                  qDebug()<<jsonData;
                         return ;

                     }// success sign in
                     else {
                       mutex_rb.lock();
                        QString user_name=new_user->getUsername();
                        db.query.prepare("select");
                       mutex_rb.unlock();
//hai mei  xie wan
                       mutex.lock();                    
                       onlineUsers.emplace(*new_user,&socket);
                       mutex.unlock();                                                                              qDebug()<<"concc";
                     }
                  }
                     else{
                        QJsonObject jsonObject;
                           jsonObject["type"]="0";
                           jsonObject["value"]="input error";
                           QJsonDocument jsonDocument(jsonObject);
                              // 将 JSON 文档转换为字节数组
                              QByteArray jsonData = jsonDocument.toJson();

                       socket.write(jsonData);
                       return;

                  }
}
                      break;
                  case 1:
{                     QString use_Name=newObject.value("username").toString();
                       QString my_Name;
                                                                                                         qDebug()<<"fuwuqi kaishi tianjia";
                       auto it = std::find_if(onlineUsers.begin(), onlineUsers.end(), [&new_user](const std::pair<const qqUser, QTcpSocket*>& element) {
                           return element.first == *new_user;
                       });
                          my_Name=(*it).first.getUsername();
                                                                                                          qDebug()<<"zhao daole zi ji de  mingzi";
                      if(db.executeQuery("select * from users where username ='"+use_Name+"'")&&db.query.next())
                      {
                          //insert into friendships;
                          mutex_rb.lock();
                    //      db.executeQuery("");
                          mutex_rb.unlock();
                                                                                                           qDebug()<<"shujuku jia zai wancheng";
                          QJsonObject jsonObject;
                     jsonObject["type"]="2";
                     jsonObject["value"]="add successed";
                     QJsonDocument jsonDocument(jsonObject);
                        // 将 JSON 文档转换为字节数组
                        QByteArray jsonData = jsonDocument.toJson();
                 socket.write(jsonData);
                        }
                          else {
                                  QJsonObject jsonObject;
                             jsonObject["type"]="3";
                             jsonObject["value"]="no users";
                             QJsonDocument jsonDocument(jsonObject);
                                // 将 JSON 文档转换为字节数组
                                QByteArray jsonData = jsonDocument.toJson();
                         socket.write(jsonData);

                      }

}                     break;
                  case 2:
                      break;
                   case 3:
                      break;
                   case 4:
                      break;
                  default:break;
                  }



    }
            socket.deleteLater();
           //qqUser mei shan.

        }
}
