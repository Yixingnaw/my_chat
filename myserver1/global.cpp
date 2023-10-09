#include "global.h"
#include"sql.h"
#include <unordered_map>
#include"qquser.h"
std::unordered_map<qqUser, QTcpSocket*> onlineUsers;
sql db;
char* generateRandomAccount() {
    // 设置随机种子
    srand(time(NULL));

    char* account;

        // 生成一个 6 位随机数作为用户帐号
        account = (char*)malloc(11); // 包括字符串结束符 '\0'
        for (int i = 0; i < 12; i++) {
            account[i] = '0' + (rand() % 10); // 生成 '0' 到 '9' 之间的随机字符
        }
        account[10] = '\0'; // 添加字符串结束符

    return account;
}
