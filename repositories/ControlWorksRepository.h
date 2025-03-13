#ifndef CONTROLWORKSREPOSITORY_H
#define CONTROLWORKSREPOSITORY_H

#include "../models/controlwork.h"
#include "databases/controlworkdatabase.h"
#include "utils/controlworkmetadataeditor.h"

class ControlWorksRepository {
private:

    ControlWorkDatabase database;
    ControlWorkMetadataEditor metadataEditor;
public:

    ControlWorksRepository();
    ~ControlWorksRepository();

    std::vector<ControlWork> getControlWorks();
    unsigned int createControlWork(std::string title, std::string path);
    void updateControlWorkTitle(int id, std::string newTitle);
};

#endif // CONTROLWORKSREPOSITORY_H
