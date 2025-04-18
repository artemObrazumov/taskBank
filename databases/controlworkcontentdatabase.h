#ifndef CONTROLWORKCONTENTDATABASE_H
#define CONTROLWORKCONTENTDATABASE_H

#include "databases/controlworkdatabase.h"
#include "models/taskgroup.h"

class ControlWorkContentDatabase
{
private:

    sqlite3* database;
public:

    ControlWorkContentDatabase(ControlWork &work);
    ~ControlWorkContentDatabase();

    std::vector<TaskGroup> getTaskGroupsFromDatabase(int id, bool getTags = true);
    std::vector<Tag> getTaskTagsFromDatabase(int id, bool getTags = true);
    Task* getTaskFromDatabase(int id, bool getTags = true);
    int addTaskGroupToDatabase();
    int addTaskToDatabase(int groupId);
    void deleteTaskFromDatabase(int id);
};

#endif // CONTROLWORKCONTENTDATABASE_H
