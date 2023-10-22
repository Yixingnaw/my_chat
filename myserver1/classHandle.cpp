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
#include<QSqlError>
#include<mutex>
#include<QDir>
#include"imagechangge.h"
#include<QHostAddress>
#include<unordered_set>
classHandle::classHandle(qintptr socketDescriptor){
    socket_Descriptor=socketDescriptor;
    image_count=0;
    caohanshu=true;
}

void classHandle::run(){
      bool succeein=false;//用户是否登录成功
      myTcpSockt socket;
      qqUser *new_user;//用户信息
    int my_id;       //用户id
      std::unordered_map<int,qqUser>::iterator qquser_id_it;//gloabal用户id指针，方便断开连接时删除
   //disconneted
      std::unordered_map<qqUser, myTcpSockt*>::iterator   it;//gloable用户指针，方便断开连接时删除
   QVector<int> uer_friend_ids;                            //用户所有好友信息id
   QVector<int>user_online_friend_ids;                     //用户在线好友信息id
   std::unordered_set<qqUser> online_friend;                //用户在线好友信息
      sigleInstance *single=nullptr;
        QObject::connect(&socket,&QTcpSocket::disconnected,[&]{
              mutex.lock();
              if(succeein){
             onlineUsers.erase(it);
             onlineIDs.erase(qquser_id_it);}
                                                        qDebug()<<"断开连接还剩多少在线"<<onlineUsers.size();
             mutex.unlock();
        });

        if (!socket.setSocketDescriptor(socket_Descriptor) ){
            qDebug() << "Failed to set socket descriptor.";
            return;
        }

        while (socket.state() == QAbstractSocket::ConnectedState&&caohanshu) {
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

                               QByteArray jsonData = jsonDocument.toJson();
                        socket.write(jsonData);
                                                                                                     qDebug()<<jsonData;
                         return ;
                       
                     }// success sign in,  jia ru zai xian lie biao
                     else {
                       mutex.lock();
                        QString user_name=new_user->getUsername();
                   succeein=true;
                  auto xx=        onlineUsers.emplace(*new_user,&socket);
                  auto xxx=onlineIDs.emplace(my_id,*new_user);
                   it=xx.first;
                    qquser_id_it=xxx.first;
                       mutex.unlock();                                                                              qDebug()<<"登录成功，在线好友数"<<onlineUsers.size();

                       //查找用户所有的好友id,保存在vector中
                  QString queryString = QString("SELECT users.* "
                                                         "FROM friendships "
                                                         "JOIN users ON (friendships.user_id1 = users.user_id OR friendships.user_id2 = users.user_id) "
                                                         "WHERE (friendships.user_id1 = %1 OR friendships.user_id2 = %1) AND users.user_id != %1")
                                               .arg(my_id);
                  db.executeQuery(queryString);
                    mutex_rb.lock();
                    while(db.query.next()) {
                        int id=db.query.value(0).toInt();
                        uer_friend_ids.push_back(id);
                    }mutex_rb.unlock();
                    //
                    for(auto value:onlineIDs){
                        for(auto id_:uer_friend_ids){
                            if(id_==value.first&&id_!=my_id){
                                user_online_friend_ids.push_back(id_);
                            }
                        }
                    }
                    for(auto x:user_online_friend_ids){
                        online_friend.emplace(onlineIDs[x]);
                    }
                      //通知每个在线好友有新的好友登录
                    {//遍历用户在线好友信息得到每一个socket
                        QJsonObject jsonObject;
                           jsonObject["type"]="30";
                           QJsonDocument jsonDocument(jsonObject);

                              QByteArray jsonData = jsonDocument.toJson();                                              qDebug()<<jsonData;

                        for(auto qquser:online_friend){
                          single=new sigleInstance();
                   //  QObject::connect(single, SIGNAL(sendmesssage(QByteArray)), onlineUsers[qquser], SLOT(getmessage(QByteArray)),Qt::QueuedConnection);
                     //QObject::connect(single, SIGNAL(sendmesssage(QByteArray)), onlineUsers[qquser], SLOT(getmessage(QByteArray)),Qt::QueuedConnection);
                                onlineUsers[qquser]->write(jsonData);
                        }
                        if(single!=nullptr);
                       //     single->send(jsonData);
                    }
                       QJsonObject jsonObject;
                          jsonObject["type"]="1";
                          jsonObject["name"]=new_user->getNikename();
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
                                                                                                         qDebug()<<"开始添加好友";
        /*  auto    it  = std::find_if(onlineUsers.begin(), onlineUsers.end(), [&](const std::pair<const qqUser, QTcpSocket*>& element) {
                           return element.first == *new_user;
                       });
                          my_Name=(*it).first.getUsername();*/
                            my_Name=new_user->getUsername();
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
                                                                                                     //   qDebug()<<"zhao daole zi ji de  mingzi";
                      if(db.executeQuery("SELECT user_id FROM users WHERE username = '"+my_Name+"' OR username = '"+use_Name+"'"))
                      {
                          int my_id;
                          int other_id;
                          if(db.query.next())
                               my_id=db.query.value(0).toInt();
                          else {                                                                           //    qDebug()<<"zhao dao le";
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
                          else {                                                                               // qDebug()<<"zhao dao le";
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

                          QString queryString = QString("SELECT * FROM friendships "
                                                        "WHERE "
                                                        "(user_id1 = %1 AND user_id2 = %2) "
                                                        "OR (user_id1 = %2 AND user_id2 = %1)")
                                              .arg(my_id).arg(other_id);

                         if (db.executeQuery(queryString)&& db.query.next()) {
                             QJsonObject jsonObject;
                             jsonObject["type"]="10";
                             jsonObject["value"]="是你的好友了，你加你妈呢";
                             QJsonDocument jsonDocument(jsonObject);
                                // 将 JSON 文档转换为字节数组
                           QByteArray jsonData = jsonDocument.toJson();
                         socket.write(jsonData);
                         mutex_rb.unlock();
                                             break;
                          }
                               mutex_rb.unlock();                                                                                          qDebug()<<"一切准备就绪添加好友";
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
                                                                                                                  qDebug()<<"添加好友成功";
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
                         socket.write(jsonData);                                                                                 qDebug()<<"添加好友失败";

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
                   case 3:                                     //界面初始化
{

               QJsonObject mainobject;
               mainobject["type"]="41";
               QJsonArray qquser_json_array;
               for(auto x:online_friend){
                   QJsonObject object;
                   object["username"]=x.getUsername();
                   object["nickname"]=x.getNikename();
                   object["photoaddress"]=x.getUserPhone();
                   object["ip"]=onlineUsers[x]->peerAddress().toString();  //好友ip

                    qquser_json_array.append(object);
               }
               mainobject["value"]=qquser_json_array;
               QJsonDocument document(mainobject);
               QByteArray senddata=document.toJson();

               qint32 lenght=senddata.length();
               QByteArray data_json;
                data_json+=intToBytes(lenght);
               data_json+=senddata;//jsonlength和jsondata
                                                                           qDebug()<< "json长"<<  bytesToInt(data_json.left(4));

               QByteArray imgdata;  //imagedata
               for(auto x:online_friend){
                   QString address=x.getUserPhone();
                   QByteArray img;
         try      {    img=imagechange()(x.getUserPhone());}
                   catch(const QString& x){qDebug()<<x;}
                   qint32 imgLength=img.length();
                   QByteArray data_json;
                    data_json+=intToBytes(imgLength);
                   data_json+=img;
                   imgdata+=data_json;
               }
               qint32 img_length=imgdata.length();

              QByteArray data;
              qint32 data_length=data_json.length()+img_length+4;// 数据总长

             data+=intToBytes(data_length);
              data+=data_json;
              data+=imgdata;
              qint32 length_json=bytesToInt(data.mid(4,4));
             qint32 leth=bytesToInt(data.left(4));
                                                                     qDebug()<<length_json<<":初次登录时所有好友json数据长"<<leth<<":总数据长";
               socket.write(data);


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
                                                                                                   qDebug()<<"创建群成功";
              
                      QJsonObject echo_json;
                      echo_json["type"]="71";
                      echo_json["group_count"]=group_count;
                      QJsonDocument echojosodocument(echo_json);
                      QByteArray ss=echojosodocument.toJson();
                     socket.write(ss);

}break;
                  case 8://服务器发送更新好友界面
{                 qqUser* new_user;
                  //找到新上线的好友
                     for(auto x:onlineIDs){
                         for(auto y:uer_friend_ids){
                             if(x.first==y){
                                 if(user_online_friend_ids.indexOf(y)==-1)
                                 {
                                     user_online_friend_ids.push_back(y);
                                     new_user=&onlineIDs[y];

                                 }
                             }
                         }
                      }

                      QJsonObject mainobject;
                      mainobject["type"]="31";
                      QJsonArray qquser_json_array;
                         QJsonObject object;
                          object["username"]=new_user->getUsername();
                          object["nickname"]=new_user->getNikename();
                          object["photoaddress"]=new_user->getUserPhone();
                          object["ip"]=onlineUsers[*new_user]->peerAddress().toString();


                           qquser_json_array.append(object);

                      mainobject["value"]=qquser_json_array;
                      QJsonDocument document(mainobject);
                      QByteArray senddata=document.toJson();

                      qint32 lenght=senddata.length();
                      QByteArray data_json;
                       data_json+=intToBytes(lenght);
                      data_json+=senddata;//jsonlength和jsondata
                                                 qDebug()<<   bytesToInt(data_json.left(4));

                      QByteArray imgdata;  //imagedata

                          QString address=new_user->getUserPhone();
                          QByteArray img;
                try      {    img=imagechange()(new_user->getUserPhone());}
                          catch(const QString& x){qDebug()<<x;}
                          qint32 imgLength=img.length();
                          QByteArray data_json_;
                           data_json_+=intToBytes(imgLength);
                          data_json_+=img;
                          imgdata+=data_json_;

                      qint32 img_length=imgdata.length();

                     QByteArray data;
                     qint32 data_length=data_json.length()+img_length+4;// 数据总长

                    data+=intToBytes(data_length);
                     data+=data_json;
                     data+=imgdata;
                     qint32 length_json=data.mid(4,4).toInt();
                    qint32 leth=bytesToInt(data.left(4));
                                                                                      qDebug()<<length_json<<":界面更新时所有好友json数据长 "<<leth<<":总长";
                      socket.write(data);


}break;
                  default:break;
                  }



    }        


        }
           QCoreApplication::processEvents();
           return;
}

void classHandle::change(bool x){
    caohanshu=x;
}
QString    classHandle:: get_ip_address(QTcpSocket* socket){
   /* QHostAddress peerAddress = socket  ->peerAddress();
    QString ipAddress = peerAddress.toString(); // 获取对端 IP 地址的字符串形式

                                                                                          qDebug() << "对端 IP 地址：" << ipAddress;
      return ipAddress;*/

    QThread *currentThread = QThread::currentThread();
       Qt::HANDLE threadId = currentThread->currentThreadId();

       // 获取当前线程的名字
       const char *threadName = currentThread->objectName().toUtf8().constData();

       // 输出线程信息
       qDebug() << "Current Thread ID:" << threadId;
       qDebug() << "Current Thread Name:" << threadName;
}
QByteArray qquserData(qqUser* new_user){
                          QJsonObject mainobject;
                          mainobject["type"]="31";
                          QJsonArray qquser_json_array;
                             QJsonObject object;
                              object["username"]=new_user->getUsername();
                              object["nickname"]=new_user->getNikename();
                              object["photoaddress"]=new_user->getUserPhone();
                              object["ip"]=onlineUsers[*new_user]->peerAddress().toString();

                               qquser_json_array.append(object);

                          mainobject["value"]=qquser_json_array;
                          QJsonDocument document(mainobject);
                          QByteArray senddata=document.toJson();

                          qint32 lenght=senddata.length();
                          QByteArray data_json;
                           data_json+=intToBytes(lenght);
                          data_json+=senddata;//jsonlength和jsondata
                                                     qDebug()<<   bytesToInt(data_json.left(4));

                          QByteArray imgdata;  //imagedata

                              QString address=new_user->getUserPhone();
                              QByteArray img;
                    try      {    img=imagechange()(new_user->getUserPhone());}
                              catch(const QString& x){qDebug()<<x;}
                              qint32 imgLength=img.length();
                              QByteArray data_json_;
                               data_json_+=intToBytes(imgLength);
                              data_json_+=img;
                              imgdata+=data_json_;

                          qint32 img_length=imgdata.length();

                         QByteArray data;
                         qint32 data_length=data_json.length()+img_length+4;// 数据总长

                        data+=intToBytes(data_length);
                         data+=data_json;
                         data+=imgdata;
                            return data;
}
