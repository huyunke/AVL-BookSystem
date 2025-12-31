#ifndef AVL_BOOKSYSTEM_BOOKBORROWINFO_H
#define AVL_BOOKSYSTEM_BOOKBORROWINFO_H
#include <string>
#include <chrono>

using namespace std;

class BookBorrowInfo {
    string bookId;
    time_t borrowTime;//借阅时间
    time_t returnTime;//最迟归还时间
    static const int MAX_BORROW_DAYS = 30;
    string formatTime(time_t time);//格式化时间为"年/月/日"
public:
    BookBorrowInfo(string bookId);
    ~BookBorrowInfo();
    string getBookId();
    time_t getBorrowTime();
    time_t getReturnTime();
    string getFormattedBorrowTime();//获取格式化的借阅时间
    string getFormattedReturnTime();//获取格式化的归还时间
    bool isOverdue();
    int getRemainDays()const;
    int getOverdueDays()const;
    void printBookBorrowInfo();//打印图书借阅信息
};


#endif //AVL_BOOKSYSTEM_BOOKBORROWINFO_H