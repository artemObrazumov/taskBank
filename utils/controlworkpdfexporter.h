#ifndef CONTROLWORKPDFEXPORTER_H
#define CONTROLWORKPDFEXPORTER_H

#include "models/controlwork.h"
#include "models/taskgroup.h"
#include <hpdf.h>

class ControlWorkPdfExporter
{

private:

    std::string outputPath;

public:
    ControlWorkPdfExporter(ControlWork work);
    int exportVariant(int id, std::vector<TaskGroup> groups, std::string title);
    int exportAnswers(int id, std::vector<TaskGroup> groups, std::string title);
};

#endif // CONTROLWORKPDFEXPORTER_H
