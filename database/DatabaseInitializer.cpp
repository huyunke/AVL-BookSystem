#include "DatabaseInitializer.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

bool DatabaseInitializer::initializeDatabase(DatabaseOperator* db) {
    if (!db) {
        cerr << "数据库操作对象为空" << std::endl;
        return false;
    }

    // 创建表
    if (!createBookTable(db)) return false;
    if (!createUserTable(db)) return false;
    if (!createBookCopyTable(db)) return false;
    if (!createRecordTable(db)) return false;
    if (!createIndexes(db)) return false;

    cout << "数据库初始化成功" << std::endl;
    return true;
}

bool DatabaseInitializer::createBookTable(DatabaseOperator* db) {
    const string sql = R"(
        CREATE TABLE IF NOT EXISTS book (
            id TEXT PRIMARY KEY,
            title TEXT NOT NULL,
            author TEXT NOT NULL,
            category TEXT,
            publisher TEXT
        );
    )";
    
    if (!db->execute(sql)) {
        cerr << "创建book表失败: " << db->getLastError() << endl;
        return false;
    }
    cout << "book表创建成功" << std::endl;
    return true;
}

bool DatabaseInitializer::createUserTable(DatabaseOperator* db) {
    const string sql = R"(
        CREATE TABLE IF NOT EXISTS user (
            user_id TEXT PRIMARY KEY,
            name TEXT NOT NULL,
            role TEXT NOT NULL,
            password TEXT NOT NULL,
            borrow_count INTEGER DEFAULT 0
        );
    )";
    
    if (!db->execute(sql)) {
        cerr << "创建user表失败: " << db->getLastError() << endl;
        return false;
    }
    cout << "user表创建成功" << endl;
    return true;
}

bool DatabaseInitializer::createBookCopyTable(DatabaseOperator* db) {
    const string sql = R"(
        CREATE TABLE IF NOT EXISTS book_copy (
            copy_id TEXT PRIMARY KEY,
            book_id TEXT NOT NULL,
            status TEXT NOT NULL,
            FOREIGN KEY (book_id) REFERENCES book(id)
        );
    )";
    
    if (!db->execute(sql)) {
        cerr << "创建book_copy表失败: " << db->getLastError() << endl;
        return false;
    }
    cout << "book_copy表创建成功" << endl;
    return true;
}

bool DatabaseInitializer::createRecordTable(DatabaseOperator* db) {
    const string sql = R"(
        CREATE TABLE IF NOT EXISTS record (
            user_id TEXT NOT NULL,
            book_id TEXT NOT NULL,
            copy_id TEXT NOT NULL,
            borrow_time INTEGER NOT NULL,
            return_time INTEGER NOT NULL,
            FOREIGN KEY (user_id) REFERENCES user(user_id),
            FOREIGN KEY (copy_id) REFERENCES book_copy(copy_id)
        );
    )";
    
    if (!db->execute(sql)) {
        cerr << "创建record表失败: " << db->getLastError() << endl;
        return false;
    }
    cout << "record表创建成功" << endl;
    return true;
}

bool DatabaseInitializer::createIndexes(DatabaseOperator* db) {
    const vector<string> indexSQLs = {
        "CREATE INDEX IF NOT EXISTS idx_book_title ON book(title);",
        "CREATE INDEX IF NOT EXISTS idx_book_author ON book(author);",
        "CREATE INDEX IF NOT EXISTS idx_book_category ON book(category);",
        "CREATE INDEX IF NOT EXISTS idx_book_copy_book_id ON book_copy(book_id);",
        "CREATE INDEX IF NOT EXISTS idx_book_copy_status ON book_copy(status);",
        "CREATE INDEX IF NOT EXISTS idx_record_user_id ON record(user_id);",
        "CREATE INDEX IF NOT EXISTS idx_record_copy_id ON record(copy_id);",
        "CREATE INDEX IF NOT EXISTS idx_record_book_id ON record(book_id);"
    };

    for (const auto& sql : indexSQLs) {
        if (!db->execute(sql)) {
            cerr << "创建索引失败: " << db->getLastError() << endl;
            return false;
        }
    }
    
    cout << "索引创建成功" << endl;
    return true;
}