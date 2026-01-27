#ifndef AVL_BOOKSYSTEM_USERDAO_H
#define AVL_BOOKSYSTEM_USERDAO_H
#include "../DatabaseOperator.h"
#include "../../User.h"
#include <string>

class UserDAO {
    DatabaseOperator* userDatabase;
public:
    explicit UserDAO(DatabaseOperator* userDatabase);
    ~UserDAO();
    bool addUser(const User& user);//添加用户
    bool deleteUser(const string& userId);//删除用户

    bool updateUserPassword(const string& userId, const string& newPassword);//更新用户密码
    bool updateUserInfo(const User& user);//更新用户信息

    bool searchUserById(const string& userId, User& user);//根据用户id查询用户信息

    bool exists(const string& userId);//判断用户是否存在，用于登录和注册校验
    bool verifyUser(const string& userId, const string& password);//验证用户登录

    //vector<User> getAllUsers();//获取所有用户信息，用于管理员查询所有用户
};


#endif //AVL_BOOKSYSTEM_USERDAO_H