#include "User.h"
#include<string>
#include "BookBorrowInfo.h"
#include <iostream>
#include "AVLTree.h"
using namespace std;

User::User(string id,string name, string password,string type) {
    this->id = id;
    this->name = name;
    this->password = password;
    this->type = type;
}

User::~User() {}

string User::getId() {
    return id;
}

string User::getName() {
    return name;
}

string User::getPassword() {
    return password;
}

string User::getType() {
    return type;
}

void User::addBorrowInfo(string bookId) {
    BookBorrowInfo info(bookId);
    borrowInfo.push_back(info);
    cout<<"=================================="<<endl;
    cout<<"借阅书本成功"<<endl;
    cout<<"请在 "<<info.getFormattedReturnTime()<<" 前归还"<<endl;
    cout<<"逾期将被罚款"<<endl;
    cout<<"=================================="<<endl;
}

void User::addBorrowInfoSilent(string bookId) {
    BookBorrowInfo info(bookId);
    borrowInfo.push_back(info);
}

//归还图书操作
bool User::removeBorrowInfo(string bookId) {
    for (auto it = borrowInfo.begin(); it != borrowInfo.end(); ++it) {
        if (it->getBookId() == bookId) {
            borrowInfo.erase(it);
            cout<<"归还书本成功"<<endl;
            return true;
        }
    }
    return false;
}

//施工中
void User::addBook(Book &book,AVLTree* tree) {
    AVLNode* targetBook=tree->search(book.getId());
    if (targetBook!=nullptr) {
        cout<<"图书已存在"<<endl;
        cout<<"请检查书本id是否正确"<<endl;
        return;
    }
    tree->insert(book);
}

void User::printBorrowInfo() {
    if (borrowInfo.size()==0) {
        cout<<"您未借阅任何图书"<<endl;
        return;
    }
    for (auto it = borrowInfo.begin(); it != borrowInfo.end(); ++it) {
        cout<<"=================================="<<endl;
        it->printBookBorrowInfo();
    }
    cout<<"=================================="<<endl;
}

vector<BookBorrowInfo> User::getBorrowBookInfo() {
    return borrowInfo;
}

string User::getBorrowBookId() {
    string borrowBookIds;
    for (auto it = borrowInfo.begin(); it != borrowInfo.end(); ++it) {
        borrowBookIds+=" "+it->getBookId();
    }
    return borrowBookIds;
}