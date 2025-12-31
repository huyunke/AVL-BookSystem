#ifndef AVL_BOOKSYSTEM_BOOK_H
#define AVL_BOOKSYSTEM_BOOK_H
#include <string>
#include <chrono>
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
    string getId()const;//获取图书id
    string getName()const;//获取图书名称
    bool getStatus() const;//获取图书状态
    string getBorrowerId() const;//获取借阅者id
    string getAuthor() const;//获取图书作者
    void setBookStatus(bool status);//设置图书状态
    void setBorrowerId(string userId);//设置借阅者id
    void setBookName(string name);//设置图书名称
    void setAuthor(string author);//设置图书作者
    void printBookInfo(bool isAdmin);//打印图书信息

    //重载比较运算符, 用于AVL树排序
    bool operator<(const Book& book1)const;
    bool operator>(const Book& book1)const;
    bool operator==(const Book& book1)const;
};

#endif //AVL_BOOKSYSTEM_BOOK_H