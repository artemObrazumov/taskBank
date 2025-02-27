#ifndef CONTROLWORK_H
#define CONTROLWORK_H

#include <string>

struct ControlWork
{
    int id;
    std::string title;
    int tasks;
    int variants;

    ControlWork(int id, const std::string& title, int tasks, int variants)
        : id(id), title(title), tasks(tasks), variants(variants) {}
};

#endif
