#include "controlworkcontentdatabase.h"
#include "Constants.h"
#include <iostream>

ControlWorkContentDatabase::ControlWorkContentDatabase() {
    sqlite3_open(CONTROL_WORK_CONTENT_DATABASE.c_str(), &database);
    const char* sql = "CREATE TABLE task_groups (id INTEGER PRIMARY KEY AUTOINCREMENT); CREATE TABLE tasks (id INTEGER PRIMARY KEY AUTOINCREMENT, groupId INTEGER NOT NULL,content TEXT NOT NULL,answer TEXT NOT NULL,FOREIGN KEY (groupId) REFERENCES task_groups(id) ON DELETE CASCADE);";
    sqlite3_exec(database, sql, nullptr, nullptr, nullptr);
}

ControlWorkContentDatabase::~ControlWorkContentDatabase() {
    sqlite3_close(reinterpret_cast<sqlite3*>(database));
    database = nullptr;
}

std::vector<TaskGroup> ControlWorkContentDatabase::getTaskGroupsFromDatabase() {
    const char* sql = R"(
        SELECT groups.id AS group_id,
            tasks.id AS task_id, tasks.content, tasks.answer
        FROM task_groups groups
        LEFT JOIN tasks ON groups.id = tasks.groupId
        ORDER BY groups.id;
    )";

    sqlite3_stmt* stmt;
    std::vector<TaskGroup> taskGroups;
    int lastGroupId = -1;
    int index = 0;

    if (sqlite3_prepare_v2(database, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int groupId = sqlite3_column_int(stmt, 0);
            int taskId = sqlite3_column_int(stmt, 1);
            const unsigned char* content = sqlite3_column_text(stmt, 2);
            const unsigned char* answer = sqlite3_column_text(stmt, 3);

            if (groupId != lastGroupId) {
                index++;
                taskGroups.emplace_back(TaskGroup(groupId, index));
                lastGroupId = groupId;
            }

            taskGroups.back().tasks.emplace_back(Task(taskId,
                reinterpret_cast<const char*>(content), reinterpret_cast<const char*>(answer)));
        }
    }

    return taskGroups;
}

int ControlWorkContentDatabase::addTaskGroupToDatabase() {
    const char* sql = "INSERT INTO task_groups DEFAULT VALUES";
    sqlite3_stmt* stmt;
    int id = -1;

    if (sqlite3_prepare_v2(database, sql, -1, &stmt, nullptr) == SQLITE_OK) {

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "Ошибка: " << sqlite3_errmsg(database) << std::endl;
        } else {
            id = sqlite3_last_insert_rowid(database);
        }
    } else {
        std::cerr << "Ошибка: " << sqlite3_errmsg(database) << std::endl;
    }

    sqlite3_finalize(stmt);
    return id;
}

int ControlWorkContentDatabase::addTaskToDatabase(int groupId) {
    const char* sql = "INSERT INTO tasks (groupId, content, answer) VALUES (?, '', '')";
    sqlite3_stmt* stmt;
    int id = -1;

    if (sqlite3_prepare_v2(database, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, groupId);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "Ошибка: " << sqlite3_errmsg(database) << std::endl;
        } else {
            id = sqlite3_last_insert_rowid(database);
        }
    } else {
        std::cerr << "Ошибка: " << sqlite3_errmsg(database) << std::endl;
    }

    sqlite3_finalize(stmt);
    return id;
}

// Task* ControlWorkContentDatabase::getTaskFromDatabase(int id) {

// }
