#ifndef AVL_BOOKSYSTEM_USER_H
#define AVL_BOOKSYSTEM_USER_H
#include <string>
#include <vector>
#include "BookBorrowInfo.h"
#include "AVLTree.h"

using namespace std;

class User {
    string id;//用户id
    string name;//用户名
    string password;//用户密码
    string type;//用户类型
    vector<BookBorrowInfo> borrowInfo;//借阅图书的相关信息，可以借阅多本，设定归还时间
public:
    User(string id,string name, string password,string type="reader");
    ~User();
    string getId();//获取用户id
    string getName();//获取用户名
    string getPassword();//获取用户密码
    string getType();//获取用户类型
    vector<BookBorrowInfo> getBorrowBookInfo();//获取借阅图书信息
    string getBorrowBookDataWithTime();//获取借阅图书数据（包含时间信息）
    void setPassword(string password);//设置用户密码
    void addBorrowInfo(string bookId);//添加借阅信息
    void addBorrowInfoWithTime(string bookId, time_t borrowTime, time_t returnTime);//添加借阅信息（带时间参数，用于从文件读取）
    bool removeBorrowInfo(string bookId);//移除借阅信息，归还成功返回true，失败返回false
    bool updateBorrowBookId(string oldBookId, string newBookId);//更新借阅信息中的图书id
    void printBorrowInfo();//打印借阅信息
};

#endif //AVL_BOOKSYSTEM_USER_H