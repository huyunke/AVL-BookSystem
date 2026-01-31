#include "AuthController.h"
#include <iostream>

AuthController::AuthController(UserService* userService) : userService(userService) {}

AuthController::~AuthController() = default;

// 解析JSON请求体
json AuthController::parseRequestBody(const httplib::Request& req) {
    try {
        return json::parse(req.body);
    } catch (const json::parse_error& e) {
        return json::object();
    }
}

// 验证必填字段
bool AuthController::validateRequiredFields(const json& data, const vector<string>& fields, string& errorMsg) {
    for (const auto& field : fields) {
        if (!data.contains(field) || data[field].is_null() ||
            (data[field].is_string() && data[field].get<string>().empty())) {
            errorMsg = "缺少必填字段: " + field;
            return false;
        }
    }
    return true;
}

// 生成成功响应
httplib::Response AuthController::createSuccessResponse(const json& data, int statusCode) {
    httplib::Response res;
    res.status = statusCode;
    res.set_content(data.dump(), "application/json; charset=utf-8");
    return res;
}

// 生成错误响应
httplib::Response AuthController::createErrorResponse(const string& message, int statusCode) {
    httplib::Response res;
    res.status = statusCode;
    json errorJson = {
        {"success", false},
        {"message", message}
    };
    res.set_content(errorJson.dump(), "application/json; charset=utf-8");
    return res;
}

// POST /api/auth/register - 用户注册
void AuthController::handleRegister(const httplib::Request& req, httplib::Response& res) const {
    json requestData = parseRequestBody(req);

    // 验证必填字段
    string errorMsg;
    if (!validateRequiredFields(requestData, {"userId", "name", "password"}, errorMsg)) {
        res = createErrorResponse(errorMsg, 400);
        return;
    }

    string userId = requestData["userId"];
    string name = requestData["name"];
    string password = requestData["password"];
    // 普通用户注册时强制设置为 student，不允许用户自己选择角色
    string role = "student";

    // 验证用户ID格式（必须为12个字符）
    if (userId.length() != 12) {
        res = createErrorResponse("用户ID长度必须为12个字符", 400);
        return;
    }

    // 验证密码强度
    if (password.length() < 6) {
        res = createErrorResponse("密码长度至少为6个字符", 400);
        return;
    }

    // 检查用户是否已存在
    if (userService->isUserExist(userId)) {
        res = createErrorResponse("用户已存在", 409);
        return;
    }

    // 创建用户对象（User构造函数会自动加密密码）
    User newUser(userId, name, password, role);

    // 注册用户
    if (userService->registerUser(newUser)) {
        json responseData = {
            {"success", true},
            {"message", "注册成功"},
            {"data", {
                {"userId", userId},
                {"name", name},
                {"role", role}
            }}
        };
        res = createSuccessResponse(responseData, 201);
    } else {
        res = createErrorResponse("注册失败，请稍后重试", 500);
    }
}

// POST /api/auth/login - 用户登录
void AuthController::handleLogin(const httplib::Request& req, httplib::Response& res) const {
    json requestData = parseRequestBody(req);

    // 验证必填字段
    string errorMsg;
    if (!validateRequiredFields(requestData, {"userId", "password"}, errorMsg)) {
        cout << "登录失败: 缺少必填字段 - " << errorMsg << endl;
        res = createErrorResponse(errorMsg, 400);
        return;
    }

    string userId = requestData["userId"];
    string password = requestData["password"];

    cout << "尝试登录 - 用户ID: " << userId << endl;

    // 检查用户是否存在
    if (!userService->isUserExist(userId)) {
        cout << "登录失败: 用户不存在 - " << userId << endl;
        res = createErrorResponse("用户不存在", 401);
        return;
    }

    cout << "用户存在，开始验证密码..." << endl;

    // 验证用户登录
    if (userService->loginUser(userId, password)) {
        cout << "密码验证成功" << endl;
        // 获取用户信息
        User user;
        if (userService->getUserById(userId, user)) {
            cout << "获取用户信息成功 - 角色: " << user.getType() << endl;
            json responseData = {
                {"success", true},
                {"message", "登录成功"},
                {"data", {
                    {"userId", user.getId()},
                    {"name", user.getName()},
                    {"role", user.getType()}
                }}
            };
            res = createSuccessResponse(responseData, 200);
        } else {
            cout << "登录失败: 获取用户信息失败" << endl;
            res = createErrorResponse("获取用户信息失败", 500);
        }
    } else {
        cout << "登录失败: 密码错误" << endl;
        res = createErrorResponse("用户ID或密码错误", 401);
    }
}

// POST /api/auth/logout - 用户登出
void AuthController::handleLogout(const httplib::Request& req, httplib::Response& res) {
    json responseData = {
        {"success", true},
        {"message", "登出成功"}
    };
    res = createSuccessResponse(responseData, 200);
}