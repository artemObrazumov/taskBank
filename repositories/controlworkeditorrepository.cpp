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
