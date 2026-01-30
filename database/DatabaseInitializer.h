#ifndef AVL_BOOKSYSTEM_DATABASEINITIALIZER_H
#define AVL_BOOKSYSTEM_DATABASEINITIALIZER_H

#include "DatabaseOperator.h"
#include <string>
using namespace std;

//用于初始化数据库
class DatabaseInitializer {
    // 创建各个表
    static bool createBookTable(DatabaseOperator* db);
    static bool createUserTable(DatabaseOperator* db);
    static bool createBookCopyTable(DatabaseOperator* db);
    static bool createRecordTable(DatabaseOperator* db);
    static bool createIndexes(DatabaseOperator* db);
public:
    // 初始化数据库，创建所有表
    static bool initializeDatabase(DatabaseOperator* db);
};

#endif //AVL_BOOKSYSTEM_DATABASEINITIALIZER_H

