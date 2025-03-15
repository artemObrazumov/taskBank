#include "controlworkmetadataeditor.h"
#include <iostream>
#include <nlohmann/json.hpp>
#include "../Constants.h"

ControlWorkMetadataEditor::ControlWorkMetadataEditor() {}

bool ControlWorkMetadataEditor::writableMetadataFile(ControlWork &work, std::ofstream &file) {
    std::string metadataPath = work.path + "/" + work.title + "/" + METADATA_FILE_NAME;
    file.open(metadataPath);
    if (!file.is_open()) {
        std::cerr << "Ошибка при открытии файла " << metadataPath << std::endl;
        return false;
    }
    work.isValid = true;
    return true;
}

bool ControlWorkMetadataEditor::readableMetadataFile(ControlWork &work, std::ifstream &file) {
    std::string metadataPath = work.path + "/" + work.title + "/" + METADATA_FILE_NAME;
    file.open(metadataPath);
    if (!file.is_open()) {
        std::cerr << "Ошибка при открытии файла " << metadataPath << std::endl;
        work.isValid = false;
        return false;
    }
    return true;
}

void ControlWorkMetadataEditor::validateControlWork(ControlWork &work) {
    std::ifstream file;
    if (readableMetadataFile(work, file) == false) {
        return;
    }
    nlohmann::json metadata;
    file >> metadata;
    file.close();

    work.title = metadata["title"];
    work.tasks = metadata["tasks"];
    work.variants = metadata["variants"];
    work.lastEdited = metadata["lastEdited"];
    work.isValid = true;
}

bool ControlWorkMetadataEditor::createControlWorkMetadata(std::string title, std::string path) {
    std::string projectFolderPath = path + "/" + title;
    try {
        bool created = std::filesystem::create_directory(projectFolderPath);
        if (!created) {
            std::cerr << "Ошибка при создании директории " << projectFolderPath << std::endl;
            return false;
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return false;
    }

    nlohmann::json metadata;
    metadata["title"] = title;
    metadata["tasks"] = 0;
    metadata["variants"] = 0;
    metadata["lastEdited"] = static_cast<long>(std::time(nullptr));

    std::ofstream file;
    ControlWork work(title, path);
    writableMetadataFile(work, file);
    file << metadata.dump(4);
    file.close();

    return true;
}

bool ControlWorkMetadataEditor::incrementTaskCount(ControlWork &work) {
    std::ifstream readableFile;
    readableMetadataFile(work, readableFile);
    nlohmann::json metadata;
    readableFile >> metadata;
    readableFile.close();

    std::cout << metadata["tasks"] << std::endl;
    metadata["tasks"] = metadata["tasks"].get<int>() + 1;
    std::cout << metadata["tasks"] << std::endl;

    std::ofstream writableFile;
    writableMetadataFile(work, writableFile);
    writableFile << metadata.dump(4);
    writableFile.close();

    return true;
}
