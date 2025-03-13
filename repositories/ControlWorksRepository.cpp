#include "ControlWorksRepository.h"
#include <iostream>
#include <sqlite3.h>
#include <filesystem>
#include "../Constants.h"

ControlWorksRepository::ControlWorksRepository() {}

ControlWorksRepository::~ControlWorksRepository() {}

std::vector<ControlWork> ControlWorksRepository::getControlWorks() {

    std::vector<ControlWork> works = this->database.getControlWorksFromDatabase();
    for(auto start{works.begin()}; start != works.end(); start++ ) {
        this->metadataEditor.validateControlWork(*start);
    }
    return works;
}

unsigned int ControlWorksRepository::createControlWork(std::string title, std::string path) {

    int id = -1;

    if (this->metadataEditor.createControlWorkMetadata(title, path)) {
        id = this->database.createControlWork(title, path);
    }

    return id;
}

// void ControlWorksRepository::updateControlWorkTitle(int id, std::string newTitle) {
//     const char* sql = "UPDATE control_works SET title = ? WHERE id = ?;";
//     sqlite3_stmt* stmt;

//     if (sqlite3_prepare_v2(database, sql, -1, &stmt, nullptr) == SQLITE_OK) {
//         sqlite3_bind_text(stmt, 0, newTitle.c_str(), -1, SQLITE_STATIC);
//         sqlite3_bind_int(stmt, 1, id);

//         if (sqlite3_step(stmt) != SQLITE_DONE) {
//             std::cerr << "Execution failed: " << sqlite3_errmsg(database) << std::endl;
//         }
//     } else {
//         std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(database) << std::endl;
//     }

//     sqlite3_finalize(stmt);
// }
