#ifndef AVL_BOOKSYSTEM_SEARCHSERVICE_H
#define AVL_BOOKSYSTEM_SEARCHSERVICE_H
#include "../database/dao/BookDAO.h"

//用于管理图书的查询等操作
class SearchService {
    BookDAO* db;
public:
    SearchService(BookDAO* bookDAO);
    ~SearchService();
    [[nodiscard]] bool searchBookById(const string& bookId, Book& book) const;//根据图书id查询图书信息
    [[nodiscard]] vector<Book> searchBooksByCategory(const string& category) const;//根据图书分类查询图书信息
    [[nodiscard]] vector<Book> searchBookByAuthor(const string& author) const;//根据图书作者查询图书信息
    [[nodiscard]] bool searchBookByTitle(const string& bookTitle, Book& book) const;//根据图书名称查询图书信息
};


#endif //AVL_BOOKSYSTEM_SEARCHSERVICE_H