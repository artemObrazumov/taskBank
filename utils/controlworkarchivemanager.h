#ifndef CONTROLWORKARCHIVEMANAGER_H
#define CONTROLWORKARCHIVEMANAGER_H

#include <string>

class ControlWorkArchiveManager
{
public:
    ControlWorkArchiveManager();

    void exportToZip(const std::string& workPath, const std::string& exportPath);
    void importFromZip(const std::string& importPath, const std::string& projectPath);
};

#endif // CONTROLWORKARCHIVEMANAGER_H
