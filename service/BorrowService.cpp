#include "BorrowService.h"
#include <iostream>

BorrowService::BorrowService(BookCopyDAO* bookCopyDAO, RecordDAO* recordDAO, UserDAO* userDAO)
: bookCopyDAO(bookCopyDAO), recordDAO(recordDAO), userDAO(userDAO) {}

BorrowService::~BorrowService() = default;

//借阅书本
bool BorrowService::borrowBook(const string &userId, const string &copyId) const {
    if (canBorrow(userId,copyId)) {
        if (recordDAO->addBorrowRecord(userId,copyId) && bookCopyDAO->updateBookCopyStatus(copyId,"borrowed") && userDAO->updateUserBorrowInfo(userId,true)) {
            cout<<"借阅成功"<<endl;//显示在用户界面
            return true;
        }
        cout<<"借阅失败"<<endl;//显示在用户界面
        return false;
    }
    return false;
}

//归还书本
bool BorrowService::returnBook(const string &userId, const string &copyId) const {
    if (!hasUserBorrowedCopy(userId, copyId)) {
        cout<<"你未借阅过该图书"<<endl;
        return false;
    }
    if (recordDAO->updateReturnTime(userId,copyId) && bookCopyDAO->updateBookCopyStatus(copyId,"available") && userDAO->updateUserBorrowInfo(userId,false)) {
        cout<<"归还成功"<<endl;
        return true;
    }
    cout<<"归还失败"<<endl;
    return false;
}

//是否可以借阅
bool BorrowService::canBorrow(const string &userId, const string &copyId) const {
    //如果用户是黑名单用户，则不能借阅（待实现）
    if (!canUserBorrowMore(userId)) return false;//用户界面应有提示信息"你的借阅数量已达到上限"
    if (hasUserBorrowedCopy(userId, copyId)) return false;//用户界面应有提示信息”你已借阅过该图书“
    if (isCopyBorrowed(copyId)) return false;//用户界面应有提示信息“该图书已借出”
    return true;
}

//用户是否可以继续借阅
bool BorrowService::canUserBorrowMore(const string &userId) const {
    int count=0;
    return recordDAO->getRecordCountByUserId(userId,count) && count<MAX_BORROW_COUNT;
}

//获取用户当前借阅的记录
vector<Record> BorrowService::getUserBorrowingRecords(const string &userId) const {
    return recordDAO->getActiveRecordsByUser(userId);
}

//书本是否已借出
bool BorrowService::isCopyBorrowed(const string &copyId) const {
    return bookCopyDAO->isCopyBorrowed(copyId);
}

//用户是否已借阅过该图书
bool BorrowService::hasUserBorrowedCopy(const string &userId, const string &copyId) const {
    return recordDAO->hasActiveRecordByUserId(userId, copyId);
}

// bool renewBook(const string& userId, const string& copyId);//续借
// bool hasOverdueBooks(const string& userId);//是否逾期

//设置最大借阅数量
void BorrowService::setMaxBorrowCount(int maxBorrowCount) {
    MAX_BORROW_COUNT = maxBorrowCount;
}
