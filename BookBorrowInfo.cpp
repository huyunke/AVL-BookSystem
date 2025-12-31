#include "BookBorrowInfo.h"
#include <iostream>
#include <sstream>
#include <iomanip>

BookBorrowInfo::BookBorrowInfo(string bookId)  {
    this->bookId = bookId;
    //设置借阅时间
    auto now = chrono::system_clock::now();
    borrowTime = chrono::system_clock::to_time_t(now);
    returnTime = borrowTime + (MAX_BORROW_DAYS * 24 * 60 * 60);
    this->borrowTime = borrowTime;
    this->returnTime = returnTime;
}

//带时间参数的构造函数
BookBorrowInfo::BookBorrowInfo(string bookId, time_t borrowTime, time_t returnTime) {
    this->bookId = bookId;
    this->borrowTime = borrowTime;
    this->returnTime = returnTime;
}

BookBorrowInfo::~BookBorrowInfo() {}

//获取图书id
string BookBorrowInfo::getBookId() {
    return bookId;
}

//获取借阅时间
time_t BookBorrowInfo::getBorrowTime() {
    return borrowTime;
}

//获取归还时间
time_t BookBorrowInfo::getReturnTime() {
    return returnTime;
}

//格式化时间为"年/月/日"
string BookBorrowInfo::formatTime(time_t time) {
    struct tm* timeinfo = localtime(&time);
    ostringstream oss;
    oss << (timeinfo->tm_year + 1900) << "/"
        << setfill('0') << setw(2) << (timeinfo->tm_mon + 1) << "/"
        << setfill('0') << setw(2) << timeinfo->tm_mday;
    return oss.str();
}

//获取格式化的借阅时间
string BookBorrowInfo::getFormattedBorrowTime() {
    return formatTime(borrowTime);
}

//获取格式化的归还时间
string BookBorrowInfo::getFormattedReturnTime() {
    return formatTime(returnTime);
}

//获取逾期天数
int BookBorrowInfo::getOverdueDays()const {
    auto now = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(now);
    return (currentTime - returnTime) / (24 * 60 * 60);
}

//获取剩余天数
int BookBorrowInfo::getRemainDays()const {
    auto now = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(now);
    return (returnTime - currentTime) / (24 * 60 * 60);
}

//设置图书id
void BookBorrowInfo::setBookId(string bookId) {
    this->bookId = bookId;
}

//设置借阅时间
void BookBorrowInfo::setBorrowTime(time_t borrowTime) {
    this->borrowTime = borrowTime;
}

//设置归还时间
void BookBorrowInfo::setReturnTime(time_t returnTime) {
    this->returnTime = returnTime;
}

//判断是否逾期
bool BookBorrowInfo::isOverdue() {
    auto now = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(now);
    return currentTime > returnTime;
}

//打印借阅信息
void BookBorrowInfo::printBookBorrowInfo() {
    cout<<"书本id: "<<bookId<<endl;
    cout<<"借阅时间: "<<getFormattedBorrowTime()<<endl;
    if (isOverdue()) {
        cout<<"已逾期"<<getOverdueDays()<<"天"<<endl;
        cout<<"请尽快归还"<<endl;
        return ;
    }
    cout<<"最迟归还时间: "<<getFormattedReturnTime()<<endl;
    cout<<"距离归还时间还有"<<getRemainDays()<<"天"<<endl;
}