#ifndef GLOBAL_H
#define GLOBAL_H
#include<QTcpSocket>
#include"sql.h"
#include"qquser.h"
#include<QList>
#include<unordered_map>
#include<memory>
#include<string>
extern sql db;
extern std::unordered_map<qqUser, QTcpSocket*> onlineUsers;
extern std::unordered_map<int,qqUser> onlineIDs;
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

#endif // GLOBAL_H
