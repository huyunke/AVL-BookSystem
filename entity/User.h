#ifndef AVL_BOOKSYSTEM_USER_H
#define AVL_BOOKSYSTEM_USER_H
#include <string>
#include <vector>

using namespace std;

class User {
    string id;//用户id
    string name;//用户名
    string password;//用户密码
    string type;//用户类型

    // int borrowedBookCount=0;//已借阅数量
    // vector<BookBorrowInfo> borrowInfo;//借阅图书的相关信息，可以借阅多本，设定归还时间
public:
    User(string id,string name, string password,string type="reader");
    User();
    ~User();
    const string getId()const;//获取用户id
    const string getName()const;//获取用户名
    const string getPassword()const;//获取用户密码
    const string getType()const;//获取用户类型

    // vector<BookBorrowInfo> getBorrowBookInfo()const;//获取借阅图书信息
    // const string getBorrowBookDataWithTime();//获取借阅图书数据（包含时间信息）
    // int getBorrowedBookCount()const;//获取已借阅数量

    void setId(string id);
    void setName(string name);
    void setPassword(string password);//设置用户密码

    // void setBorrowedBookCount(int borrowedBookCount);
    //
    // void addBorrowInfo(string bookId);//添加借阅信息
    // void addBorrowInfoWithTime(string bookId, time_t borrowTime, time_t returnTime);//添加借阅信息（带时间参数，用于从文件读取）
    // bool removeBorrowInfo(string bookId);//移除借阅信息，归还成功返回true，失败返回false
    // bool updateBorrowBookId(string oldBookId, string newBookId);//更新借阅信息中的图书id
    // void printBorrowInfo();//打印借阅信息
};

#endif //AVL_BOOKSYSTEM_USER_H