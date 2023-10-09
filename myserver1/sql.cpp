#include <QString>
#include <QDebug>
#include<QtSql/QSqlDatabase>
#include"sql.h"
#include<QSqlQuery>
#include<QSqlError>
sql::sql()
{

    // 初始化数据库连接
    db = QSqlDatabase::addDatabase("QMYSQL"); // 使用SQLite驱动程序
    db.setHostName("127.0.0.1");    //数据库服务器IP，本地服务器
        db.setPort(3306);               //端口号
        db.setDatabaseName("chat");     //数据库名
        db.setUserName("root");         //用户名
        db.setPassword("511304");       //密码

    if (!db.open())
    {
        qDebug() << "Error: Failed to connect to the database.";
    }
    else
    {
        qDebug() << "Connected to the database.";
     }
      query=QSqlQuery(db);
}
    //
bool sql::executeQuery(const QString &queryStr)
      {
          mutx.lock();
          if (query.exec(queryStr))    //
  {
              return true;
          }
          else
          {
              qDebug() << "Error executing query: " << query.lastError().text();
              return false;
          }
          mutx.unlock();
      }
QSqlQuery& sql::fquery(){

    return   query;
}


sql::~sql(){
    db.close();

}
