#ifndef TASKGROUP_H
#define TASKGROUP_H

#include "models/task.h"

struct TaskGroup {
    int id;
    int index;
    std::vector<Task> tasks;

    TaskGroup(int id, int index): id(id), index(index) {}
    TaskGroup(int id, int index, std::vector<Task> tasks): id(id), index(index), tasks(tasks) {}
};

#endif // TASKGROUP_H
