#include "global.h"
#include"sql.h"
#include <unordered_map>
#include"qquser.h"
#include<string>
#include<memory>
#include<QMutex>
std::unordered_map<qqUser, QTcpSocket*> onlineUsers;
sql db;
std::unordered_map<int,qqUser> onlineIDs;
std::mutex mutex;
std::mutex mutex_rb;
std::shared_ptr<std::string> generateRandomAccount() {
    // 设置随机种子
    srand(time(NULL));
      std::shared_ptr<std::string> string_ptr=std::make_shared<std::string>(std::string(""));
    char* account;
   
        // 生成一个 6 位随机数作为用户帐号
        account = (char*)malloc(11); // 包括字符串结束符 '\0'
        for (int i = 0; i < 10; i++) {
            account[i] = '0' + (rand() % 10); // 生成 '0' 到 '9' 之间的随机字符
        }
        account[10] = '\0'; // 添加字符串结束符
     *string_ptr=account;
        delete  account;
        
    return  string_ptr;
}
QByteArray intToBytes(qint32 value) {
    QByteArray byteArray;
    QDataStream stream(&byteArray, QIODevice::WriteOnly);
    stream << value;
    return byteArray;
}
// 将 QByteArray 转换为 qint32
qint32 bytesToInt(const QByteArray &byteArray) {
    qint32 value = 0;
    QDataStream stream(byteArray);
    stream >> value;
    return value;
}
