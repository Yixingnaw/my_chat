﻿#include"classHandle.h"
#include<QTcpSocket>
#include"global.h"
#include"sql.h"
#include"qquser.h"
#include<QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include<algorithm>
#include<QByteArray>
#include<QSqlError>
#include<mutex>
#include<QDir>
#include"imagechangge.h"
#include<QHostAddress>
classHandle::classHandle(qintptr socketDescriptor){
    socket_Descriptor=socketDescriptor;
    image_count=0;
}

void classHandle::run(){

        QTcpSocket socket;

        if (!socket.setSocketDescriptor(socket_Descriptor) ){
            qDebug() << "Failed to set socket descriptor.";
            return;
        }
       qqUser *new_user;
       int my_id;
           std::unordered_map<int,qqUser>::iterator qquser_id_it;
   //disconneted
           std::unordered_map<qqUser, QTcpSocket*>::iterator   it;
       
        while (socket.state() == QAbstractSocket::ConnectedState) {
            if (socket.waitForReadyRead()) {

                   QByteArray data = socket.readAll();
                     QJsonDocument   newDocument ;
                      QJsonObject   newObject;
                      // image data
                      QByteArray imageData;
                 if(data.size()>250){//register group
                     int json_size=(int)  data[246];
                      QByteArray json_json=data.left(json_size);
                       newDocument=QJsonDocument::fromJson(json_json);
                        newObject=newDocument.object();
                       imageData=data.mid(250);
                   }
                    else{ newDocument = QJsonDocument::fromJson(data);
                     newObject = newDocument.object();
                   }
                     if(newObject.size()==0){qDebug()<<"client input error";}                                                                                //  int case_x=newObject.value("type").toInt();
                  QString typeString = newObject.value("type").toString();
                  // 确保 "type" 字段的值确实是一个整数的字符串表示
                  bool conversionOk;
                  int case_x = typeString.toInt(&conversionOk);
                  switch (case_x) {
                  case 0:                //   sign in
{
                    QString use_Name=newObject.value("username").toString();
                    QString pass__word=newObject.value("password").toString();

                    //查找有没有这个用户
                    if(db.executeQuery("select * from users where username ='"+use_Name+"'and password ='"+pass__word+"'")&&db.query.next()){
                     mutex_rb.lock();
                     QString column1Value = db.query.value(1).toString(); // username
                      QString column2Value =db. query.value(2).toString(); // password
                      QString nickName;
                      QString user_Photo;
                    db.query.prepare("SELECT user_id,nickname,avatar_url FROM users WHERE username = :username");
                    db.query.bindValue(":username", column1Value);
                    if(db.query.exec()&&db.query.next()){
                        my_id=db.query.value(0).toInt();
                        nickName=db.query.value(1).toString();
                        user_Photo=db.query.value(2).toString();}
                    mutex_rb.unlock();

                  new_user=new qqUser(column1Value,column2Value,nickName,user_Photo);
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
                       
                     }// success sign in,  jia ru zai xian lie biao
                     else {
                       mutex_rb.lock();
                        QString user_name=new_user->getUsername();
                        db.query.prepare("select");
                       mutex_rb.unlock();
//hai mei  xie wan
                       mutex.lock();                    
                  auto xx=        onlineUsers.emplace(*new_user,&socket);
                  auto xxx=onlineIDs.emplace(my_id,*new_user);
                   it=xx.first;
                    qquser_id_it=xxx.first;
                       mutex.unlock();                                                                              qDebug()<<"concc"<<onlineUsers.size();
                          QJsonObject jsonObject;
                          jsonObject["type"]="1";
                          jsonObject["value"]="succues online";
                          QJsonDocument jsonDocument(jsonObject);
                          // 将 JSON 文档转换为字节数组
                             QByteArray jsonData = jsonDocument.toJson();                                              qDebug()<<jsonData;
                      socket.write(jsonData);

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
                  case 1:                            //add frineds
{                     QString use_Name=newObject.value("username").toString();
                       QString my_Name;
                                                                                                         qDebug()<<"fuwuqi kaishi tianjia";
          auto    it  = std::find_if(onlineUsers.begin(), onlineUsers.end(), [&new_user](const std::pair<const qqUser, QTcpSocket*>& element) {
                           return element.first == *new_user;
                       });
                          my_Name=(*it).first.getUsername();
                        if(my_Name==use_Name){
                            QJsonObject jsonObject;
                            jsonObject["type"]="10";
                            jsonObject["value"]="amazing!!you add your self!!";
                            QJsonDocument jsonDocument(jsonObject);
                               // 将 JSON 文档转换为字节数组
                          QByteArray jsonData = jsonDocument.toJson();
                        socket.write(jsonData);
                        break;
                        }                                                                              //bu  neng jia yi yang de
                                                                                                        qDebug()<<"zhao daole zi ji de  mingzi";
                      if(db.executeQuery("SELECT user_id FROM users WHERE username = '"+my_Name+"' OR username = '"+use_Name+"'"))
                      {
                          int my_id;
                          int other_id;
                          if(db.query.next())
                               my_id=db.query.value(0).toInt();
                          else {                                                                               qDebug()<<"zhao dao le";
                              QJsonObject jsonObject;
                              jsonObject["type"]="10";
                              jsonObject["value"]="滚你妈的没得 ";
                              QJsonDocument jsonDocument(jsonObject);
                                 // 将 JSON 文档转换为字节数组
                            QByteArray jsonData = jsonDocument.toJson();
                          socket.write(jsonData);
                          break;
                          }
                          if(db.query.next())
                           other_id=db.query.value(0).toInt();
                          else {                                                                                qDebug()<<"zhao dao le";
                              QJsonObject jsonObject;
                              jsonObject["type"]="10";
                              jsonObject["value"]="滚你妈的没得";
                              QJsonDocument jsonDocument(jsonObject);
                                 // 将 JSON 文档转换为字节数组
                            QByteArray jsonData = jsonDocument.toJson();
                          socket.write(jsonData);
                          break;
                          }
                          //查看好友列表里面有没有了
                          mutex_rb.lock();
                          db.query.prepare("SELECT CASE "
                                        "  WHEN user_id1 = :id THEN user_id2 "
                                        "  WHEN user_id2 = :id THEN user_id1 "
                                        "END AS friend_id "
                                        "FROM friendships "
                                        "WHERE user_id1 = :id OR user_id2 = :id");
                          db.query.bindValue(":id", my_id);
                          db.query.exec();
                         if (db.query.next()) {
                             QJsonObject jsonObject;
                             jsonObject["type"]="10";
                             jsonObject["value"]="是你的好友了，你加你妈呢";
                             QJsonDocument jsonDocument(jsonObject);
                                // 将 JSON 文档转换为字节数组
                           QByteArray jsonData = jsonDocument.toJson();
                         socket.write(jsonData);
                          } mutex_rb.unlock();
                            break;
                                                                                                                        qDebug()<<"kai shi cha ru le";
                          mutex_rb.lock();
                         db.query.prepare("INSERT INTO friendships (user_id1, user_id2) VALUES (:id1, :id2)");
                          db.query.bindValue(":id1", my_id);
                          db.query.bindValue(":id2", other_id);
                          if (db.query.exec()) {
                              QJsonObject jsonObject;
                              jsonObject["type"]="10";
                              jsonObject["value"]="哎呦不错哦添加成功了也";
                              QJsonDocument jsonDocument(jsonObject);
                                 // 将 JSON 文档转换为字节数组
                            QByteArray jsonData = jsonDocument.toJson();
                          socket.write(jsonData);
                          } else {
                              // 插入失败，处理错误
                              qDebug() << "Error:" << db.query.lastError().text();
                          }
                          mutex_rb.unlock();
                                                                                                                  qDebug()<<"shujuku jia zai wancheng";
                          QJsonObject jsonObject;
                     jsonObject["type"]="11";
                     jsonObject["value"]="add successed";
                     QJsonDocument jsonDocument(jsonObject);
                        // 将 JSON 文档转换为字节数组
                        QByteArray jsonData = jsonDocument.toJson();
                 socket.write(jsonData);
                        }
                          else {

                             QJsonObject jsonObject;
                             jsonObject["type"]="10";
                             jsonObject["value"]="no users";
                             QJsonDocument jsonDocument(jsonObject);
                                // 将 JSON 文档转换为字节数组
                           QByteArray jsonData = jsonDocument.toJson();
                         socket.write(jsonData);

                      }

}                     break;
                  case 2:                 //add groups
{
                     QString group_count=newObject.value("group_count").toString();
                     int groupid=-1;
                     mutex_rb.lock();
                                               //先看群表有没有这个群
                     if(db.executeQuery("SELECT group_id FROM groups WHERE group_count ='"+group_count+"'") &&db.query.next() )
                       {
                             groupid=db.query.value(0).toInt();
                             mutex_rb.unlock();
                      }else {  QJsonObject jsonObject;
                         jsonObject["type"]="20";
                         jsonObject["value"]="mei you";
                         QJsonDocument jsonDocument(jsonObject);

                       QByteArray jsonData = jsonDocument.toJson();
                     socket.write(jsonData);mutex_rb.unlock();
                     break;
                      }

                     QString queryString = QString("SELECT group_id, user_id FROM group_members WHERE group_id = %1 AND user_id = %2")
                         .arg(groupid)
                         .arg(my_id);
                     db.query.clear();
                     mutex_rb.lock();
                                                    //在检查群表里面有没有自己
           if(db.executeQuery(queryString) &&db.query.next()){
             QJsonObject jsonObject;
             jsonObject["type"]="70";
             jsonObject["value"]="是你的组，你加你妈呢";
             QJsonDocument jsonDocument(jsonObject);
               // 将 JSON 文档转换为字节数组
             QByteArray jsonData = jsonDocument.toJson();
             socket.write(jsonData);
                   mutex_rb.unlock();break;
                     }else{        //没有就插入
               qDebug()<<db.query.value(0);
            QString queryString = QString("INSERT INTO group_members (group_id, user_id) VALUES (%1, %2)")
                .arg(groupid)
                .arg(my_id);
               db.executeQuery(queryString);
                  mutex_rb.unlock();
             }  QJsonObject jsonObject;
               jsonObject["type"]="71";
                 jsonObject["value"]="加群成功";
               QJsonDocument jsonDocument(jsonObject);
             // 将 JSON 文档转换为字节数组
                QByteArray jsonData = jsonDocument.toJson();
                socket.write(jsonData);



}
                      break;
                   case 3:                //the client  groups image  get echo
{

}
                      break;
                   case 4:                //the client  friends image get echo
{

}
                      break;
                   case 5:                 //the client friends chat
{

}
                      break;
                   case 6:                 //the   client groups chat
{
                    
} break;
                   case 7:               //group create
{
                     QString group_Name=newObject.value("groupname").toString();
                      QString description=newObject.value("groupdescribe").toString();                   
                      
                      QString group_count;
                      do{
                         std::shared_ptr<std::string> username =generateRandomAccount();

                      group_count=(*username).c_str();
                         db.executeQuery("select * from groups where group_count like "+group_count);
                     
                         }while(db.query.next());
                       QImage photo;
                   try{    photo=       imagechange().byte_to_qimage(imageData);}
                   catch(const QString &){
                           QJsonObject jsonObject;
                           jsonObject["type"]="70";
                           jsonObject["value"]="图片上传失败请重新传送";
                           QJsonDocument jsonDocument(jsonObject);
                             // 将 JSON 文档转换为字节数组
                           QByteArray jsonData = jsonDocument.toJson();
                           socket.write(jsonData);
                           break;
                      }
                      // 获取当前工作目录
                      QString currentDir = QDir::currentPath();
                      // 使用相对路径
                      QString relativePath = "image_groups/"+ group_count+imagechange().image_postfix(photo); // 以当前工作目录为起点的相对路径
                      // 将相对路径转换为绝对路径
                      QString absolutePath = QDir(currentDir).filePath(relativePath);
                        photo.save(absolutePath);
                        std::mutex mutex;
                     std::lock_guard<std::mutex> lock(mutex);
                db.executeQuery( "INSERT INTO groups (group_name, description, photo_address,group_count) VALUES ('" + group_Name + "', '" + description + "', '" + absolutePath + "','"+group_count+"');");
                                                                                                   qDebug()<<"shu  ju ca ru chenggong";
              
                      QJsonObject echo_json;
                      echo_json["type"]="71";
                      echo_json["group_count"]=group_count;
                      QJsonDocument echojosodocument(echo_json);
                      QByteArray ss=echojosodocument.toJson();
                     socket.write(ss);

}break;
                  default:break;
                  }



    }        


        }
        QJsonObject jsonObject;
          jsonObject["type"]="0";
          jsonObject["value"]="input error";
          QJsonDocument jsonDocument(jsonObject);
            // 将 JSON 文档转换为字节数组
             QByteArray jsonData = jsonDocument.toJson();

        socket.write(jsonData);
        mutex_rb.lock();
       onlineUsers.erase(it);
       onlineIDs.erase(qquser_id_it);
       mutex_rb.unlock();
       QObject::connect(&socket,&QTcpSocket::disconnected,[]{
           QJsonObject jsonObject;
             jsonObject["type"]="-1";
             jsonObject["value"]="not found server";
       });
        socket.deleteLater();
           return;
}


QString    classHandle:: get_ip_address(QTcpSocket* &socket){
    QHostAddress peerAddress = socket  ->peerAddress();
    QString ipAddress = peerAddress.toString(); // 获取对端 IP 地址的字符串形式

                                                                                          qDebug() << "对端 IP 地址：" << ipAddress;
      return ipAddress;
}