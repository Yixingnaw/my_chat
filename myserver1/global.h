#ifndef GLOBAL_H
#define GLOBAL_H
#include<QTcpSocket>
#include"sql.h"
#include"qquser.h"
#include<QList>
#include<unordered_map>
#include<memory>
#include <QCoreApplication>
#include <QThread>
#include<string>
#include<QDataStream>
#include"mytcpsockt.h"
#include"classHandle.h"
extern   qint32 bytesToInt(const QByteArray &byteArray) ;
extern sql db;
extern std::unordered_map<qqUser, myTcpSockt*> onlineUsers;
extern std::unordered_map<int,qqUser> onlineIDs;
  extern std::mutex mutex;
  extern std::mutex mutex_rb;
namespace std {
    template<>
// 声明哈希函数的特化
    struct hash<qqUser> {
        size_t operator()(const qqUser& user) const {
            return qqUser::customHash(user);
        }
    };
}
extern  std::shared_ptr<std::string> generateRandomAccount();//12ge sui ji zifu
extern QByteArray intToBytes(qint32 value);
#endif // GLOBAL_H
