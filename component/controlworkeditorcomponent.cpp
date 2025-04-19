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
    _taskTabs.deleteTask(taskId);
    emit taskDeleted(taskId);
}

Q_INVOKABLE void ControlWorkEditorComponent::addTaskTab(int taskId) {
    Task* task = repository->getTaskById(taskId);
    QVariantMap tabMap;
    tabMap["taskId"] = taskId;
    tabMap["saved"] = true;
    tabMap["title"] = QString::fromStdString(task->content);
    _taskTabs.addTab(tabMap);
}

Q_INVOKABLE void ControlWorkEditorComponent::saveLocally(int taskId, QString content, QString answer) {
    taskContentMap.at(taskId).content = content.toStdString();
    taskContentMap.at(taskId).answer = answer.toStdString();
}

Q_INVOKABLE void ControlWorkEditorComponent::openTask(int taskId) {
    if (taskContentMap.find(taskId) == taskContentMap.end()) {
        Task* task = repository->getTaskById(taskId);
        taskContentMap.insert({taskId, *task});
    }
    Task openedTask = taskContentMap.at(taskId);
    emit taskOpened(QString::fromStdString(openedTask.content), QString::fromStdString(openedTask.answer));
}

Q_INVOKABLE void ControlWorkEditorComponent::saveTask(int taskId, QString content, QString answer) {
    saveLocally(taskId, content, answer);
    repository->saveTask(taskId, content.toStdString(), answer.toStdString());
    _taskTabs.changeTabTitle(taskId, content);
    _taskGroups.updateTaskTitle(taskId, content);
}

Q_INVOKABLE void ControlWorkEditorComponent::closeTaskTab(int taskId) {
    _taskTabs.deleteTask(taskId);
}
