#include "Router.h"
#include "../utils/json.hpp"
#include <iostream>

Router::Router(httplib::Server* server) : server(server) {}

Router::~Router() = default;

// 初始化所有路由
void Router::initializeRoutes(UserService* userService) {
    // 创建Controller实例
    authController = make_unique<AuthController>(userService);
    
    // 设置CORS
    setupCORS();
    
    // 注册中间件
    registerMiddleware();
    
    // 注册路由
    registerAuthRoutes();
    
    cout << "✓ 路由初始化完成" << endl;
}

// 注册认证相关路由
void Router::registerAuthRoutes() const {
    // POST /api/auth/register - 用户注册
    server->Post("/api/auth/register", [this](const httplib::Request& req, httplib::Response& res) {
        authController->handleRegister(req, res);
    });
    
    // POST /api/auth/login - 用户登录
    server->Post("/api/auth/login", [this](const httplib::Request& req, httplib::Response& res) {
        authController->handleLogin(req, res);
    });
    
    // POST /api/auth/logout - 用户登出
    server->Post("/api/auth/logout", [this](const httplib::Request& req, httplib::Response& res) {
        authController->handleLogout(req, res);
    });
}

// 注册中间件
void Router::registerMiddleware() const {
    // 请求日志中间件
    server->set_logger([](const httplib::Request& req, const httplib::Response& res) {
        cout << "[" << req.method << "] " << req.path;
        if (!req.body.empty()) {
            cout << " - Body: " << req.body.substr(0, 100); // 只打印前100个字符
        }
        cout << " - Status: " << res.status << endl;
    });
    
    // 错误处理中间件
    server->set_error_handler([](const httplib::Request& req, httplib::Response& res) {
        nlohmann::json errorJson = {
            {"success", false},
            {"message", "请求处理失败"},
            {"status", res.status}
        };
        res.set_content(errorJson.dump(), "application/json; charset=utf-8");
    });
    
    cout << "✓ 中间件注册完成" << endl;
}

// 设置CORS
void Router::setupCORS() const {
    server->set_pre_routing_handler([](const httplib::Request& req, httplib::Response& res) {
        // 设置CORS头
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type, Authorization");
        
        // 处理OPTIONS预检请求
        if (req.method == "OPTIONS") {
            res.status = 200;
            return httplib::Server::HandlerResponse::Handled;
        }
        
        return httplib::Server::HandlerResponse::Unhandled;
    });

    cout << "✓ CORS配置完成" << endl;
}

// 设置静态文件目录
void Router::setStaticFileDirectory(const string& dir) {
    server->set_mount_point("/", dir);
    cout << "✓ 静态文件目录设置为: " << dir << endl;
}
