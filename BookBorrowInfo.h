#ifndef AVL_BOOKSYSTEM_BOOKBORROWINFO_H
#define AVL_BOOKSYSTEM_BOOKBORROWINFO_H
#include <string>
#include <chrono>

using namespace std;

class BookBorrowInfo {
    string bookId;//图书id
    time_t borrowTime;//借阅时间
    time_t returnTime;//最迟归还时间
    static const int MAX_BORROW_DAYS = 30;//最大借阅天数
    string formatTime(time_t time);//格式化时间为"年/月/日"
public:
    BookBorrowInfo(string bookId);
    BookBorrowInfo(string bookId, time_t borrowTime, time_t returnTime);//带时间参数的构造函数
    ~BookBorrowInfo();
    string getBookId();//获取图书id
    time_t getBorrowTime();//获取借阅时间
    time_t getReturnTime();//获取归还时间
    string getFormattedBorrowTime();//获取格式化的借阅时间
    string getFormattedReturnTime();//获取格式化的归还时间
    int getOverdueDays()const;//获取逾期天数
    int getRemainDays()const;//获取剩余天数
    void setBookId(string bookId);//设置图书id
    void setBorrowTime(time_t borrowTime);//设置借阅时间
    void setReturnTime(time_t returnTime);//设置归还时间

    bool isOverdue();//判断是否逾期
    void printBookBorrowInfo();//打印借阅信息
};


#endif //AVL_BOOKSYSTEM_BOOKBORROWINFO_H