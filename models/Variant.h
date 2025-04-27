#ifndef VARIANT_H
#define VARIANT_H

#include "models/taskgroup.h"

struct Variant {
    int id;
    int index;
    std::vector<TaskGroup> groups;

    Variant(int id, int index): id(id), index(index) {}
};

#endif // VARIANT_H
