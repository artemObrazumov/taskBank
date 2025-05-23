#include "ControlWorksRepository.h"
#include <iostream>
#include <sqlite3.h>
#include <filesystem>
#include "../Constants.h"

ControlWorksRepository::ControlWorksRepository() {}

ControlWorksRepository::~ControlWorksRepository() {}

std::vector<ControlWork> ControlWorksRepository::getControlWorks() {

    std::vector<ControlWork> works = this->database.getControlWorksFromDatabase();
    for(auto start{works.begin()}; start != works.end(); start++ ) {
        this->metadataEditor.validateControlWork(*start);
    }
    return works;
}

ControlWork* ControlWorksRepository::getControlWork(int id) {
    return this->database.getControlWorkFromDatabase(id);
}

unsigned int ControlWorksRepository::createControlWork(std::string title, std::string path) {

    int id = -1;

    if (this->metadataEditor.createControlWorkMetadata(title, path)) {
        id = this->database.createControlWork(title, path);
    }

    return id;
}

unsigned int ControlWorksRepository::addControlWork(std::string title, std::string path) {
    return this->database.createControlWork(title, path);
}
