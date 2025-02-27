#ifndef CONTROLWORKSREPOSITORY_H
#define CONTROLWORKSREPOSITORY_H

#include <QObject>
#include "../common/database.h"
#include "../models/controlwork.h"

class ControlWorksRepository {
private:
    Database db;
public:
    ControlWorksRepository();
    ~ControlWorksRepository();

    std::vector<ControlWork> getControlWorks();
    unsigned int createControlWork(std::string title, std::string path);
};

#endif // CONTROLWORKSREPOSITORY_H
