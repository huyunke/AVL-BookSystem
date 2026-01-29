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

    bool addBook(const Book& book);
    bool deleteBook(const string& bookId);
    bool updateBook(const Book& book);

    bool searchBookById(const string& bookId, Book& book);
    bool searchBookByName(const string& bookName, Book& book);
    vector<Book> searchBooksByCategory(const string& category);
};


#endif //AVL_BOOKSYSTEM_BOOKDAO_H