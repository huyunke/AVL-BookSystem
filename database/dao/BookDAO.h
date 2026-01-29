#ifndef AVL_BOOKSYSTEM_BOOKDAO_H
#define AVL_BOOKSYSTEM_BOOKDAO_H
#include "D:\CLion\AVL-BookSystem\database\DatabaseOperator.h"
#include "../../Book/Book.h"
#include <string>
#include <vector>

/*
CREATE TABLE book (
id INTEGER PRIMARY KEY,
title TEXT,
author TEXT,
category TEXT,
publisher TEXT,
);
*/

class BookDAO {
    DatabaseOperator* bookDatabase;
public:
    explicit BookDAO(DatabaseOperator* bookDatabase);
    ~BookDAO();

    //核心操作
    [[nodiscard]] bool addBook(const Book& book) const;//添加图书
    [[nodiscard]] bool deleteBook(const string& bookId) const;//删除图书
    [[nodiscard]] bool updateBook(const Book& book) const;//更新图书

    //查询操作
    bool searchBookById(const string& bookId, Book& book) const;//根据图书id查询图书信息
    bool searchBookByTitle(const string& bookTitle, Book& book) const;//根据图书名称查询图书信息
    [[nodiscard]] vector<Book> searchBooksByCategory(const string& category) const;//根据图书分类查询图书信息
    [[nodiscard]] vector<Book> searchBookByAuthor(const string& author) const;

    //业务校验
    bool isBookIdExist(const string& bookId) const;//用于判断图书id是否已存在
};


#endif //AVL_BOOKSYSTEM_BOOKDAO_H