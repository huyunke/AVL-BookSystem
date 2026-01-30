#ifndef AVL_BOOKSYSTEM_AUTHCONTROLLER_H
#define AVL_BOOKSYSTEM_AUTHCONTROLLER_H

#include "../utils/httplib.h"
#include "../service/UserService.h"
#include "../utils/PasswordUtils.h"
#include "../utils/json.hpp"
#include <string>

using json = nlohmann::json;
using namespace std;

// 认证控制器 - 处理登录、注册、登出等认证相关操作
class AuthController {
    UserService* userService;

    //辅助方法
    //解析JSON请求体
    static json parseRequestBody(const httplib::Request& req);
    //验证必填字段
    static bool validateRequiredFields(const json& data, const vector<string>& fields, string& errorMsg);
    //生成成功响应
    static httplib::Response createSuccessResponse(const json& data, int statusCode = 200);
    //生成错误响应
    static httplib::Response createErrorResponse(const string& message, int statusCode = 400);

public:
    explicit AuthController(UserService* userService);
    ~AuthController();

    // POST /api/auth/register - 用户注册
    void handleRegister(const httplib::Request& req, httplib::Response& res) const;
    
    // POST /api/auth/login - 用户登录
    void handleLogin(const httplib::Request& req, httplib::Response& res) const;
    
    // POST /api/auth/logout - 用户登出
    static void handleLogout(const httplib::Request& req, httplib::Response& res);
};

#endif //AVL_BOOKSYSTEM_AUTHCONTROLLER_H

