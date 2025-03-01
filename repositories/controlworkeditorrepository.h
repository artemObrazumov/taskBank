#ifndef CONTROLWORKEDITORREPOSITORY_H
#define CONTROLWORKEDITORREPOSITORY_H

#include <sqlite3.h>
#include "../models/controlwork.h"

class controlWorkEditorRepository
{
private:
    sqlite3* database;
    ControlWork* openedWork;
    int workId;

    void loadControlWork();
public:

    controlWorkEditorRepository();
    ~controlWorkEditorRepository();

    void initializeRepository(int id);
};

#endif // CONTROLWORKEDITORREPOSITORY_H
