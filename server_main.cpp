#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#endif

#include <iostream>
#include "utils/httplib.h"
#include "database/DatabaseOperator.h"
#include "database/DatabaseInitializer.h"
#include "database/dao/UserDAO.h"
#include "service/UserService.h"
#include "controller/Router.h"

using namespace std;

int main() {
    #ifdef _WIN32
    // 设置控制台代码页为UTF-8
    system("chcp 65001 > nul");
    #endif

    cout << "========================================" << endl;
    cout << "    图书管理系统 - HTTP服务器启动      " << endl;
    cout << "========================================" << endl;
    cout << endl;

    // 1. 初始化数据库
    string dbPath = "D:/CLion/AVL-BookSystem/library.db";
    DatabaseOperator* db = new DatabaseOperator();
    
    cout << "正在连接数据库..." << endl;
    if (!db->open(dbPath)) {
        cerr << "✗ 数据库连接失败: " << db->getLastError() << endl;
        delete db;
        return 1;
    }
    cout << "✓ 数据库连接成功" << endl;
    
    // 确保数据库表已创建
    cout << "正在检查数据库表..." << endl;
    DatabaseInitializer::initializeDatabase(db);
    cout << endl;

    // 2. 初始化DAO和Service层
    UserDAO* userDAO = new UserDAO(db);
    UserService* userService = new UserService(userDAO);
    cout << "✓ Service层初始化完成" << endl;
    cout << endl;

    // 3. 创建HTTP服务器
    httplib::Server server;
    
    // 4. 初始化路由
    Router router(&server);
    router.initializeRoutes(userService);

    // 设置静态文件目录（提供HTML页面）
    router.setStaticFileDirectory("D:/CLion/AVL-BookSystem/public");
    cout << endl;

    // 5. 设置服务器参数
    const char* host = "0.0.0.0";
    int port = 8080;
    
    cout << "========================================" << endl;
    cout << "服务器配置信息:" << endl;
    cout << "  地址: http://" << host << ":" << port << endl;
    cout << "  本地访问: http://localhost:" << port << endl;
    cout << "  数据库: " << dbPath << endl;
    cout << "========================================" << endl;
    cout << endl;
    
    cout << "可用的API端点:" << endl;
    cout << "  POST   /api/auth/register        - 用户注册" << endl;
    cout << "  POST   /api/auth/login           - 用户登录" << endl;
    cout << "  POST   /api/auth/logout          - 用户登出" << endl;
    cout << endl;

    cout << "可用的页面:" << endl;
    cout << "  http://localhost:" << port << "/login.html - 登录页面" << endl;
    cout << endl;

    cout << "========================================" << endl;
    cout << "服务器正在启动..." << endl;
    cout << "按 Ctrl+C 停止服务器" << endl;
    cout << "========================================" << endl;
    cout << endl;

    // 6. 启动服务器
    if (!server.listen(host, port)) {
        cerr << "✗ 服务器启动失败，端口 " << port << " 可能已被占用" << endl;
        delete userService;
        delete userDAO;
        delete db;
        return 1;
    }

    // 7. 清理资源（服务器停止后）
    cout << endl;
    cout << "服务器已停止" << endl;
    delete userService;
    delete userDAO;
    delete db;

    return 0;
}

