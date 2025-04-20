#include "controlworkcontentdatabase.h"
#include "Constants.h"
#include <iostream>

ControlWorkContentDatabase::ControlWorkContentDatabase(ControlWork &work) {
    sqlite3_open((work.path + "/" + work.title + "/" + CONTROL_WORK_CONTENT_DATABASE).c_str(), &database);
    const char* sql = R"(
        CREATE TABLE task_groups (id INTEGER PRIMARY KEY AUTOINCREMENT);
        CREATE TABLE tasks (id INTEGER PRIMARY KEY AUTOINCREMENT, groupId INTEGER NOT NULL,content TEXT NOT NULL,answer TEXT NOT NULL,FOREIGN KEY (groupId) REFERENCES task_groups(id) ON DELETE CASCADE);
        CREATE TABLE tags (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT NOT NULL UNIQUE);
        CREATE TABLE task_tags (taskId INTEGER NOT NULL, tagId INTEGER NOT NULL, PRIMARY KEY (taskId, tagId), FOREIGN KEY (taskId) REFERENCES tasks(id) ON DELETE CASCADE, FOREIGN KEY (tagId) REFERENCES tags(id) ON DELETE CASCADE);
        INSERT INTO tags(name) VALUES ("Простое");
        INSERT INTO tags(name) VALUES ("Средняя сложность");
        INSERT INTO tags(name) VALUES ("Сложное");
    )";
    sqlite3_exec(database, sql, nullptr, nullptr, nullptr);
}

ControlWorkContentDatabase::~ControlWorkContentDatabase() {
    sqlite3_close(reinterpret_cast<sqlite3*>(database));
    database = nullptr;
}

std::vector<TaskGroup> ControlWorkContentDatabase::getTaskGroupsFromDatabase(int id) {
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

            if (content and answer) {
                taskGroups.back().tasks.emplace_back(Task(taskId,
                    reinterpret_cast<const char*>(content), reinterpret_cast<const char*>(answer)));
            }
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

Task* ControlWorkContentDatabase::getTaskFromDatabase(int id) {
    const char* sql = "SELECT * FROM tasks WHERE id = ?;";
    sqlite3_stmt* stmt;
    Task* task = nullptr;

    if (sqlite3_prepare_v2(this->database, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, id);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            const unsigned char* content = sqlite3_column_text(stmt, 2);
            const unsigned char* answer = sqlite3_column_text(stmt, 3);
            task = new Task(id, reinterpret_cast<const char*>(content), reinterpret_cast<const char*>(answer));
        }
    } else {
        std::cerr << "Ошибка: " << sqlite3_errmsg(database) << std::endl;
    }

    sqlite3_finalize(stmt);
    return task;
}

void ControlWorkContentDatabase::deleteTaskFromDatabase(int id) {
    const char* sql = "DELETE FROM tasks WHERE id = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(this->database, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, id);
        sqlite3_step(stmt);
    } else {
        std::cerr << "Ошибка: " << sqlite3_errmsg(database) << std::endl;
    }

    sqlite3_finalize(stmt);
}

std::vector<Tag> ControlWorkContentDatabase::getTaskTagsFromDatabase(int id) {
    const char* sql = R"(
        SELECT tags.id, tags.name FROM tasks
        INNER JOIN task_tags ON task_tags.taskId = tasks.id
        INNER JOIN tags ON tags.id = task_tags.tagId
        WHERE tasks.id = ?;
    )";
    sqlite3_stmt* stmt;
    std::vector<Tag> tags;

    if (sqlite3_prepare_v2(this->database, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, id);
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            const unsigned char* name = sqlite3_column_text(stmt, 1);
            tags.emplace_back(Tag(id, reinterpret_cast<const char*>(name)));
        }
    } else {
        std::cerr << "Ошибка: " << sqlite3_errmsg(database) << std::endl;
    }

    sqlite3_finalize(stmt);
    return tags;
}

std::vector<Tag> ControlWorkContentDatabase::getAllTagsFromDatabase() {
    const char* sql = "SELECT * FROM tags";
    sqlite3_stmt* stmt;
    std::vector<Tag> tags;

    if (sqlite3_prepare_v2(this->database, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            const unsigned char* name = sqlite3_column_text(stmt, 1);
            tags.emplace_back(Tag(id, reinterpret_cast<const char*>(name)));
        }
    } else {
        std::cerr << "Ошибка: " << sqlite3_errmsg(database) << std::endl;
    }

    sqlite3_finalize(stmt);
    return tags;
}

void ControlWorkContentDatabase::saveTaskToDatabase(int taskId, std::string content, std::string answer) {
    const char* sql = "UPDATE tasks SET content = ?, answer = ? WHERE id = ?";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(this->database, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, content.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, answer.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 3, taskId);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "Ошибка: " << sqlite3_errmsg(this->database) << std::endl;
        }
    }

    sqlite3_finalize(stmt);
}

Tag* ControlWorkContentDatabase::getTagFromDatabase(int tagId) {
    const char* sql = "SELECT * FROM tags WHERE id = ?";
    sqlite3_stmt* stmt;
    Tag* tag = nullptr;

    if (sqlite3_prepare_v2(this->database, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, tagId);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            const unsigned char* name = sqlite3_column_text(stmt, 1);
            tag = new Tag(id, reinterpret_cast<const char*>(name));
        }
    } else {
        std::cerr << "Ошибка: " << sqlite3_errmsg(database) << std::endl;
    }

    sqlite3_finalize(stmt);
    return tag;
}

int ControlWorkContentDatabase::createTagInDatabase(std::string title) {
    const char* sql = "INSERT INTO tags (name) VALUES (?)";
    sqlite3_stmt* stmt;
    int id = -1;

    if (sqlite3_prepare_v2(database, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, title.c_str(), -1, SQLITE_STATIC);

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

void ControlWorkContentDatabase::deleteTaskTags(int taskId) {
    const char* sql = "DELETE FROM task_tags WHERE taskId = ?";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(database, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, taskId);
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "Ошибка: " << sqlite3_errmsg(database) << std::endl;
        }
    } else {
        std::cerr << "Ошибка: " << sqlite3_errmsg(database) << std::endl;
    }

    sqlite3_finalize(stmt);
}

void ControlWorkContentDatabase::saveTaskTag(int taskId, int tagId) {
    const char* sql = "INSERT INTO task_tags (taskId, tagId) VALUES (?, ?)";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(database, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, taskId);
        sqlite3_bind_int(stmt, 2, tagId);
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "Ошибка: " << sqlite3_errmsg(database) << std::endl;
        }
    } else {
        std::cerr << "Ошибка: " << sqlite3_errmsg(database) << std::endl;
    }

    sqlite3_finalize(stmt);
}
