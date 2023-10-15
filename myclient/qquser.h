#ifndef QQUSER_H
#define QQUSER_H
#include<QtSql/QSqlDatabase>
#include<string>
#include<QHash>
#include<QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include<QByteArray>
class qqUser
{

public:
 qqUser(QString user_name="root",QString pass_word="123456",QString nikeName="马保国");
   void swap(qqUser& other) noexcept ;

    qqUser(const qqUser&)noexcept;
    qqUser& operator=(qqUser&& other) noexcept ;
    qqUser& operator=(qqUser& other) noexcept ;
    qqUser(qqUser&& other) noexcept;

        static uint customHash(const qqUser& user) ;
   bool operator!=(const qqUser& other) const;
bool static loadUserByUserName(std::string id);
bool setUser(const qqUser&);
   bool operator==(const qqUser& other) const;

QString getUsername() const {
    return username;
}

QString getPassword() const {
    return password;
}

QString getNikename() const {
    return nikename;
}

QString getUserPhone() const {
    return user_phonte;
}


private:

     QString username;
    QString password;
     QString nikename;
    QString user_phonte;
};
// 声明哈希函数的特化
namespace std {
template <>
    struct hash<qqUser> {
        size_t operator()(const qqUser& user) const {
            return qqUser::customHash(user);
        }
    };
}

#endif // QQUSER_H
