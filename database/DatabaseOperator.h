#ifndef AVL_BOOKSYSTEM_DATABASEOPERATOR_H
#define AVL_BOOKSYSTEM_DATABASEOPERATOR_H
#include "../sqlite3.h"
#include<string>
#include <vector>
using namespace std;
class DatabaseOperator {
    sqlite3* database;
    string lastError;
public:
    DatabaseOperator();
    ~DatabaseOperator();

    //数据库连接
    bool open(const string& daPath);
    void close();

    //执行非查询操作
    bool execute(const string& sql);

    //执行查询操作
    bool query(const string& sql, vector<vector<string>>& result);

    bool prepare(const string& sql,sqlite3_stmt** statement);
    bool beginTransaction();
    bool commit();
    bool rollback();
    string getLastError() const;
};


#endif //AVL_BOOKSYSTEM_DATABASEOPERATOR_H