#ifndef CONTROLWORKSREPOSITORY_H
#define CONTROLWORKSREPOSITORY_H

#include <sqlite3.h>
#include "../models/controlwork.h"

class ControlWorksRepository {
private:
    sqlite3* database;
public:

    ControlWorksRepository();
    ~ControlWorksRepository();

    std::vector<ControlWork> getControlWorks();
    unsigned int createControlWork(std::string title, std::string path);
    void validateControlWork(ControlWork &work);
    void updateControlWorkTitle(int id, std::string newTitle);
};

#endif // CONTROLWORKSREPOSITORY_H
