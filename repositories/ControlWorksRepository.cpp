#include "ControlWorksRepository.h"
#include <iostream>
#include <sqlite3.h>
#include <filesystem>

ControlWorksRepository::ControlWorksRepository(): db(Database("control_works")) {}
ControlWorksRepository::~ControlWorksRepository() {}

std::vector<ControlWork> ControlWorksRepository::getControlWorks() {
    const char* sql = "SELECT * FROM control_works";
    sqlite3_stmt* stmt;
    std::vector<ControlWork> works;

    for (int i = 0; i < 60; ++i) {
        works.emplace_back(ControlWork(i , "test " + std::to_string(i), 100, 2));
    }
    if (sqlite3_prepare(this->db.sqliteptr, sql, 0, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            const char* name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            const char* email = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            //works.emplace_back(1 , "test", 100, 2);
        }
    } else {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(this->db.sqliteptr) << std::endl;
    }

    sqlite3_finalize(stmt);
    return works;
}

unsigned int ControlWorksRepository::createControlWork(std::string title, std::string path) {
    std::string projectFolderPath = path + "/"  + title;
    std::cout << projectFolderPath << std::endl;
    try {
        bool created = std::filesystem::create_directory(projectFolderPath);
        if (!created) {
            std::cerr << "Directory already exists or could not be created." << std::endl;
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 1;
}
