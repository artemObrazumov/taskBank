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

    std::vector<TaskGroup> getTaskGroupsFromDatabase();
    Task* getTaskFromDatabase(int id);
    int addTaskGroupToDatabase();
    int addTaskToDatabase(int groupId);
};

#endif // CONTROLWORKCONTENTDATABASE_H
