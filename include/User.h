#ifndef AVL_BOOKSYSTEM_USER_H
#define AVL_BOOKSYSTEM_USER_H
#include <string>
#include <vector>
#include "BookBorrowInfo.h"
#include "AVLTree.h"

using namespace std;

class User {
    string id;
    string name;
    string password;
    string type;
    vector<BookBorrowInfo> borrowInfo;//借阅图书的相关信息，可以借阅多本（设定归还时间/借阅数量限制）
public:
    User(string id,string name, string password,string type="reader");
    ~User();
    string getId();
    string getName();
    string getPassword();
    string getType();
    void addBorrowInfo(string bookId);//添加借阅信息
    bool removeBorrowInfo(string bookId);//移除借阅信息，归还成功返回true，失败返回false
    void addBook(Book &book,AVLTree* tree);//添加图书（管理员）
    void removeBook(const string& bookId);//删除图书（管理员）
    void printBorrowInfo();//打印借阅信息
    vector<BookBorrowInfo> getBorrowBookInfo();
    string getBorrowBookId();
};

#endif //AVL_BOOKSYSTEM_USER_H