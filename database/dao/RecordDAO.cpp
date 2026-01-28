#include "RecordDAO.h"
#include <chrono>

RecordDAO::RecordDAO(DatabaseOperator *recordDatabase):recordDatabase(recordDatabase) {}

RecordDAO::~RecordDAO() = default;

bool RecordDAO::addBorrowRecord(const string &userId, const string &bookId) {
    const string sql =
        "INSERT INTO record (user_id, book_id, borrow_time, return_time) "
        "VALUES (?, ?, ?, ?);";

    sqlite3_stmt* stmt = nullptr;
    if (!recordDatabase->prepare(sql, &stmt)) return false;

    auto now = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(now);

    sqlite3_bind_text(stmt, 1, userId.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, bookId.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int64(stmt, 3, currentTime);
    sqlite3_bind_int64(stmt, 4, 0);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

bool RecordDAO::updateReturnTime(const string &userId, const string &bookId) {
    const string sql = "UPDATE record SET return_time = ? WHERE user_id = ? AND book_id = ?;";

    sqlite3_stmt* stmt = nullptr;
    if (!recordDatabase->prepare(sql, &stmt)) return false;

    auto now = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(now);

    sqlite3_bind_int64(stmt, 1, currentTime);
    sqlite3_bind_text(stmt, 2, userId.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, bookId.c_str(), -1, SQLITE_TRANSIENT);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

static string columnText(sqlite3_stmt* stmt, int col) {
    const unsigned char* text = sqlite3_column_text(stmt, col);
    return text ? reinterpret_cast<const char*>(text) : "";
}

vector<Record> RecordDAO::getActiveRecordsByUser(const string &userId) {
    vector<Record> records;
    const string sql = "SELECT user_id, book_id, borrow_time, return_time FROM record WHERE user_id = ? AND return_time = 0;";

    sqlite3_stmt* stmt = nullptr;
    if (!recordDatabase->prepare(sql, &stmt)) return records;

    sqlite3_bind_text(stmt, 1, userId.c_str(), -1, SQLITE_TRANSIENT);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Record record;
        record.setUserId(columnText(stmt, 0));
        record.setCopyId(columnText(stmt, 1));
        record.setBorrowTime(sqlite3_column_int64(stmt, 2));
        records.push_back(record);
    }
    sqlite3_finalize(stmt);
    return records;
}

vector<Record> RecordDAO::getRecordsByUser(const string &userId) {
    vector<Record> records;
    const string sql = "SELECT user_id, book_id, borrow_time, return_time FROM record WHERE user_id = ?;";

    sqlite3_stmt* stmt = nullptr;
    if (!recordDatabase->prepare(sql, &stmt)) return records;

    sqlite3_bind_text(stmt, 1, userId.c_str(), -1, SQLITE_TRANSIENT);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Record record;
        record.setUserId(columnText(stmt, 0));
        record.setCopyId(columnText(stmt, 1));
        record.setBorrowTime(sqlite3_column_int64(stmt, 2));
        records.push_back(record);
    }
    sqlite3_finalize(stmt);
    return records;
}

vector<Record> RecordDAO::getRecordsByCopyId(const string &copyId) {
    vector<Record> records;
    const string sql = "SELECT user_id, book_id, borrow_time, return_time FROM record WHERE book_id = ?;";

    sqlite3_stmt* stmt = nullptr;
    if (!recordDatabase->prepare(sql, &stmt)) return records;

    sqlite3_bind_text(stmt, 1, copyId.c_str(), -1, SQLITE_TRANSIENT);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Record record;
        record.setUserId(columnText(stmt, 0));
        record.setCopyId(columnText(stmt, 1));
        record.setBorrowTime(sqlite3_column_int64(stmt, 2));
        records.push_back(record);
    }
    sqlite3_finalize(stmt);
    return records;
}

bool RecordDAO::hasActiveRecord(const string &userId, const string &copyId) {
    const string sql = "SELECT COUNT(*) FROM record WHERE user_id = ? AND book_id = ? AND return_time = 0;";

    sqlite3_stmt* stmt = nullptr;
    if (!recordDatabase->prepare(sql, &stmt)) return false;

    sqlite3_bind_text(stmt, 1, userId.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, copyId.c_str(), -1, SQLITE_TRANSIENT);

    int count = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        count = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);
    return count > 0;
}