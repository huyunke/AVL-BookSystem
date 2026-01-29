#include "Book.h"
#include <iostream>
using namespace std;

Book::Book(string id, string title, string author,string category,string publisher) {
    this->id = id;
    this->title = title;
    this->author = author;
    this->category = category;
    this->publisher = publisher;
}

Book::Book() {
    this->id = "";
    this->title = "";
    this->author = "";
    this->category = "";
    this->publisher = "";
}

Book::~Book() {}

//获取图书id
string Book::getId() const{
    return id;
}

//获取图书名称
string Book::getTitle() const{
    return title;
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

//设置图书名称
void Book::setBookTitle(string name) {
    this->title = title;
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
    cout<<"书名: "<<title<<endl;
    cout<<"作者: "<<author<<endl;
    cout<<"id: "<<id<<endl;
    cout<<"分类: "<<category<<endl;
    cout<<"出版社: "<<publisher<<endl;
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
