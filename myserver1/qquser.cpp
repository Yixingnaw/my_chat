#include "qquser.h"
#include"sql.h"
#include"global.h"
#include<string>
#include"glob.h"
#include<QString>
qqUser::qqUser(QString user_name,QString pass_word,QString nikeName)
    :username(user_name),password(pass_word),nikename(nikeName)
{

}


    // 比较操作符，用于哈希表中的比较
    bool qqUser::operator==(const qqUser& other) const {
        return username == other.username && password == other.password;

    }

    // 哈希函数
  uint qqUser::customHash(const qqUser& user) {
        return qHash(user.username) ^ qHash(user.password);
    }
 qqUser:: qqUser(const qqUser&x)noexcept{
     username=x.username;
     password=x.password;
     nikename=x.nikename;
     user_phonte=x.user_phonte;
  }

   qqUser& qqUser:: operator=(qqUser& x )noexcept{
       if(&x==this)return *this;
       username=x.username;
       password=x.password;
       nikename=x.nikename;
       user_phonte=x.user_phonte;
       return  *this;
 }


    // 移动构造函数
   qqUser:: qqUser(qqUser&& other) noexcept {
        swap(other);
    }

    // 移动赋值运算符
    qqUser& qqUser::operator=(qqUser&& other) noexcept {
        if (this != &other) {
            swap(other);
        }
        return *this;
    }

    // 交换函数，用于移动构造函数和移动赋值运算符
    void qqUser:: swap(qqUser& other) noexcept {
        std::swap(username, other.username);
        std::swap(password, other.password);
        std::swap(nikename, other.nikename);
        std::swap(user_phonte, other.user_phonte);
    }

   

bool loadUserByUserName(QString usr_name) {

        db.executeQuery(usr_name);
        return  db.query.next();

}

bool setUser(const qqUser& usr){

}
