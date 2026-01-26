#include "BookDAO.h"

BookDAO::BookDAO(DatabaseOperator* bookDatabase):bookDatabase(bookDatabase){}

BookDAO::~BookDAO() = default;

bool BookDAO::addBook(const Book &book) {
    const string sql =
        "INSERT INTO book (id, title, author, category, publisher) "
        "VALUES (?, ?, ?, ?, ?);";

    sqlite3_stmt* stmt = nullptr;
    if (!bookDatabase->prepare(sql, &stmt)) return false;

    sqlite3_bind_text(stmt, 1, book.getId().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, book.getName().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, book.getAuthor().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, book.getCategory().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 5, book.getPublisher().c_str(), -1, SQLITE_TRANSIENT);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

bool BookDAO::updateBook(const Book &book) {
    const string sql = "UPDATE book SET title=?, author=?, category=?, publisher=? "
        "WHERE id=?;";

    sqlite3_stmt* stmt = nullptr;
    if (!bookDatabase->prepare(sql, &stmt)) return false;

    sqlite3_bind_text(stmt, 1, book.getName().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, book.getAuthor().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, book.getCategory().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, book.getPublisher().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 5, book.getId().c_str(), -1, SQLITE_TRANSIENT);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

bool BookDAO::deleteBook(const string &bookId) {
    const string sql = "DELETE FROM book WHERE id = ?;";

    sqlite3_stmt* stmt = nullptr;
    if (!bookDatabase->prepare(sql, &stmt)) return false;

    sqlite3_bind_text(stmt, 1, bookId.c_str(), -1, SQLITE_TRANSIENT);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

static string columnText(sqlite3_stmt* stmt, int col) {
    const unsigned char* text = sqlite3_column_text(stmt, col);
    return text ? reinterpret_cast<const char*>(text) : "";
}

static Book extractBook(sqlite3_stmt* stmt) {
    Book book;
    book.setBookId(columnText(stmt, 0));
    book.setBookName(columnText(stmt, 1));
    book.setAuthor(columnText(stmt, 2));
    book.setCategory(columnText(stmt, 3));
    book.setPublisher(columnText(stmt, 4));
    return book;
}


bool BookDAO::searchBookById(const string &bookId, Book& book) {
    const string sql = "SELECT id, title, author, category, publisher FROM book WHERE id = ?;";

    sqlite3_stmt* stmt = nullptr;
    if (!bookDatabase->prepare(sql, &stmt)) return false;
    sqlite3_bind_text(stmt, 1, bookId.c_str(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        book = extractBook(stmt);
        sqlite3_finalize(stmt);
        return true;
    }
    sqlite3_finalize(stmt);
    return false;
}

bool BookDAO::searchBookByName(const string &bookName, Book& book) {
    const string sql = "SELECT id, title, author, category, publisher FROM book WHERE title = ?;";
    sqlite3_stmt* stmt = nullptr;
    if (!bookDatabase->prepare(sql, &stmt)) return false;
    sqlite3_bind_text(stmt, 1, bookName.c_str(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        book = extractBook(stmt);
        sqlite3_finalize(stmt);
        return true;
    }
    sqlite3_finalize(stmt);
    return false;
}

vector<Book> BookDAO::searchBooksByCategory(const string &category) {
    vector<Book> books;
    const string sql = "SELECT id, title, author, category, publisher FROM book WHERE category = ?;";

    sqlite3_stmt* stmt = nullptr;
    if (!bookDatabase->prepare(sql, &stmt)) return books;
    sqlite3_bind_text(stmt, 1, category.c_str(), -1, SQLITE_TRANSIENT);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        books.push_back(extractBook(stmt));
    }

    sqlite3_finalize(stmt);
    return books;
}



