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

    //核心操作
    [[nodiscard]] bool addUser(const User& user) const;//添加用户
    [[nodiscard]] bool deleteUser(const string& userId) const;//删除用户

    [[nodiscard]] bool updateUserPassword(const string& userId, const string& newPassword) const;//更新用户密码
    [[nodiscard]] bool updateUserBorrowInfo(const string& userId,bool flag) const;//更新用户借阅信息
    [[nodiscard]] bool updateUserName(const string& userId, const string& newName) const;//更新用户名

    bool searchUserById(const string& userId, User& user) const;//根据用户id查询用户信息

    [[nodiscard]] bool exists(const string& userId) const;//判断用户是否存在，用于登录和注册校验
    [[nodiscard]] bool verifyUser(const string& userId, const string& password) const;//验证用户登录

    //vector<User> getAllUsers();//获取所有用户信息，用于管理员查询所有用户
};


#endif //AVL_BOOKSYSTEM_USERDAO_H