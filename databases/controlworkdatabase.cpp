#include "controlworkdatabase.h"
#include <iostream>
#include <sqlite3.h>
#include "../models/controlwork.h"
#include "../Constants.h"

ControlWorkDatabase::ControlWorkDatabase() {
    sqlite3_open(CONTROL_WORKS_DATABASE.c_str(), &database);
    const char* sql = "CREATE TABLE IF NOT EXISTS control_works (id INTEGER PRIMARY KEY AUTOINCREMENT, title TEXT, path TEXT)";
    sqlite3_exec(database, sql, nullptr, nullptr, nullptr);
}

ControlWorkDatabase::~ControlWorkDatabase() {
    sqlite3_close(reinterpret_cast<sqlite3*>(database));
    database = nullptr;
}

ControlWork* ControlWorkDatabase::getControlWorkFromDatabase(int id) {
    const char* sql = "SELECT * FROM control_works WHERE id = ?;";
    sqlite3_stmt* stmt;
    ControlWork* work = nullptr;

    if (sqlite3_prepare_v2(this->database, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, id);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            const unsigned char* title = sqlite3_column_text(stmt, 1);
            const unsigned char* path = sqlite3_column_text(stmt, 2);
            work = new ControlWork(id, reinterpret_cast<const char*>(title), reinterpret_cast<const char*>(path));
        }
    } else {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(database) << std::endl;
    }

    sqlite3_finalize(stmt);
    return work;
}

std::vector<ControlWork> ControlWorkDatabase::getControlWorksFromDatabase() {

    const char* sql = "SELECT * FROM control_works;";
    sqlite3_stmt* stmt;
    std::vector<ControlWork> works;

    if (sqlite3_prepare_v2(this->database, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            const unsigned char* title = sqlite3_column_text(stmt, 1);
            const unsigned char* path = sqlite3_column_text(stmt, 2);
            ControlWork work = ControlWork(id, reinterpret_cast<const char*>(title), reinterpret_cast<const char*>(path));
            works.emplace_back(work);
        }
    } else {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(database) << std::endl;
    }

    sqlite3_finalize(stmt);
    return works;
}

int ControlWorkDatabase::createControlWork(std::string title, std::string path) {
    const char* sql = "INSERT INTO control_works (title, path) VALUES (?, ?);";
    sqlite3_stmt* stmt;
    int id = -1;

    if (sqlite3_prepare_v2(database, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, title.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, path.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "Execution failed: " << sqlite3_errmsg(database) << std::endl;
        } else {
            id = sqlite3_last_insert_rowid(database);
        }
    } else {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(database) << std::endl;
    }

    sqlite3_finalize(stmt);

    return id;
}
