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

    [[nodiscard]] bool addBorrowRecord(const Record& record) const;//为TxtToDatabaseWriter提供接口
    [[nodiscard]] bool addBorrowRecord(const string& userId, const string& copyId) const;
    [[nodiscard]] bool updateReturnTime(const string& userId, const string& copyId) const;

    [[nodiscard]] vector<Record> getActiveRecordsByUser(const string& userId) const;
    [[nodiscard]] vector<Record> getRecordsByUser(const string& userId) const;
    [[nodiscard]] vector<Record> getRecordsByCopyId(const string& copyId) const;
    bool getRecordCountByBookId(const string& bookId,int& count) const;

    [[nodiscard]] bool hasActiveRecord(const string& userId, const string& copyId) const;
};


#endif //AVL_BOOKSYSTEM_RECORDDAO_H