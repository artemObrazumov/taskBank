#include "controlworkeditorrepository.h"

controlWorkEditorRepository::controlWorkEditorRepository(int workId): workId(workId) {
    loadControlWork();
}

void controlWorkEditorRepository::loadControlWork() {
    this->work = database.getControlWorkFromDatabase(this->workId);
    metadataEditor.validateControlWork(*this->work);
    content = new ControlWorkContentDatabase(*this->work);
    groups = content->getTaskGroupsFromDatabase();
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
