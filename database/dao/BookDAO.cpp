#include "BookDAO.h"

BookDAO::BookDAO(DatabaseOperator* bookDatabase):bookDatabase(bookDatabase){}

BookDAO::~BookDAO() = default;

//添加图书
bool BookDAO::addBook(const Book &book) const {
    const string sql =
        "INSERT INTO book (id, title, author, category, publisher) "
        "VALUES (?, ?, ?, ?, ?);";

    sqlite3_stmt* stmt = nullptr;
    if (!bookDatabase->prepare(sql, &stmt)) return false;

    sqlite3_bind_text(stmt, 1, book.getId().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, book.getTitle().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, book.getAuthor().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, book.getCategory().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 5, book.getPublisher().c_str(), -1, SQLITE_TRANSIENT);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

//删除图书
bool BookDAO::deleteBook(const string &bookId) const {
    const string sql = "DELETE FROM book WHERE id = ?;";

    sqlite3_stmt* stmt = nullptr;
    if (!bookDatabase->prepare(sql, &stmt)) return false;

    sqlite3_bind_text(stmt, 1, bookId.c_str(), -1, SQLITE_TRANSIENT);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

//更新图书
bool BookDAO::updateBook(const Book &book) const {
    const string sql = "UPDATE book SET title=?, author=?, category=?, publisher=? "
        "WHERE id=?;";

    sqlite3_stmt* stmt = nullptr;
    if (!bookDatabase->prepare(sql, &stmt)) return false;

    sqlite3_bind_text(stmt, 1, book.getTitle().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, book.getAuthor().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, book.getCategory().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, book.getPublisher().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 5, book.getId().c_str(), -1, SQLITE_TRANSIENT);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

//用于获取列文本
static string columnText(sqlite3_stmt* stmt, int col) {
    const unsigned char* text = sqlite3_column_text(stmt, col);
    return text ? reinterpret_cast<const char*>(text) : "";
}

//从查询结果中提取图书信息
static Book extractBook(sqlite3_stmt* stmt) {
    Book book;
    book.setBookId(columnText(stmt, 0));
    book.setBookTitle(columnText(stmt, 1));
    book.setAuthor(columnText(stmt, 2));
    book.setCategory(columnText(stmt, 3));
    book.setPublisher(columnText(stmt, 4));
    return book;
}

//根据图书id查询图书信息
bool BookDAO::searchBookById(const string &bookId, Book& book) const {
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

//根据图书名称查询图书信息
bool BookDAO::searchBookByTitle(const string &bookTitle, Book& book) const {
    const string sql = "SELECT id, title, author, category, publisher FROM book WHERE title = ?;";
    sqlite3_stmt* stmt = nullptr;
    if (!bookDatabase->prepare(sql, &stmt)) return false;
    sqlite3_bind_text(stmt, 1, bookTitle.c_str(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        book = extractBook(stmt);
        sqlite3_finalize(stmt);
        return true;
    }
    sqlite3_finalize(stmt);
    return false;
}

//根据图书分类查询图书信息
vector<Book> BookDAO::searchBooksByCategory(const string &category) const {
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

vector<Book> BookDAO::searchBookByAuthor(const string &author) const {
    vector<Book> books;
    const string sql = "SELECT id, title, author, category, publisher FROM book WHERE author = ?;";

    sqlite3_stmt* stmt = nullptr;
    if (!bookDatabase->prepare(sql, &stmt)) return books;

    sqlite3_bind_text(stmt, 1, author.c_str(), -1, SQLITE_TRANSIENT);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        books.push_back(extractBook(stmt));
    }

    sqlite3_finalize(stmt);
    return books;
}

bool BookDAO::isBookIdExist(const string &bookId) const {
    const string sql = "SELECT COUNT(*) FROM book WHERE id = ?;";
    sqlite3_stmt* stmt = nullptr;
    if (!bookDatabase->prepare(sql, &stmt)) return false;

    sqlite3_bind_text(stmt, 1, bookId.c_str(), -1, SQLITE_TRANSIENT);

    int count = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        count = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);
    return count > 0;
}
