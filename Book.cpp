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

void Book::printBookInfo() {
    cout<<"书名: "<<name<<endl;
    cout<<"作者: "<<author<<endl;
    //cout<<"借阅者: "<<endl;
}

void Book::setBookStatus(bool status) {
    this->status = status;
}

void Book::setBorrower(string userId) {
    this->borrowerId = userId;
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
