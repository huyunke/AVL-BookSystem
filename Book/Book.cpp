#include "Book.h"
#include <iostream>
using namespace std;

Book::Book(string id, string name, string author,string category, string borrowerId, bool status) {
    this->id = id;
    this->name = name;
    this->author = author;
    this->category = category;
    this->borrowerId = borrowerId;
    this->status = status;
}

Book::Book() {
    this->id = "";
    this->name = "";
    this->author = "";
    this->category = "";
    this->borrowerId = "";
    this->status = true;
}

Book::~Book() {}

//获取图书id
string Book::getId() const{
    return id;
}

//获取图书名称
string Book::getName() const{
    return name;
}

//获取图书状态
bool Book::getStatus() const{
    return status;
}

//获取借阅者id
string Book::getBorrowerId() const{
    return borrowerId;
}

//获取图书作者
string Book::getAuthor() const{
    return author;
}

//获取图书分类
string Book::getCategory() const{
    return category;
}

//获取图书出版社
string Book::getPublisher() const{
    return publisher;
}

//设置图书状态
void Book::setBookStatus(bool status) {
    this->status = status;
}

//设置借阅者id
void Book::setBorrowerId(string userId) {
    this->borrowerId = userId;
}

//设置图书名称
void Book::setBookName(string name) {
    this->name = name;
}

//设置图书作者
void Book::setAuthor(string author) {
    this->author = author;
}

//设置图书分类
void Book::setCategory(string category) {
    this->category = category;
}

//设置图书出版社
void Book::setPublisher(string publisher) {
    this->publisher = publisher;
}

void Book::setBookId(string id) {
    this->id = id;
}

//打印图书信息
void Book::printBookInfo(bool isAdmin) {
    cout<<"书名: "<<name<<endl;
    cout<<"作者: "<<author<<endl;
    cout<<"id: "<<id<<endl;
    cout<<"分类: "<<category<<endl;
    cout<<"出版社: "<<publisher<<endl;
    if (status) {
        cout<<"状态: 可借"<<endl;
    } else {
        cout<<"状态: 已借出"<<endl;
        //管理员可以查看借阅者id
        if (isAdmin) {
            cout<<"借阅者id: "<<borrowerId<<endl;
        }
    }
}

//重载比较运算符, 用于AVL树排序
bool Book::operator>(const Book &book) const {
    return id>book.id;
}

bool Book::operator<(const Book &book) const {
    return id<book.id;
}

bool Book::operator==(const Book &book) const {
    return id==book.id;
}
