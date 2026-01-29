#ifndef AVL_BOOKSYSTEM_RECORDDAO_H
#define AVL_BOOKSYSTEM_RECORDDAO_H
#include "../DatabaseOperator.h"
#include "../../Record.h"
#include<vector>
/*
CREATE TABLE record (
user_id       TEXT NOT NULL,
book_id       TEXT NOT NULL,
copy_id       TEXT NOT NULL,
borrow_time   INTEGER NOT NULL,
return_time   INTEGER NOT NULL
);
*/

//用于封装对借阅信息的操作
class RecordDAO {
    DatabaseOperator *recordDatabase;
public:
    explicit RecordDAO(DatabaseOperator* recordDatabase);
    ~RecordDAO();

    //核心操作
    [[nodiscard]] bool addBorrowRecord(const Record& record) const;//为TxtToDatabaseWriter提供接口
    [[nodiscard]] bool addBorrowRecord(const string& userId, const string& copyId) const;//添加借阅记录
    [[nodiscard]] bool updateReturnTime(const string& userId, const string& copyId) const;//更新归还时间

    //查询操作
    [[nodiscard]] vector<Record> getActiveRecordsByUser(const string& userId) const;//获取用户当前借阅的记录
    [[nodiscard]] vector<Record> getHistoryRecordsByUser(const string& userId) const;//获取用户的借阅历史
    [[nodiscard]] vector<Record> getRecordsByCopyId(const string& copyId) const;//获取图书的借阅历史
    bool getRecordCountByBookId(const string& bookId,int& count) const;//获取图书的借阅次数
    bool getRecordCountByUserId(const string& userId,int& count) const;//获取用户的借阅次数

    //业务校验
    [[nodiscard]] bool hasActiveRecordByUserId(const string& userId, const string& copyId) const;//用于判断用户是否借阅该图书
    [[nodiscard]] bool hasActiveRecordByCopyId(const string& copyId) const;//用于判断图书是否已借出
};


#endif //AVL_BOOKSYSTEM_RECORDDAO_H