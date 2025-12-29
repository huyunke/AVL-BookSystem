#include "include/User.h"
#include<string>
#include "include/BookBorrowInfo.h"
#include <iostream>
using namespace std;

User::User(string id,string name, string password,string type) {
    this->id = id;
    this->name = name;
    this->password = password;
    this->type = type;
}

User::~User() {
    delete this;
}

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

void User::addBorrowInfo(BookBorrowInfo info) {
    borrowInfo.push_back(info);
}

bool User::removeBorrowInfo(string bookId) {
    for (auto it = borrowInfo.begin(); it != borrowInfo.end(); ++it) {
        if (it->getBook().getId() == bookId) {
            borrowInfo.erase(it);
            cout<<"归还书本成功"<<endl;
            return true;
        }
    }
    return false;
}

void User::printBorrowInfo() {
    for (auto it = borrowInfo.begin(); it != borrowInfo.end(); ++it) {
        it->printBookBorrowInfo();
    }
}