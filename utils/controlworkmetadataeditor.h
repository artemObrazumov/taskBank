#ifndef CONTROLWORKMETADATAEDITOR_H
#define CONTROLWORKMETADATAEDITOR_H

#include "models/controlwork.h"
#include <fstream>

class ControlWorkMetadataEditor
{
private:

    bool writableMetadataFile(ControlWork &work, std::ofstream &file);
    bool readableMetadataFile(ControlWork &work, std::ifstream &file);
public:
    ControlWorkMetadataEditor();

    void validateControlWork(ControlWork &work);
    bool createControlWorkMetadata(std::string title, std::string path);
    bool incrementTaskCount(ControlWork &work);
};

#endif // CONTROLWORKMETADATAEDITOR_H
