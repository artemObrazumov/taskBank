#include "controlworkmetadataeditor.h"
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include "../Constants.h"

ControlWorkMetadataEditor::ControlWorkMetadataEditor() {}

void ControlWorkMetadataEditor::validateControlWork(ControlWork &work) {
    std::string metadataPath = work.path + "/" + work.title + "/" + METADATA_FILE_NAME;

    std::ifstream file(metadataPath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for reading." << std::endl;
        work.isValid = false;
        return;
    }
    nlohmann::json data;
    file >> data;

    work.title = data["title"];
    work.tasks = data["tasks"];
    work.variants = data["variants"];
    work.lastEdited = data["lastEdited"];
    work.isValid = true;
}

bool ControlWorkMetadataEditor::createControlWorkMetadata(std::string title, std::string path) {
    std::string projectFolderPath = path + "/" + title;
    try {
        bool created = std::filesystem::create_directory(projectFolderPath);
        if (!created) {
            std::cerr << "Directory already exists or could not be created." << std::endl;
            return false;
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }

    nlohmann::json metadata;
    metadata["title"] = title;
    metadata["tasks"] = 0;
    metadata["variants"] = 0;
    metadata["lastEdited"] = static_cast<long>(std::time(nullptr));

    std::string metadataPath = projectFolderPath + "/" + METADATA_FILE_NAME;
    std::ofstream file(metadataPath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for writing." << std::endl;
        return false;
    }
    file << metadata.dump(4);
    file.close();

    return true;
}
