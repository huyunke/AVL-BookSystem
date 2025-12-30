#include "Print.h"
#include <iostream>
using namespace std;

void Print::printUserMenu() {
    cout<<"请选择操作："<<endl;
    cout<<"1. 查询图书"<<endl;
    cout<<"2. 借阅图书"<<endl;
    cout<<"3. 归还图书"<<endl;
    cout<<"4. 修改密码"<<endl;
    cout<<"5. 退出"<<endl;
    cout<<"返回请输入0"<<endl;
    cout<<"请输入你的选择：";
}

void Print::printAdminMenu() {
    cout<<"1. 添加图书"<<endl;
    cout<<"2. 删除图书"<<endl;
    cout<<"3. 修改图书"<<endl;
    cout<<"4. 查询图书"<<endl;
    cout<<"5. 退出"<<endl;
    cout<<"返回请输入0"<<endl;
    cout<<"请输入你的选择：";
}

void Print::printWelcome() {
    cout<<"================================"<<endl;
    cout<<"欢迎来到图书馆管理系统"<<endl;
    cout<<"用户ID是您的学号，初始密码是学号后六位"<<endl;
    cout<<"================================"<<endl;
}