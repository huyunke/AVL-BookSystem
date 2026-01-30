#include "User.h"
#include<string>
#include "../utils/PasswordUtils.h"
using namespace std;

User::User(string id,string name, string password,string type) {
    this->id = id;
    this->name = name;
    password=PasswordUtils::encryptPassword(password);
    this->password = password;
    this->type = type;
}

User::User() {
    this->id = "";
    this->name = "";
    this->password = "";
    this->type = "";
}

User::~User() {}

//获取用户id
const string User::getId() const{
    return id;
}

//获取用户名
const string User::getName() const{
    return name;
}

//获取用户密码
const string User::getPassword() const{
    return password;
}

//获取用户类型
const string User::getType() const{
    return type;
}

// //获取借阅图书信息
// vector<BookBorrowInfo> User::getBorrowBookInfo() const{
//     return borrowInfo;
// }
//
// //获取借阅图书数据（包含时间信息）
// const string User::getBorrowBookDataWithTime() {
//     string borrowBookData;
//     for (auto it = borrowInfo.begin(); it != borrowInfo.end(); ++it) {
//         borrowBookData += " " + it->getBookId() + ":" +
//                          to_string(it->getBorrowTime()) + ":" +
//                          to_string(it->getReturnTime());
//     }
//     return borrowBookData;
// }
//
// int User::getBorrowedBookCount() const{
//     return borrowedBookCount;
// }

void User::setId(string id) {
    this->id = id;
}

void User::setName(string name) {
    this->name = name;
}

//设置用户密码
void User::setPassword(string password) {
    password=PasswordUtils::encryptPassword(password);
    this->password = password;
}

// void User::setBorrowedBookCount(int borrowedBookCount) {
//     this->borrowedBookCount = borrowedBookCount;
// }
//
// //添加借阅信息
// void User::addBorrowInfo(string bookId) {
//     BookBorrowInfo info(bookId);
//     borrowInfo.push_back(info);
//     cout<<"=================================="<<endl;
//     cout<<"借阅书本成功"<<endl;
//     cout<<"请在 "<<info.getFormattedReturnTime()<<" 前归还"<<endl;
//     cout<<"逾期将被罚款"<<endl;
//     cout<<"=================================="<<endl;
// }
//
// //添加借阅信息（带时间参数，用于从文件读取）
// void User::addBorrowInfoWithTime(string bookId, time_t borrowTime, time_t returnTime) {
//     BookBorrowInfo info(bookId, borrowTime, returnTime);
//     borrowInfo.push_back(info);
// }
//
// //移除借阅信息
// bool User::removeBorrowInfo(string bookId) {
//     for (auto it = borrowInfo.begin(); it != borrowInfo.end(); ++it) {
//         if (it->getBookId() == bookId) {
//             borrowInfo.erase(it);
//             cout<<"归还书本成功"<<endl;
//             return true;
//         }
//     }
//     return false;
// }
//
// //更新借阅信息中的图书id（保留借阅时间）
// bool User::updateBorrowBookId(string oldBookId, string newBookId) {
//     for (auto it = borrowInfo.begin(); it != borrowInfo.end(); ++it) {
//         if (it->getBookId() == oldBookId) {
//             it->setBookId(newBookId);
//             return true;
//         }
//     }
//     return false;
// }
//
// //打印借阅信息
// void User::printBorrowInfo() {
//     if (borrowInfo.size()==0) {
//         cout<<"您未借阅任何图书"<<endl;
//         return;
//     }
//     for (auto it = borrowInfo.begin(); it != borrowInfo.end(); ++it) {
//         cout<<"=================================="<<endl;
//         it->printBookBorrowInfo();
//     }
//     cout<<"=================================="<<endl;
// }