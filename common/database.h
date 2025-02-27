#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>

class Database {
public:
    Database(const std::string& dbName);
    ~Database();
    sqlite3* sqliteptr;

private:
    void open();
    void close();
    std::string dbName;
};

#endif // DATABASE_H
