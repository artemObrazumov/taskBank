#include "controlworkeditorcomponent.h"

QVariantMap mapFromTask(Task* task) {
    QVariantMap taskMap;
    taskMap["taskId"] = task->id;
    taskMap["content"] = QString::fromStdString(task->content);
    taskMap["answer"] = QString::fromStdString(task->answer);
    return taskMap;
}

QVariantMap mapFromTag(Tag* tag) {
    QVariantMap taskMap;
    taskMap["tagId"] = tag->id;
    taskMap["title"] = QString::fromStdString(tag->name);
    return taskMap;
}

ControlWorkEditorComponent::ControlWorkEditorComponent() {}

ControlWorkEditorComponent::~ControlWorkEditorComponent() {}

void ControlWorkEditorComponent::componentComplete() {
    componentComplete();
}

void ControlWorkEditorComponent::loadControlWork() {
    if (repository == nullptr) {
        repository = new controlWorkEditorRepository(_workId);
    }

    ControlWork* work = repository->getControlWork();
    _controlWork["title"] = QString::fromStdString(work->title);
    this->_path = work->path + "/" + work->title;
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

void ControlWorkEditorComponent::loadAllTags() {
    allTags = repository->getTags();
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
    taskContentMap.at(taskId).tags.clear();
    for (int i = 0; i < _taskTags.taskTags().count(); ++i) {
        taskContentMap.at(taskId).tags.emplace_back(
            _taskTags.taskTags()[i]["tagId"].toInt(), _taskTags.taskTags()[i]["title"].toString().toStdString()
        );
    }
}

Q_INVOKABLE void ControlWorkEditorComponent::openTask(int taskId) {
    if (taskContentMap.find(taskId) == taskContentMap.end()) {
        Task* task = repository->getTaskById(taskId);
        taskContentMap.insert({taskId, *task});
        std::vector<Tag> tags = repository->getTaskTags(taskId);
        for (int i = 0; i < tags.size(); ++i) {
            taskContentMap.at(taskId).tags.push_back(tags[i]);
        }
    }
    lastOpenedWork = taskId;
    this->_taskId = lastOpenedWork;
    emit taskIdChanged();
    Task openedTask = taskContentMap.at(taskId);
    _taskTags.deleteAll();
    for (int i = 0; i < openedTask.tags.size(); ++i) {
        _taskTags.addTag( mapFromTag(&openedTask.tags[i]) );
    }
    emit taskOpened(QString::fromStdString(openedTask.content), QString::fromStdString(openedTask.answer));
}

Q_INVOKABLE void ControlWorkEditorComponent::saveTask(int taskId, QString content, QString answer) {
    saveLocally(taskId, content, answer);
    repository->saveTask(taskId, content.toStdString(), answer.toStdString());
    repository->deleteTaskTags(taskId);
    std::vector<Tag> tags = taskContentMap.at(taskId).tags;
    for (int i = 0; i < tags.size(); ++i) {
        repository->saveTaskTag(taskId, tags[i].id);
    }
    _taskTabs.changeTabTitle(taskId, content);
    _taskGroups.updateTaskTitle(taskId, content);
}

Q_INVOKABLE void ControlWorkEditorComponent::closeTaskTab(int taskId) {
    _taskTabs.deleteTask(taskId);
}

Q_INVOKABLE void ControlWorkEditorComponent::loadTagsList() {
    _tagsSelectList.deleteAll();
    for(auto tag{allTags.begin()}; tag != allTags.end(); tag++) {
        if (_taskTags.containsTag(tag->id) == false) {
            _tagsSelectList.addTag(mapFromTag(&*tag));
        }
    }
}

Q_INVOKABLE void ControlWorkEditorComponent::addTag(int tagId) {
    Tag* tag = repository->getTagById(tagId);
    taskContentMap.at(lastOpenedWork).tags.push_back(*tag);
    _taskTags.addTag(mapFromTag(tag));
}

Q_INVOKABLE void ControlWorkEditorComponent::createTag(QString title) {
    int tagId = repository->createTag(title.toStdString());
    Tag tag(tagId, title.toStdString());
    allTags.push_back(tag);
    _tagsSelectList.addTag(mapFromTag(&tag));
}

Q_INVOKABLE void ControlWorkEditorComponent::deleteTag(int tagId) {
    _taskTags.deleteTag(tagId);
}
