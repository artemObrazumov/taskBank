#ifndef TAG_H
#define TAG_H

#include <string>

struct Tag {
    int id;
    std::string name;

    Tag(int id, std::string name) : id(id), name(name) {}
};

#endif // TAG_H
