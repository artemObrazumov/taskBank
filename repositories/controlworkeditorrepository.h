#ifndef CONTROLWORKEDITORREPOSITORY_H
#define CONTROLWORKEDITORREPOSITORY_H

#include <sqlite3.h>
#include "../models/controlwork.h"

class controlWorkEditorRepository
{
private:

    sqlite3* database;
    ControlWork* work;
    int workId;

    void loadControlWork();
    std::string loadControlWorkPath();
    void loadMetadata();
public:

    controlWorkEditorRepository(int workId);
    ~controlWorkEditorRepository();
};

#endif // CONTROLWORKEDITORREPOSITORY_H
