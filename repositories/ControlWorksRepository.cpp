#include "ControlWorksRepository.h"
#include <iostream>
#include <sqlite3.h>
#include <filesystem>
#include <nlohmann/json.hpp>
#include <fstream>
#include <chrono>

ControlWorksRepository::ControlWorksRepository() {
    const std::string a = "control_works.db";
    sqlite3_open(a.c_str(), &database);
    const char* sql = "CREATE TABLE IF NOT EXISTS control_works (id INTEGER PRIMARY KEY AUTOINCREMENT, title TEXT, path TEXT)";
    sqlite3_exec(database, sql, nullptr, nullptr, nullptr);
}

ControlWorksRepository::~ControlWorksRepository() {
    sqlite3_close(reinterpret_cast<sqlite3*>(database));
    database = nullptr;
}

std::vector<ControlWork> ControlWorksRepository::getControlWorks() {

    sqlite3_exec(database, "BEGIN TRANSACTION;", nullptr, nullptr, nullptr);
    const char* sql = "SELECT * FROM control_works;";
    sqlite3_stmt* stmt;
    std::vector<ControlWork> works;

    if (sqlite3_prepare_v2(database, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            const unsigned char* title = sqlite3_column_text(stmt, 1);
            const unsigned char* path = sqlite3_column_text(stmt, 2);
            ControlWork work = ControlWork(id, reinterpret_cast<const char*>(title), reinterpret_cast<const char*>(path));
            validateControlWork(work);
            works.emplace_back(work);
        }
    } else {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(database) << std::endl;
    }

    sqlite3_exec(database, "COMMIT;", nullptr, nullptr, nullptr);
    sqlite3_finalize(stmt);
    return works;
}

unsigned int ControlWorksRepository::createControlWork(std::string title, std::string path) {

    std::string projectFolderPath = path + "/" + title;
    try {
        bool created = std::filesystem::create_directory(projectFolderPath);
        if (!created) {
            std::cerr << "Directory already exists or could not be created." << std::endl;
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    nlohmann::json metadata;
    metadata["title"] = title;
    metadata["tasks"] = 0;
    metadata["variants"] = 0;
    metadata["lastEdited"] = static_cast<long>(std::time(nullptr));

    std::string metadataPath = projectFolderPath + "/metadata.json";
    std::ofstream file(metadataPath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for writing." << std::endl;
        return 1;
    }
    file << metadata.dump(4);
    file.close();

    const char* sql = "INSERT INTO control_works (title, path) VALUES (?, ?);";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(database, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, title.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, path.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "Execution failed: " << sqlite3_errmsg(database) << std::endl;
        }
    } else {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(database) << std::endl;
    }

    sqlite3_finalize(stmt);

    return 1;
}

void ControlWorksRepository::validateControlWork(ControlWork &work) {
    std::string metadataPath = work.path + "/" + work.title + "/metadata.json";

    std::ifstream file(metadataPath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for reading." << std::endl;
        work.isValid = false;
        return;
    }
    nlohmann::json data;
    file >> data;

    work.title = data["title"];
    work.tasks = data["tasks"];
    work.variants = data["variants"];
    work.lastEdited = data["lastEdited"];
    work.isValid = true;
}

void ControlWorksRepository::updateControlWorkTitle(int id, std::string newTitle) {
    const char* sql = "UPDATE control_works SET title = ? WHERE id = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(database, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 0, newTitle.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 1, id);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "Execution failed: " << sqlite3_errmsg(database) << std::endl;
        }
    } else {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(database) << std::endl;
    }

    sqlite3_finalize(stmt);
}
