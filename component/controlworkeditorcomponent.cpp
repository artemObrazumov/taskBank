#include "controlworkeditorcomponent.h"

QVariantMap mapFromTask(Task* task) {
    QVariantMap taskMap;
    taskMap["taskId"] = task->id;
    taskMap["content"] = QString::fromStdString(task->content);
    taskMap["answer"] = QString::fromStdString(task->answer);
    return taskMap;
}

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
    for(auto group{groups.begin()}; group != groups.end(); group++ ) {
        QVariantMap groupMap;
        groupMap["id"] = group->id;
        groupMap["index"] = group->index;
        groupMap["show"] = false;
        QList<QVariantMap> tasks;
        for(auto task{group->tasks.begin()}; task != group->tasks.end(); task++ ) {
            tasks.append(mapFromTask(&*task));
        }
        groupMap["taskVariants"] = QVariant::fromValue(tasks);
        _taskGroups.addGroup(groupMap);
    }
}

Q_INVOKABLE void ControlWorkEditorComponent::addTaskGroup() {
    int groupId = repository->addTaskGroup();
    QVariantMap groupMap;
    groupMap["id"] = groupId;
    groupMap["index"] = _taskGroups.rowCount() + 1;
    groupMap["show"] = false;
    QList<QVariantMap> tasks;
    groupMap["taskVariants"] = QVariant::fromValue(tasks);
    _taskGroups.addGroup(groupMap);
}

Q_INVOKABLE void ControlWorkEditorComponent::addTaskToGroup(int groupId) {
    int taskId = repository->addTask(groupId);
    Task* task = repository->getTaskById(taskId);
    _taskGroups.addTaskToGroup(groupId, mapFromTask(task));
}

Q_INVOKABLE void ControlWorkEditorComponent::deleteTask(int groupId, int taskId) {
    repository->deleteTask(taskId);
    _taskGroups.deleteTask(groupId, taskId);
}

Q_INVOKABLE void ControlWorkEditorComponent::addTaskTab(int taskId) {
    Task* task = repository->getTaskById(taskId);
    QVariantMap tabMap;
    tabMap["taskId"] = taskId;
    tabMap["saved"] = true;
    tabMap["title"] = QString::fromStdString(task->content);
    _taskTabs.addTab(tabMap);
}
