#ifndef AVL_BOOKSYSTEM_TXTTODATABASEWRITER_H
#define AVL_BOOKSYSTEM_TXTTODATABASEWRITER_H
#include<string>
#include "../database/dao/BookDAO.h"
#include "../database/dao/UserDAO.h"
#include "../database/dao/BookCopyDAO.h"
#include "../database/dao/RecordDAO.h"

//用于将txt文件中的数据写入数据库
class TxtToDatabaseWriter {
public:
    static void writeBooksToDatabase(const string& filePath, BookDAO* db);
    static void writeUsersToDatabase(const string& filePath, UserDAO* db);
    static void writeBookCopiesToDatabase(const string& filePath, BookCopyDAO* db);
    static void writeRecordsToDatabase(const string& filePath, RecordDAO* db);
};


#endif //AVL_BOOKSYSTEM_TXTTODATABASEWRITER_H