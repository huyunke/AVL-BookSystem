#include "DatabaseOperator.h"
#include <iostream>
using namespace std;

DatabaseOperator::DatabaseOperator() {
    database = nullptr;
}

DatabaseOperator::~DatabaseOperator() {
    close();
}

bool DatabaseOperator::open(const string& daPath) {
    int result = sqlite3_open(daPath.c_str(), &database);
    if (result != SQLITE_OK) {
        lastError=sqlite3_errmsg(database);
        //cout<<"打开数据库失败:"<<sqlite3_errmsg(database)<<""<<endl;//后续写入日志
        close();
        return false;
    }
    return true;
}

void DatabaseOperator::close() {
    if (database) {
        sqlite3_close(database);
        database = nullptr;
       // cout<<"数据库已关闭"<<endl;//后续写入日志
    }
}

bool DatabaseOperator::execute(const string& sql) {
    char* errorMessage = nullptr;
    int result = sqlite3_exec(database, sql.c_str(), nullptr, nullptr, &errorMessage);
    if (result != SQLITE_OK) {
        lastError=errorMessage?errorMessage:sqlite3_errmsg(database);
        sqlite3_free(errorMessage);

        //cout<<"执行SQL失败:"<<lastError<<endl;//后续写入日志

        return false;
    }

    //cout<<"执行SQL成功"<<endl;//后续写入日志

    return true;
}

bool DatabaseOperator::query(const string& sql, vector<vector<string>>& result) {
    sqlite3_stmt* statement = nullptr;
    if (!prepare(sql,&statement)) {

        //cout<<"查询SQL失败"<<endl;//后续写入日志

        return false;
    }
    int columnCount = sqlite3_column_count(statement);
    while (sqlite3_step(statement) == SQLITE_ROW) {
        vector<string> row;
        for (int i = 0; i < columnCount; i++) {
            const unsigned char* text=sqlite3_column_text(statement, i);
            row.push_back(text ? reinterpret_cast<const char*>(text):"");
        }
        result.push_back(row);
    }
    sqlite3_finalize(statement);

    //cout<<"查询SQL成功"<<endl;//后续写入日志

    return true;
}

bool DatabaseOperator::prepare(const string& sql,sqlite3_stmt** statement) {
    int result = sqlite3_prepare_v2(database, sql.c_str(), -1, statement, nullptr);
    if (result != SQLITE_OK) {
        if (*statement) {
            sqlite3_finalize(*statement);
            *statement = nullptr;
        }
        lastError=sqlite3_errmsg(database);

        //cout<<"准备SQL失败:"<<sqlite3_errmsg(database)<<""<<endl;//后续写入日志

        return false;
    }

    //cout<<"准备SQL成功"<<endl;//后续写入日志

    return true;
}

bool DatabaseOperator::beginTransaction() {
    return execute("BEGIN TRANSACTION;");
}

bool DatabaseOperator::commit() {
    return execute("COMMIT;");
}

bool DatabaseOperator::rollback() {
    return execute("ROLLBACK;");
}

string DatabaseOperator::getLastError() const{
    return lastError;
}