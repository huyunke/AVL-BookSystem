#ifndef AVL_BOOKSYSTEM_BOOKCOPYDAO_H
#define AVL_BOOKSYSTEM_BOOKCOPYDAO_H
#include "D:\CLion\AVL-BookSystem\database\DatabaseOperator.h"
#include "../../Book/BookCopy.h"
#include <string>


class BookCopyDAO {
    DatabaseOperator* bookCopyDatabase;
public:
    explicit BookCopyDAO(DatabaseOperator* bookDatabase);
    ~BookCopyDAO();

    bool addBookCopy(const BookCopy& bookCopy);
    bool deleteBookCopy(const string& copyId);

    std::vector<BookCopy> getCopiesByBookId(const string& bookId);
    std::vector<BookCopy> getAvailableCopies(const string& bookId);
};


#endif //AVL_BOOKSYSTEM_BOOKCOPYDAO_H