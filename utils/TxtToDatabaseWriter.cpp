#include "TxtToDatabaseWriter.h"
#include "../database/dao/BookCopyDAO.h"
#include <fstream>
#include <iostream>
#include <sstream>

void TxtToDatabaseWriter::writeBooksToDatabase(const string &filePath, BookDAO *db) {
    ifstream bookFile(filePath);
    if (!bookFile) {
        cout << "无法打开图书文件" << endl;//后续写入日志
        return ;
    }

    string line;
    int count=1;
    while (getline(bookFile, line)) {
        istringstream iss(line);
        string bookId;
        string title;
        string author;
        string category;
        string publisher;
        iss>>bookId>>title>>author>>category>>publisher;

        Book book = Book(bookId,title,author,category,publisher);
        if (!db->addBook(book)) {
            cout << "第"<<count<<"行记录添加到数据库失败" << endl;//后续写入日志
        }
    }

    bookFile.close();
    cout << "图书数据写入数据库完成" << endl;//后续写入日志
}

void TxtToDatabaseWriter::writeUsersToDatabase(const string &filePath, UserDAO *db) {
    ifstream userFile(filePath);
    if (!userFile) {
        cout << "无法打开用户文件" << endl;//后续写入日志
        return ;
    }

    string line;
    int count=1;
    while (getline(userFile, line)) {
        istringstream iss(line);
        string userId;
        string name;
        string password;//加密过后的密码
        string type;
        iss>>userId>>name>>password>>type;

        User user = User(userId,name,password,type);
        if (!db->addUser(user)) {
            cout << "第"<<count<<"行记录添加到数据库失败" << endl;//后续写入日志
        }
    }

    userFile.close();
    cout << "用户数据写入数据库完成" << endl;//后续写入日志
}

void TxtToDatabaseWriter::writeBookCopiesToDatabase(const string &filePath, BookCopyDAO *db) {
    ifstream bookFile(filePath);
    if (!bookFile) {
        cout << "无法打开图书副本文件" << endl;//后续写入日志
        return ;
    }

    string line;
    int count=1;
    while (getline(bookFile, line)) {
        istringstream iss(line);
        string copyId;
        string bookId;
        string status;
        iss>>copyId>>bookId>>status;
        if (copyId.empty()||bookId.empty()||status.empty()) {
            cout << "第"<<count<<"行图书副本信息不完整" << endl;//后续写入日志
            count++;
            continue;
        }

        BookCopy bookCopy = BookCopy(bookId,copyId,status);
        if (!db->addBookCopy(bookCopy)) {
            cout << "第"<<count<<"行记录添加到数据库失败" << endl;//后续写入日志
        }
    }

    bookFile.close();
    cout << "图书副本数据写入数据库完成" << endl;//后续写入日志
}

void TxtToDatabaseWriter::writeRecordsToDatabase(const string &filePath, RecordDAO *db) {
    ifstream recordFile(filePath);
    if (!recordFile) {
        cout << "无法打开借阅记录文件" << endl;//后续写入日志
        return ;
    }

    string line;
    int count=1;
    while (getline(recordFile, line)) {
        istringstream iss(line);
        string userId;
        string copyId;
        string borrowTimeStr;
        string returnTimeStr;
        iss>>userId>>copyId>>borrowTimeStr>>returnTimeStr;

        time_t borrowTime = stoll(borrowTimeStr);
        time_t returnTime = stoll(returnTimeStr);

        Record record = Record(userId,copyId,borrowTime,returnTime);
        if (!db->addBorrowRecord(record)) {
            cout << "第"<<count<<"行记录添加到数据库失败" << endl;//后续写入日志
        }
    }

    recordFile.close();
    cout << "借阅记录数据写入数据库完成" << endl;//后续写入日志
}