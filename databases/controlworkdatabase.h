#ifndef CONTROLWORKDATABASE_H
#define CONTROLWORKDATABASE_H

#include "../models/controlwork.h"
#include <sqlite3.h>

class ControlWorkDatabase
{
private:

    sqlite3* database;
public:

    ControlWorkDatabase();
    ~ControlWorkDatabase();

    ControlWork* getControlWorkFromDatabase(int id);
    std::vector<ControlWork> getControlWorksFromDatabase();
    int createControlWork(std::string title, std::string path);
};

#endif // CONTROLWORKDATABASE_H
