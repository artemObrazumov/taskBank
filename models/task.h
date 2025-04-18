#ifndef TASK_H
#define TASK_H

#include "models/Tag.h"
#include <string>

struct Task {
    int id;
    std::string content;
    std::string answer;
    std::vector<Tag> tags;

    Task(int id, std::string content, std::string answer): id(id), content(content), answer(answer) {}
    Task(int id, std::string content, std::string answer, std::vector<Tag> tags): id(id), content(content),
        answer(answer), tags(tags) {}
};

#endif
