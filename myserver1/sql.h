#ifndef SQL_H
#define SQL_H
#include <QString>
#include <QDebug>
#include<QtSql/QSqlDatabase>
#include<QSqlQuery>
#include<mutex>
class sql
{
public:
    sql();
    bool executeQuery(const QString &queryStr);

    ~sql();

     QSqlQuery query;
     QSqlQuery& fquery();
private:
    QSqlDatabase db;
    std::mutex mutx;

    sql(const sql&);
    sql& operator==(const sql&);
};


#endif // SQL_H
