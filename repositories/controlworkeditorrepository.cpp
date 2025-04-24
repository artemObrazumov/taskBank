#include "controlworkeditorrepository.h"

controlWorkEditorRepository::controlWorkEditorRepository(int workId): workId(workId) {
    loadControlWork();
}

void controlWorkEditorRepository::loadControlWork() {
    this->work = database.getControlWorkFromDatabase(this->workId);
    controlWorkPdfExporter = new ControlWorkPdfExporter(*this->work);
    metadataEditor.validateControlWork(*this->work);
    content = new ControlWorkContentDatabase(*this->work);
    groups = content->getTaskGroupsFromDatabase(this->work->id);
    tags = content->getAllTagsFromDatabase();
}

int controlWorkEditorRepository::addTaskGroup() {
    int id = content->addTaskGroupToDatabase();
    if(metadataEditor.incrementTaskCount(*this->work)) {
        return id;
    } else {
        return -1;
    }
}

int controlWorkEditorRepository::addTask(int groupId) {
    return content->addTaskToDatabase(groupId);
}

Task* controlWorkEditorRepository::getTaskById(int id) {
    return content->getTaskFromDatabase(id);
}

void controlWorkEditorRepository::deleteTask(int id) {
    content->deleteTaskFromDatabase(id);
}

void controlWorkEditorRepository::saveTask(int taskId, std::string content, std::string answer) {
    this->content->saveTaskToDatabase(taskId, content, answer);
}

Tag* controlWorkEditorRepository::getTagById(int tagId) {
    return content->getTagFromDatabase(tagId);
}

int controlWorkEditorRepository::createTag(std::string title) {
    return content->createTagInDatabase(title);
}

void controlWorkEditorRepository::deleteTaskTags(int taskId) {
    content->deleteTaskTags(taskId);
}

void controlWorkEditorRepository::saveTaskTag(int taskId, int tagId) {
    content->saveTaskTag(taskId, tagId);
}

std::vector<Tag> controlWorkEditorRepository::getTaskTags(int taskId) {
    return content->getTaskTagsFromDatabase(taskId);
}

std::vector<TaskGroup> controlWorkEditorRepository::getNotEmptyTaskGroups() {
    return content->getNotEmptyTaskGroups();
}

std::vector<Tag> controlWorkEditorRepository::getNotEmptyTaskTags() {
    return content->getNotEmptyTaskTags();
}

// Результаты:
// 0 - ОК
// -1 - Вариант собрался, но набор заданий неполный
// -2 - Некоторые варианты не смогли собраться
int controlWorkEditorRepository::generateAndSaveVariants(std::vector<int> groups, std::vector<int> tags, int variants, std::string title) {
    int result = 0;
    for(int i = 0; i < variants; ++i) {
        std::vector<TaskGroup> taskGroups = content->getRandomTasksFromGroups(groups, tags);
        if (taskGroups.size() < groups.size()) {
            if (result > -1) result = -1;
        }
        if (taskGroups.size() == 0) {
            if (result > -2) result = -2;
        } else {
            int variantId = content->saveVariant(taskGroups);
            controlWorkPdfExporter->exportVariant(variantId, taskGroups, title);
            controlWorkPdfExporter->exportAnswers(variantId, taskGroups, title);
        }
    }
    return result;
}
