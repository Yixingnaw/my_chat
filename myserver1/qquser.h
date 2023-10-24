#ifndef QQUSER_H
#define QQUSER_H
#include<QtSql/QSqlDatabase>
#include<string>

class qqUser
{

public:
 qqUser(QString user_name="root",QString pass_word="123456",QString nikeName="马保国",QString xx="");
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
   bool operator<(const qqUser& x)const{
       return  username<x.username;
   }
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

#endif // QQUSER_H

