#include "database.h"
#include <iostream>
#include <sqlite3.h>

Database::Database(const std::string& dbName) : dbName(dbName) {}

Database::~Database() {
    close();
}

void Database::open() {
    if (sqlite3_open(dbName.c_str(), reinterpret_cast<sqlite3**>(&sqliteptr)) != SQLITE_OK) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(reinterpret_cast<sqlite3*>(sqliteptr)) << std::endl;
        return;
    }
    std::cout << "Opened database: " << dbName << std::endl;
}

void Database::close() {
    if (sqliteptr) {
        sqlite3_close(reinterpret_cast<sqlite3*>(sqliteptr));
        sqliteptr = nullptr;
    }
}
