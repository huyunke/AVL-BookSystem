#include "BookCopy.h"
#include <string>

BookCopy::BookCopy(string bookId, string copyId, string status) {
    this->bookId = bookId;
    this->copyId = copyId;
    this->status = status;
}

BookCopy::BookCopy() {}

BookCopy::~BookCopy() {}

//获取图书id
string BookCopy::getBookId()const {
    return bookId;
}

//获取实体书id
string BookCopy::getCopyId()const {
    return copyId;
}

//获取图书状态
string BookCopy::getStatus()const {
    return status;
}

//设置图书id
void BookCopy::setBookId(string bookId) {
    this->bookId = bookId;
}

//设置实体书id
void BookCopy::setCopyId(string copyId) {
    this->copyId = copyId;
}

//设置图书状态
void BookCopy::setStatus(string status) {
    this->status = status;
}
