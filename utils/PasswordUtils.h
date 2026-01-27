#ifndef AVL_BOOKSYSTEM_PASSWORDUTILS_H
#define AVL_BOOKSYSTEM_PASSWORDUTILS_H

#include <string>

using namespace std;

class PasswordUtils {
public:
    static string generateSalt();
    static string hashPassword(const string& password, const string& salt);//计算哈希值
    static string encryptPassword(const string& password);//加密密码
    static bool verifyPassword(const string& password, const string& encryptedPassword);

private:
    static const int SALT_SIZE = 16; // 盐值大小（字节）
};

#endif //AVL_BOOKSYSTEM_PASSWORDUTILS_H