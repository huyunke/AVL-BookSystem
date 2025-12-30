#include "include/Book.h"
#include <iostream>
using namespace std;

Book::Book(string id, string name, string author, string borrowerId, bool status) {
    this->id = id;
    this->name = name;
    this->author = author;
    this->borrowerId = borrowerId;
    this->status = status;
}

Book::~Book() {
    delete this;
}

string Book::getId() const{
    return id;
}

string Book::getName() const{
    return name;
}

string Book::getAuthor() const{
    return author;
}

string Book::getBorrowerId() const{
    return borrowerId;
}

bool Book::getStatus() const{
    return status;
}

void Book::printBookInfo(bool isAdmin) {
    cout<<"书名: "<<name<<endl;
    cout<<"作者: "<<author<<endl;
    cout<<"id: "<<id<<endl;
    if (status) {
        cout<<"状态: 可借"<<endl;
    } else {
        cout<<"状态: 已借出"<<endl;
    }
    if (isAdmin) {
        cout<<"借阅者id: "<<borrowerId<<endl;
    }
}

void Book::setBookStatus(bool status) {
    this->status = status;
}

void Book::setBorrowerId(string userId) {
    this->borrowerId = userId;
}

void Book::setBookName(string name) {
    this->name = name;
}

void Book::setAuthor(string author) {
    this->author = author;
}

bool Book::operator>(const Book &book) const {
    return id>book.id;
}

bool Book::operator<(const Book &book) const {
    return id<book.id;
}

bool Book::operator==(const Book &book) const {
    return id==book.id;
}
