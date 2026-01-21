#include "Print.h"
#include <iostream>
using namespace std;

//打印普通用户菜单
void Print::printUserMenu() {
    cout<<"=================================="<<endl;
    cout<<"请选择操作："<<endl;
    cout<<"1. 查询图书"<<endl;
    cout<<"2. 借阅图书"<<endl;
    cout<<"3. 归还图书"<<endl;
    cout<<"4. 查看借阅信息"<<endl;
    cout<<"5. 修改密码"<<endl;
    cout<<"6. 退出"<<endl;
    cout<<"请输入你的选择：";
}

//打印管理员菜单
void Print::printAdminMenu() {
    cout<<"1. 添加图书"<<endl;
    cout<<"2. 删除图书"<<endl;
    cout<<"3. 修改图书"<<endl;
    cout<<"4. 查询图书"<<endl;
    cout<<"5. 修改密码"<<endl;
    cout<<"6. 退出"<<endl;
    cout<<"请输入你的选择：";
}

//打印欢迎菜单
void Print::printWelcome() {
    cout<<"================================"<<endl;
    cout<<"欢迎来到图书馆管理系统"<<endl;
    cout<<"用户id是您的学号，初始密码是123456"<<endl;
    cout<<"================================"<<endl;
}