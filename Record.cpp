#include "../Record.h"

Record::Record(string userId, string copyId, time_t borrowTime, time_t returnTime) {
    this->userId = userId;
    this->copyId = copyId;
    this->borrowTime = borrowTime;
    this->returnTime = returnTime;
}

Record::Record() {
    this->userId = "";
    this->copyId = "";
    this->borrowTime = 0;
    this->returnTime = 0;
}

Record::~Record() {}

string Record::getUserId()const {
    return userId;
}

string Record::getCopyId()const {
    return copyId;
}

time_t Record::getBorrowTime()const {
    return borrowTime;
}

time_t Record::getReturnTime()const {
    return returnTime;
}

void Record::setUserId(string userId) {
    this->userId = userId;
}

void Record::setCopyId(string copyId) {
    this->copyId = copyId;
}

void Record::setBorrowTime(time_t borrowTime) {
    this->borrowTime = borrowTime;
}

void Record::setReturnTime(time_t returnTime) {
    this->returnTime = returnTime;
}