#ifndef AVL_BOOKSYSTEM_ROUTER_H
#define AVL_BOOKSYSTEM_ROUTER_H

#include "../utils/httplib.h"
#include "AuthController.h"
#include <memory>

using namespace std;

//路由管理器 - 负责注册和管理所有HTTP路由
class Router {
    httplib::Server* server;

    unique_ptr<AuthController> authController;

    void registerAuthRoutes() const;//注册认证相关路由
    void registerMiddleware() const;//注册中间件
    
    // CORS中间件
    void setupCORS() const;

public:
    explicit Router(httplib::Server* server);
    ~Router();

    // 初始化所有路由
    void initializeRoutes(UserService* userService);

    // 设置静态文件目录
    void setStaticFileDirectory(const string& dir);
};

#endif //AVL_BOOKSYSTEM_ROUTER_H

