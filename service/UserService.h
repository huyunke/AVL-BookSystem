#ifndef AVL_BOOKSYSTEM_USERSERVICE_H
#define AVL_BOOKSYSTEM_USERSERVICE_H
#include "../database/dao/UserDAO.h"

//用于管理用户，包括用户注册、登录、修改密码等操作
class UserService {
    UserDAO* db;
public:
    UserService(UserDAO* db);
    ~UserService();

    //核心操作
    [[nodiscard]] bool registerUser(const User& user) const;//用户注册
    [[nodiscard]] bool loginUser(const string& userId, const string& password) const;//用户登录
    [[nodiscard]] bool changePassword(const string& userId, const string& oldPassword, const string& newPassword) const;//修改密码
    [[nodiscard]] bool deleteUser(const string& userId) const;//删除用户

    //查询
    bool getUserById(const string& userId, User& user) const;//根据用户ID获取用户信息

    //校验
    //[[nodiscard]] bool isUserBlacklisted(const string& userId) const;//用户是否被拉黑
    [[nodiscard]] bool isUserExist(const string& userId) const;//用户是否存在
    [[nodiscard]] bool verifyUser(const string& userId, const string& password) const;//验证用户登录
    [[nodiscard]] bool verifyOldPassword(const string& userId, const string& oldPassword) const;//验证旧密码
};


#endif //AVL_BOOKSYSTEM_USERSERVICE_H