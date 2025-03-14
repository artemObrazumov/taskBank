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
    ControlWorkContentDatabase content;
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
};

#endif // CONTROLWORKEDITORREPOSITORY_H
