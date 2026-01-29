#ifndef AVL_BOOKSYSTEM_BOOKCOPYDAO_H
#define AVL_BOOKSYSTEM_BOOKCOPYDAO_H
#include "../../database/DatabaseOperator.h"
#include "../../Book/BookCopy.h"
#include <string>


class BookCopyDAO {
    DatabaseOperator* bookCopyDatabase;
public:
    explicit BookCopyDAO(DatabaseOperator* bookDatabase);
    ~BookCopyDAO();

    //核心操作
    [[nodiscard]] bool addBookCopy(const BookCopy& bookCopy) const;//添加图书副本
    [[nodiscard]] bool deleteBookCopy(const string& copyId) const;//删除图书副本
    [[nodiscard]] bool updateBookCopyStatus(const string& copyId, const string& status) const;//更新图书副本状态

    //查询操作
    [[nodiscard]] vector<BookCopy> getCopiesByBookId(const string& bookId) const;//根据图书id获取所有副本
    [[nodiscard]] vector<BookCopy> getAvailableCopies(const string& bookId) const;//根据图书id获取所有可借阅的副本

    //校验
    [[nodiscard]] bool isCopyBorrowed(const string& copyId) const;//根据副本id判断图书是否已借出
};


#endif //AVL_BOOKSYSTEM_BOOKCOPYDAO_H