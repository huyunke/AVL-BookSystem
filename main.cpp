#include <iostream>
#include <fstream>
#include "Print.h"
#include "AVLTree.h"
#include "Book.h"
#include "BookBorrowInfo.h"
#include "User.h"
#include "FileOperator.h"
#ifdef _WIN32
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef max
#undef min
#endif
using namespace std;

int main() {
    #ifdef _WIN32
    // 设置控制台代码页为 UTF-8
    system("chcp 65001 > nul");
    #endif

    //读取图书信息
    AVLTree* tree=new AVLTree();
    if (!FileOperator::readBookFile("book.txt",tree)) {
        cout<<"读取图书文件失败"<<endl;
        return 0;
    }
    //读取用户信息
    unordered_map<string,User*> userMap;
    if (!FileOperator::readUserFile("user.txt",userMap)) {
        cout<<"读取用户文件失败"<<endl;
        return 0;
    }

    //登录
    Print::printWelcome();
    cout<<"请输入您的id：";
    string id;
    cin>>id;
    while(userMap.find(id)==userMap.end()) {
        cout<<"用户不存在"<<endl;
        cout<<"请检查id是否正确并重新输入："<<endl;
        cin>>id;
    }
    cout<<"请输入密码：";
    string password;
    cin>>password;
    while (userMap[id]->getPassword()!=password) {
        cout<<"密码错误"<<endl;
        cout<<"请重新输入密码："<<endl;
        cin>>password;
    }
    cout<<"登录成功！"<<endl;
    cout<<"=================================="<<endl;
    User *user=userMap[id];

    //根据用户类型进入不同的界面
    if (user->getType()=="reader") {
        //用户

        //登录成功后，如果该用户有书本逾期，提醒用户书本逾期
        vector<BookBorrowInfo> BookBorrowInfos=user->getBorrowBookInfo();
        for (auto it = BookBorrowInfos.begin(); it != BookBorrowInfos.end(); ++it) {
            if (it->isOverdue()) {
                cout<<"您的书本"<<it->getBookId()<<"已逾期"<<it->getOverdueDays()<<"天"<<endl;
                cout<<"请尽快归还"<<endl;
            }
        }

        Print::printUserMenu();
        int choice;
        cin>>choice;
        while (choice!=5) {
            switch (choice) {
                //查询图书
                //根据id查找到书本，并输出书本信息（包括是否被借阅）
                case 1: {
                    cout<<"请输入要查询的图书id：";
                    string bookId;
                    while (cin>>bookId) {
                        if (bookId=="0") break;
                        AVLNode* targetNode=tree->search(bookId);
                        if (!targetNode) {
                            cout<<"图书不存在"<<endl;
                            cout<<"请检查书本id是否正确"<<endl;
                            cout<<"请输入要查询的图书id：";
                            continue;
                        }
                        targetNode->book.printBookInfo(false);
                        cout<<"请输入要查询的图书id：";
                    }
                    break;
                }

                //借阅图书
                //借阅图书：如果id正确将书本信息添加到用户的借阅信息中
                //根据id查找到书本，并更改图书的状态
                //如果id不正确输出提示信息
                case 2: {
                    cout<<"请输入要借阅的图书id：";
                    string bookId;
                    while (cin>>bookId) {
                        if (bookId=="0") break;
                        AVLNode* targetNode=tree->search(bookId);
                        if (!targetNode) {
                            cout<<"图书不存在"<<endl;
                            cout<<"请检查书本id是否正确"<<endl;
                            cout<<"请输入要借阅的图书id：";
                            continue;
                        }
                        if (!targetNode->book.getStatus()) {
                            cout<<"图书已借出"<<endl;
                            cout<<"请重新输入要借阅的图书id：";
                            continue;
                        }
                        user->addBorrowInfo(bookId);
                        targetNode->book.setBookStatus(false);
                        targetNode->book.setBorrowerId(user->getId());
                        cout<<"请输入要借阅的图书id：";
                    }
                    break;

                }

                //归还图书：如果id正确将书本信息从用户的借阅信息中删除
                //根据id查找到书本，并更改图书的状态
                //如果id不正确输出提示信息
                case 3: {
                    cout<<"请输入要归还的图书id：";
                    string bookId;
                    while (cin>>bookId) {
                        if (bookId=="0") break;
                        if (!user->removeBorrowInfo(bookId)) {
                            cout<<"您未借阅该图书"<<endl;
                            cout<<"请检查书本id是否正确"<<endl;
                            cout<<"请输入要归还的图书id：";
                            continue;
                        }
                        AVLNode* targetNode=tree->search(bookId);
                        targetNode->book.setBookStatus(true);
                        targetNode->book.setBorrowerId("");
                        cout<<"请输入要归还的图书id：";
                    }
                    break;
                }
                //修改密码:修改用户的密码(不知道做不做)
                case 4:
                    break;
                //退出
                default:
                    break;
            }
            Print::printUserMenu();
            cin>>choice;
        }
    } else {
        Print::printAdminMenu();
        int choice;
        cin>>choice;
        while (choice!=5) {
            switch (choice) {
                //添加图书
                case 1: {
                    cout<<"请输入要添加的图书id：";
                    string bookId;
                    while (cin>>bookId) {
                        if (bookId=="0") break;
                        if (tree->search(bookId)) {
                            cout<<"图书已存在"<<endl;
                            cout<<"请检查书本id是否正确"<<endl;
                            cout<<"请输入要添加的图书id：";
                            break;
                        }
                        cout<<"请输入要添加的图书名称：";
                        string bookName;
                        cin>>bookName;
                        cout<<"请输入要添加的图书作者：";
                        string bookAuthor;
                        cin>>bookAuthor;
                        Book book(bookId,bookName,bookAuthor,"",true);
                        tree->insert(book);
                    }
                    break;
                }

                //删除图书
                case 2: {
                    cout<<"请输入要删除的图书id：";
                    string bookId;
                    while (cin>>bookId) {
                        if (bookId=="0") break;
                        if (!tree->search(bookId)) {
                            cout<<"图书不存在"<<endl;
                            cout<<"请检查书本id是否正确"<<endl;
                            cout<<"请输入要删除的图书id：";
                            continue;
                        }
                        tree->remove(bookId);
                        cout<<"请输入要删除的图书id：";
                    }
                    break;
                }

                //修改图书
                case 3: {
                    cout<<"请输入要修改的图书id：";
                    string bookId;
                    while (cin>>bookId) {
                        if (bookId=="0") break;
                        AVLNode* targetNode=tree->search(bookId);
                        if (!targetNode) {
                            cout<<"图书不存在"<<endl;
                            cout<<"请检查书本id是否正确"<<endl;
                            cout<<"请输入要修改的图书id：";
                            continue;
                        }
                        cout<<"不需要修改的字段请输入0"<<endl;
                        cout<<"请输入要修改的图书名称：";//不修改就输入0
                        string bookName;
                        cin>>bookName;
                        cout<<"请输入要修改的图书作者：";//不修改就输入0
                        string author;
                        cin>>author;
                        if (bookName!="0") {
                            targetNode->book.setBookName(bookName);
                        }
                        if (author!="0") {
                            targetNode->book.setAuthor(author);
                        }
                        //图书id修改不知道加不加，大致流程如下
                        //1.删除原图书
                        //2.根据新信息生成图书
                        //3.插入新图书
                        //4.根据借阅者的借阅信息修改借阅信息，需要把其中的图书id修改为新图书id
                        cout<<"请输入要修改的图书id：";
                    }
                    break;
                }

                //查询图书
                case 4: {
                    cout<<"请输入要查询的图书id：";
                    string bookId;
                    while (cin>>bookId) {
                        if (bookId=="0") break;
                        AVLNode* targetNode=tree->search(bookId);
                        if (!targetNode) {
                            cout<<"图书不存在"<<endl;
                            cout<<"请检查书本id是否正确"<<endl;
                            cout<<"请输入要查询的图书id：";
                            continue;
                        }
                        targetNode->book.printBookInfo(true);
                        cout<<"请输入要查询的图书id：";
                    }
                    break;
                }
                default:
                    break;
            }
            Print::printAdminMenu();
            cin>>choice;
        }
    }

    //更新数据
    FileOperator::writeBookFile("book.txt",tree);
    FileOperator::writeUserFile("user.txt",user);
    return 0;
}