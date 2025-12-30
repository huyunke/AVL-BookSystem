#include "include/BookBorrowInfo.h"
#include <iostream>

BookBorrowInfo::BookBorrowInfo(string bookId)  {
    this->bookId = bookId;
    //设置借阅时间
    auto now = chrono::system_clock::now();
    borrowTime = chrono::system_clock::to_time_t(now);
    returnTime = borrowTime + (MAX_BORROW_DAYS * 24 * 60 * 60);
    this->borrowTime = borrowTime;
    this->returnTime = returnTime;
}

BookBorrowInfo::~BookBorrowInfo() {
    delete this;
}

string BookBorrowInfo::getBookId() {
    return bookId;
}

time_t BookBorrowInfo::getBorrowTime() {
    return borrowTime;
}

time_t BookBorrowInfo::getReturnTime() {
    return returnTime;
}

bool BookBorrowInfo::isOverdue() {
    auto now = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(now);
    return currentTime > returnTime;
}

int BookBorrowInfo::getOverdueDays()const {
    auto now = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(now);
    return (currentTime - returnTime) / (24 * 60 * 60);
}

int BookBorrowInfo::getRemainDays()const {
    auto now = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(now);
    return (returnTime - currentTime) / (24 * 60 * 60);
}

void BookBorrowInfo::printBookBorrowInfo() {
    cout<<"书本id: "<<bookId<<endl;
    cout<<"借阅时间: "<<borrowTime<<endl;
    if (isOverdue()) {
        cout<<"已逾期"<<getOverdueDays()<<"天"<<endl;
        cout<<"请尽快归还"<<endl;
        return ;
    }
    cout<<"最迟归还时间: "<<returnTime<<endl;
    cout<<"距离归还时间还有"<<getRemainDays()<<"天"<<endl;
}
