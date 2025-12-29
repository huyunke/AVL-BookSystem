#ifndef AVL_BOOKSYSTEM_BOOKBORROWINFO_H
#define AVL_BOOKSYSTEM_BOOKBORROWINFO_H
#include "Book.h"
#include <string>
#include <chrono>
#include <vector>
#include <ctime>
#include <algorithm>
#include <iomanip>
using namespace std;

class BookBorrowInfo {
    Book book;
    time_t borrowTime;//借阅时间
    time_t returnTime;//最迟归还时间
    static const int MAX_BORROW_DAYS = 30;
public:
    BookBorrowInfo(Book book,time_t borrowTime, time_t returnTime);
    ~BookBorrowInfo();
    Book getBook();
    time_t getBorrowTime();
    time_t getReturnTime();
    bool isOverdue();
    int getRemainDays()const;
    int getOverdueDays()const;
    void printBookBorrowInfo();//打印图书借阅信息
};


#endif //AVL_BOOKSYSTEM_BOOKBORROWINFO_H