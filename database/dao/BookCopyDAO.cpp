#include "BookCopyDAO.h"
/*
CREATE TABLE book_copy (
copy_id     TEXT PRIMARY KEY,
book_id     TEXT NOT NULL,
status      TEXT NOT NULL,   -- available / borrowed
);
*/

BookCopyDAO::BookCopyDAO(DatabaseOperator* bookDatabase):bookCopyDatabase(bookDatabase){}
BookCopyDAO::~BookCopyDAO()=default;

bool BookCopyDAO::addBookCopy(const BookCopy& bookCopy) {
    const string sql =
        "INSERT INTO book_copy (copy_id, book_id, status) "
        "VALUES (?, ?, ?);";

    sqlite3_stmt* stmt = nullptr;
    if (!bookCopyDatabase->prepare(sql, &stmt)) return false;

    sqlite3_bind_text(stmt, 1, bookCopy.getCopyId().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, bookCopy.getBookId().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, bookCopy.getStatus().c_str(), -1, SQLITE_TRANSIENT);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

bool BookCopyDAO::deleteBookCopy(const string& copyId) {
    const string sql = "DELETE FROM book_copy WHERE copy_id = ?;";

    sqlite3_stmt* stmt = nullptr;
    if (!bookCopyDatabase->prepare(sql, &stmt)) return false;
    sqlite3_bind_text(stmt, 1, copyId.c_str(), -1, SQLITE_TRANSIENT);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

static string columnText(sqlite3_stmt* stmt, int col) {
    const unsigned char* text = sqlite3_column_text(stmt, col);
    return text ? reinterpret_cast<const char*>(text) : "";
}

std::vector<BookCopy> BookCopyDAO::getCopiesByBookId(const string& bookId) {
    vector<BookCopy> copies;
    const string sql =
        "SELECT copy_id, book_id, status "
        "FROM book_copy "
        "WHERE book_id = ?;";

    sqlite3_stmt* stmt = nullptr;
    if (!bookCopyDatabase->prepare(sql, &stmt)) return copies;
    sqlite3_bind_text(stmt, 1, bookId.c_str(), -1, SQLITE_TRANSIENT);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        BookCopy copy;
        copy.setCopyId(columnText(stmt, 0));
        copy.setBookId(columnText(stmt, 1));
        copy.setStatus(columnText(stmt, 2));
        copies.push_back(copy);
    }

    sqlite3_finalize(stmt);
    return copies;
}

std::vector<BookCopy> BookCopyDAO::getAvailableCopies(const string& bookId) {
    vector<BookCopy> copies;
    const string sql =
        "SELECT copy_id, book_id, status "
        "FROM book_copy "
        "WHERE book_id = ? AND status = 'available';";

    sqlite3_stmt* stmt = nullptr;
    if (!bookCopyDatabase->prepare(sql, &stmt)) return copies;

    sqlite3_bind_text(stmt, 1, bookId.c_str(), -1, SQLITE_TRANSIENT);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        BookCopy copy;
        copy.setCopyId(columnText(stmt, 0));
        copy.setBookId(columnText(stmt, 1));
        copy.setStatus(columnText(stmt, 2));
        copies.push_back(copy);
    }

    sqlite3_finalize(stmt);
    return copies;
}

// int BookCopyDAO::getTotalBookCount(const string& bookId) {
//     const string sql =
//         "SELECT COUNT(*) FROM book_copy WHERE book_id=?;";
//
//     sqlite3_stmt* stmt = nullptr;
//     if (!bookCopyDatabase->prepare(sql, &stmt)) return 0;
//
//     sqlite3_bind_text(stmt, 1, bookId.c_str(),-1, SQLITE_TRANSIENT);
//
//     int count = 0;
//     if (sqlite3_step(stmt) == SQLITE_ROW) {
//         count = sqlite3_column_int(stmt, 0);
//     }
//
//     sqlite3_finalize(stmt);
//     return count;
// }
//
// int BookCopyDAO::getAvailableBookCount(const string& bookId) {
//     const std::string sql =
//         "SELECT COUNT(*) FROM book_copy "
//         "WHERE book_id=? AND status='available';";
//
//     sqlite3_stmt* stmt = nullptr;
//     if (!bookCopyDatabase->prepare(sql, &stmt)) return 0;
//
//     sqlite3_bind_text(stmt, 1, bookId.c_str(),-1, SQLITE_TRANSIENT);
//
//     int count = 0;
//     if (sqlite3_step(stmt) == SQLITE_ROW) {
//         count = sqlite3_column_int(stmt, 0);
//     }
//
//     sqlite3_finalize(stmt);
//     return count;
// }