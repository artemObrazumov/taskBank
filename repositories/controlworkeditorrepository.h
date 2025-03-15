#ifndef CONTROLWORKEDITORREPOSITORY_H
#define CONTROLWORKEDITORREPOSITORY_H

#include <sqlite3.h>
#include "../models/controlwork.h"
#include "databases/controlworkcontentdatabase.h"
#include "databases/controlworkdatabase.h"
#include "models/taskgroup.h"
#include "utils/controlworkmetadataeditor.h"

class controlWorkEditorRepository
{
private:

    ControlWorkDatabase database;
    ControlWorkContentDatabase* content = nullptr;
    ControlWorkMetadataEditor metadataEditor;
    ControlWork* work;
    std::vector<TaskGroup> groups;
    int workId;

    void loadControlWork();
public:

    controlWorkEditorRepository(int workId);
    ~controlWorkEditorRepository();

    int addTaskGroup();
    int addTask(int groupId);
    Task* getTaskById(int id);
    ControlWork* getControlWork() {
        return work;
    }
    std::vector<TaskGroup> getTaskGroups() {
        return groups;
    }
    void deleteTask(int id);
};

#endif // CONTROLWORKEDITORREPOSITORY_H
