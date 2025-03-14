#ifndef TASK_H
#define TASK_H

#include <string>

struct Task {
    int id;
    std::string content;
    std::string answer;

    Task(int id, std::string content, std::string answer): id(id), content(content), answer(answer) {}
};

#endif
