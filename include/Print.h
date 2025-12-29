#ifndef AVL_BOOKSYSTEM_UIPRINT_H
#define AVL_BOOKSYSTEM_UIPRINT_H

//分装UI打印的函数
class Print {
public:
    static void printUserMenu();//打印普通用户的菜单
    static void printAdminMenu();//打印管理员的菜单
    static void printWelcome();//打印欢迎菜单
    // static void printErrorInfo();
};

#endif //AVL_BOOKSYSTEM_UIPRINT_H