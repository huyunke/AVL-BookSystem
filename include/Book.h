#ifndef AVL_BOOKSYSTEM_BOOK_H
#define AVL_BOOKSYSTEM_BOOK_H
#include<string>
#include<chrono>
#include"User.h"
using namespace std;

class Book {
    string id;//图书的id
    string name;//图书的名称
    string author;//图书的作者
    string borrowerId;//借阅者id
    bool status;//表示图书是否可借
public:
    Book(string id, string name, string author,string borrowerId,bool status=true);
    ~Book();
    string getId()const;
    string getName()const;
    bool getStatus() const;
    string getBorrowerId() const;
    string getAuthor() const;
    void printBookInfo();//打印图书信息
    void setBookStatus(bool status);
    void setBorrower(string userId);
    //重载比较运算符, 用于AVL树排序
    bool operator<(const Book& book1)const;
    bool operator>(const Book& book1)const;
    bool operator==(const Book& book1)const;
};

#endif //AVL_BOOKSYSTEM_BOOK_H