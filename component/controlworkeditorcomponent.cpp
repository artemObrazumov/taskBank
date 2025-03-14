#include "controlworkeditorcomponent.h"

ControlWorkEditorComponent::ControlWorkEditorComponent() {}

ControlWorkEditorComponent::~ControlWorkEditorComponent() {}

void ControlWorkEditorComponent::componentComplete() {
    componentComplete();
    loadControlWork();
}

void ControlWorkEditorComponent::loadControlWork() {
    if (repository == nullptr) {
        repository = new controlWorkEditorRepository(_workId);
    }

    ControlWork* work = repository->getControlWork();
    _controlWork["title"] = QString::fromStdString(work->title);
    emit controlWorkChanged();

    std::vector<TaskGroup> groups = repository->getTaskGroups();
    QList<QVariantMap> groupsMap;
    for(auto group{groups.begin()}; group != groups.end(); group++ ) {
        QVariantMap groupMap;
        groupMap["id"] = group->id;
        groupMap["index"] = group->index;
        groupMap["show"] = false;
        QList<QVariantMap> tasks;
        for(auto task{group->tasks.begin()}; task != group->tasks.end(); task++ ) {
            QVariantMap taskMap;
            taskMap["taskId"] = task->id;
            taskMap["content"] = QString::fromStdString(task->content);
            taskMap["answer"] = QString::fromStdString(task->answer);
            tasks.append(taskMap);
        }
        groupMap["taskVariants"] = QVariant::fromValue(tasks);
        groupsMap.append(groupMap);
    }
    _taskGroups = groupsMap;
    emit taskGroupsChanged();
}

Q_INVOKABLE void ControlWorkEditorComponent::toggleGroupShow(int groupId) {
    for (int i = 0; i < _taskGroups.size(); ++i) {
        if (_taskGroups[i]["id"] == groupId) {
            _taskGroups[i]["show"] = _taskGroups[i]["show"] == false;
            emit taskGroupsChanged();
            break;
        }
    }
}
