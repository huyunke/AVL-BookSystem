#ifndef AVL_BOOKSYSTEM_RECORDDAO_H
#define AVL_BOOKSYSTEM_RECORDDAO_H
#include "../DatabaseOperator.h"
#include "../../Record.h"
#include<vector>
/*
CREATE TABLE record (
user_id       TEXT NOT NULL,
book_id       TEXT NOT NULL,
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

    bool addBorrowRecord(const string& userId, const string& bookId);
    bool updateReturnTime(const string& userId, const string& bookId);

    vector<Record> getActiveRecordsByUser(const string& userId);
    vector<Record> getRecordsByUser(const string& userId);
    vector<Record> getRecordsByCopyId(const string& copyId);
    bool hasActiveRecord(const string& userId, const string& copyId);

};


#endif //AVL_BOOKSYSTEM_RECORDDAO_H