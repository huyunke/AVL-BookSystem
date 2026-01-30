#ifndef AVL_BOOKSYSTEM_INVENTORYSERVICE_H
#define AVL_BOOKSYSTEM_INVENTORYSERVICE_H
#include "../database/dao/BookDAO.h"
#include "../database/dao/BookCopyDAO.h"

//用于管理库存，包括图书的添加、删除、修改等操作
class InventoryService {
    BookDAO* db;
    BookCopyDAO* bookCopyDAO;
public:
    InventoryService(BookDAO* bookDAO, BookCopyDAO* bookCopyDAO);
    ~InventoryService();

    //核心操作
    [[nodiscard]] bool addBook(const Book& book) const;//添加图书
    [[nodiscard]] bool deleteBook(const string& bookId) const;//删除图书
    [[nodiscard]] bool addBookCopy(const BookCopy& bookCopy) const;//添加图书副本
    [[nodiscard]] bool deleteBookCopy(const string& copyId) const;//删除图书副本
    [[nodiscard]] bool updateBook(const Book& book) const;//更新图书
};


#endif //AVL_BOOKSYSTEM_INVENTORYSERVICE_H