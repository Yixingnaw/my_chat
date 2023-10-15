#include "widget.h"
#include"chat.h"
#include <QApplication>
#include"sql.h"
#include<QString>
#include<thread>
#include<QSqlError>
#include<iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

   QString queryStr = "SELECT COUNT(*) AS user_count FROM users";
   QString  user_name="woaini";    // 检查查询是否执行成功
    if (db.executeQuery(queryStr)){
        // 移动到结果集的第一行
        db.query.first();

        // 获取第一列的值（即 user_count 列的值）
        int userCount = db.query.value(0).toInt();

        qDebug() << "Total number of users: " << userCount;
    }
    else
    {
        qDebug() << "Error executing query: " << db.query.lastError().text();
    }
    Widget w;


    w.show();
    return a.exec();
}