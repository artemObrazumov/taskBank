#ifndef CONTROLWORKMETADATAEDITOR_H
#define CONTROLWORKMETADATAEDITOR_H

#include "models/controlwork.h"

class ControlWorkMetadataEditor
{
public:
    ControlWorkMetadataEditor();

    void validateControlWork(ControlWork &work);
    bool createControlWorkMetadata(std::string title, std::string path);
};

#endif // CONTROLWORKMETADATAEDITOR_H
