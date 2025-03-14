#ifndef CONTROLWORK_H
#define CONTROLWORK_H

#include <string>

struct ControlWork
{
    int id;
    std::string title;
    int tasks;
    int variants;
    std::string path;
    long lastEdited;

    ControlWork(int id, const std::string& title, int tasks, int variants, const std::string& path, long lastEdited)
        : id(id), title(title), tasks(tasks), variants(variants), path(path), lastEdited(lastEdited) {}

    ControlWork(int id, const std::string& title, const std::string& path)
        : id(id), title(title), path(path) {}

    ControlWork(std::string title, std::string path)
        : title(title), path(path) {}

    bool isValid;
};

#endif
