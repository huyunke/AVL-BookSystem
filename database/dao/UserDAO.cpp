#include "UserDAO.h"
#include "../../utils/PasswordUtils.h"
/*
User
-------------------------
user_id        PK
name
role           (student / admin)
password
*/

UserDAO::UserDAO(DatabaseOperator* userDatabase):userDatabase(userDatabase){}

UserDAO::~UserDAO() {}

bool UserDAO::addUser(const User& user) {
    const string sql =
        "INSERT INTO user (user_id, name, role, password, borrow_count) "
        "VALUES (?, ?, ?, ?, ?);";

    sqlite3_stmt* stmt = nullptr;
    if (!userDatabase->prepare(sql, &stmt)) return false;

    sqlite3_bind_text(stmt, 1, user.getId().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, user.getName().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, user.getType().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, user.getPassword().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 5, 0);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

bool UserDAO::deleteUser(const string& userId) {
    const string sql = "DELETE FROM user WHERE user_id = ?;";
    sqlite3_stmt* stmt = nullptr;

    if (!userDatabase->prepare(sql, &stmt)) return false;

    sqlite3_bind_text(stmt, 1, userId.c_str(), -1, SQLITE_TRANSIENT);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

bool UserDAO::updateUserPassword(const string& userId, const string& newPassword) {
    const string sql = "UPDATE user SET password = ? WHERE user_id = ?;";
    sqlite3_stmt* stmt = nullptr;

    if (!userDatabase->prepare(sql, &stmt)) return false;

    sqlite3_bind_text(stmt, 1, newPassword.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, userId.c_str(), -1, SQLITE_TRANSIENT);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

bool UserDAO::updateUserBorrowInfo(const string& userId,bool flag) {
    //flag为true时，借阅数量加1，否则减1
    if (flag) {
        const string sql = "UPDATE user SET borrow_count = borrow_count + 1 WHERE user_id = ?;";
        sqlite3_stmt* stmt = nullptr;

        if (!userDatabase->prepare(sql, &stmt)) return false;

        sqlite3_bind_text(stmt, 1, userId.c_str(), -1, SQLITE_TRANSIENT);

        bool success = (sqlite3_step(stmt) == SQLITE_DONE);
        sqlite3_finalize(stmt);
        return success;
    }
    const string sql = "UPDATE user SET borrow_count = borrow_count - 1 WHERE user_id = ?;";
    sqlite3_stmt* stmt = nullptr;

    if (!userDatabase->prepare(sql, &stmt)) return false;

    sqlite3_bind_text(stmt, 1, userId.c_str(), -1, SQLITE_TRANSIENT);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

static string columnText(sqlite3_stmt* stmt, int col) {
    const unsigned char* text = sqlite3_column_text(stmt, col);
    return text ? reinterpret_cast<const char*>(text) : "";
}

bool UserDAO::searchUserById(const string& userId, User& user) {
    const string sql = "SELECT user_id, name, role, password FROM user WHERE user_id = ?;";
    sqlite3_stmt* stmt = nullptr;

    if (!userDatabase->prepare(sql, &stmt)) return false;

    sqlite3_bind_text(stmt, 1, userId.c_str(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        user.setId(columnText(stmt, 0));
        user.setName(columnText(stmt, 1));
        user.setPassword(columnText(stmt, 3));
        sqlite3_finalize(stmt);
        return true;
    }
    sqlite3_finalize(stmt);
    return false;
}

bool UserDAO::exists(const string& userId) {
    const string sql = "SELECT COUNT(*) FROM user WHERE user_id = ?;";
    sqlite3_stmt* stmt = nullptr;

    if (!userDatabase->prepare(sql, &stmt)) return false;

    sqlite3_bind_text(stmt, 1, userId.c_str(), -1, SQLITE_TRANSIENT);

    int count = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        count = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);
    return count > 0;
}

bool UserDAO::verifyUser(const string& userId, const string& password) {
    const string sql = "SELECT password FROM user WHERE user_id = ?;";
    sqlite3_stmt* stmt = nullptr;

    if (!userDatabase->prepare(sql, &stmt)) return false;

    sqlite3_bind_text(stmt, 1, userId.c_str(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        string storedPassword = columnText(stmt, 0);
        sqlite3_finalize(stmt);
        return PasswordUtils::verifyPassword(password, storedPassword);
    }
    sqlite3_finalize(stmt);
    return false;
}