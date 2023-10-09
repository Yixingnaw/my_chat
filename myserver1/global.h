#ifndef GLOBAL_H
#define GLOBAL_H
#include<QTcpSocket>
#include"sql.h"
#include"qquser.h"
#include<QList>
#include<unordered_map>
extern sql db;
extern std::unordered_map<qqUser, QTcpSocket*> onlineUsers;
namespace std {
    template<>
// 声明哈希函数的特化
    struct hash<qqUser> {
        size_t operator()(const qqUser& user) const {
            return qqUser::customHash(user);
        }
    };
}
extern  char* generateRandomAccount();//12ge sui ji zifu
#endif // GLOBAL_H
