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
#include <fstream>
#include "Book/Book.h"
#include "User.h"
#include "database/DatabaseInitializer.h"

using namespace std;

int main() {
    #ifdef _WIN32
    //设置控制台代码页为UTF-8
    system("chcp 65001 > nul");
    #endif

    //第一次运行需要初始化数据库

    //文件路径用于
    string bookFilePath;
    string bookCopyFilePath;
    string userFilePath;
    string recordFilePath;

    //登录

    //没有账号进入注册

    //根据用户类型进入不同的界面
    //用户
    if (user->getType()=="reader") {
        //登录成功后，如果该用户有书本逾期，提醒用户书本逾期
        while (choice!=6) {
            switch (choice) {
                //查询图书
                //输出所有图书信息
                case 1: {
                    cout<<"请选择查询类型"<<endl;
                    int queryType;
                    cout<<"1. 查询所有图书"<<endl;
                    cout<<"2. 查询单本图书"<<endl;
                    cout<<"0. 返回"<<endl;
                    cout<<"请输入您的选择：";
                    }
                    break;
                }

                //借阅图书
                //借阅图书：如果id正确将书本信息添加到用户的借阅信息中
                //根据id查找到书本，并更改图书的状态
                //如果id不正确输出提示信息
                //如果书本已借出输出提示信息
                case 2: {

                    }
                    break;
                }

                //归还图书：如果id正确将书本信息从用户的借阅信息中删除
                //根据id查找到书本，并更改图书的状态
                //如果id不正确输出提示信息
                //如果书本未借输出提示信息
                case 3: {

                    }
                    break;
                }

                //查询借阅信息
                case 4: {

                }

                //修改密码:修改用户的密码
                case 5: {

                    break;
                }

                default: {
                    cout<<"指令无效请重新输入";
                    break;
                }
            }
        }
    } else {
        Print::printAdminMenu();
        int choice;
        cin>>choice;
        cout<<"=================================="<<endl;
        while (choice!=6) {
            switch (choice) {
                //添加图书
                //输入图书id，名称，作者，分类，出版社，添加到数据库中
                //如果id已存在输出提示信息
                case 1: {

                    break;
                }

                //删除图书
                //输入图书id，从数据库中删除图书
                //如果id不存在输出提示信息
                //如果书本已借出输出提示信息
                case 2: {

                    break;
                }

                //修改图书
                //输入图书id，修改图书信息，包括名称，作者，分类，出版社
                //如果id不存在输出提示信息
                case 3: {
                        //图书id修改
                        //删除原图书
                        //根据新信息生成图书（需要判断新书本id是否重复）
                        //插入新图书
                        //根据借阅者的借阅信息修改借阅信息，需要把其中的图书id修改为新图书id

                        //如果只修改了名称或作者，直接更新
                        //如果图书已借出，需要更新借阅者的借阅信息

                    break;
                }

                //查询图书
                case 4: {
                    cout<<"请选择查询类型"<<endl;
                    int queryType;
                    cout<<"1. 查询所有图书"<<endl;
                    cout<<"2. 查询单本图书"<<endl;
                    cout<<"0. 返回"<<endl;
                    cout<<"请输入您的选择：";

                    break;
                }
                //修改密码
                case 5: {
                    cout<<"请输入旧密码：";
                    string oldPassword;
                    cin>>oldPassword;
                    if (oldPassword=="0") {
                        break;
                    }
                    while (oldPassword!=user->getPassword()) {
                        cout<<"密码错误"<<endl;
                        cout<<"请重新输入旧密码：";
                        cin>>oldPassword;
                    }
                    cout<<"请输入新密码：";
                    string newPassword;
                    cin>>newPassword;
                    user->setPassword(newPassword);
                    break;
                }
                default: {
                    cout<<"指令无效请重新输入";
                    break;
                }
            }
            Print::printAdminMenu();
            cin>>choice;
            cout<<"=================================="<<endl;
        }
    }

    return 0;
}