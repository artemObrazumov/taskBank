#ifndef CONTROLWORKEDITORCOMPONENT_H
#define CONTROLWORKEDITORCOMPONENT_H

#include "component/utils/taskgroupsmodel.h"
#include "component/utils/tasktabsmodel.h"
#include "component/utils/tasktagsmodel.h"
#include "repositories/controlworkeditorrepository.h"
#include <QObject>
#include <QVariantList>
#include <QtCore/qabstractitemmodel.h>

class ControlWorkEditorComponent : public QObject {
    Q_OBJECT
    Q_PROPERTY(int workId READ workId WRITE setWorkId NOTIFY workIdChanged)
    Q_PROPERTY(QVariantMap controlWork READ controlWork NOTIFY controlWorkChanged)
    Q_PROPERTY(TaskGroupModel* taskGroups READ taskGroups CONSTANT)
    Q_PROPERTY(TaskTabsModel* taskTabs READ taskTabs CONSTANT)
    Q_PROPERTY(TaskTagsModel* tagsSelectList READ tagsSelectList CONSTANT)
    Q_PROPERTY(TaskTagsModel* taskTags READ taskTags CONSTANT)
    Q_PROPERTY(QString taskName READ taskName NOTIFY taskNameChanged)
    Q_PROPERTY(QString path READ path CONSTANT)
    Q_PROPERTY(int taskId READ taskId NOTIFY taskIdChanged)

private:

    controlWorkEditorRepository* repository = nullptr;
    int _workId;
    QVariantMap _controlWork;
    void loadControlWork();
    void loadAllTags();
    TaskGroupModel _taskGroups;
    TaskTabsModel _taskTabs;
    TaskTagsModel _tagsSelectList;
    TaskTagsModel _taskTags;
    std::unordered_map<int, Task> taskContentMap;
    std::string _taskName;
    std::vector<Tag> allTags;
    std::string _path;
    int _taskId;

    int lastOpenedWork = -1;

public:

    ControlWorkEditorComponent();
    ~ControlWorkEditorComponent();

    int workId() {
        return _workId;
    }

    QVariantMap controlWork() {
        return _controlWork;
    }

    void setWorkId(const int& workId) {
        if (_workId != workId) {
            _workId = workId;
            loadControlWork();
            loadAllTags();
        }
    }

    TaskGroupModel* taskGroups() {
        return &_taskGroups;
    }

    TaskTabsModel* taskTabs() {
        return &_taskTabs;
    }

    TaskTagsModel* tagsSelectList() {
        return &_tagsSelectList;
    }

    TaskTagsModel* taskTags() {
        return &_taskTags;
    }

    QString taskName() {
        return QString::fromStdString(_taskName);
    }

    QString path() {
        return QString::fromStdString(_path);
    }

    int taskId() {
        return _taskId;
    }

    Q_INVOKABLE void addTaskGroup();

    Q_INVOKABLE void addTaskToGroup(int groupId);

    Q_INVOKABLE void deleteTask(int groupId, int taskId);

    Q_INVOKABLE void addTaskTab(int taskId);

    Q_INVOKABLE void saveLocally(int taskId, QString content, QString answer);

    Q_INVOKABLE void openTask(int taskId);

    Q_INVOKABLE void saveTask(int taskId, QString content, QString answer);

    Q_INVOKABLE void closeTaskTab(int taskId);

    Q_INVOKABLE void loadTagsList();

    Q_INVOKABLE void addTag(int tagId);

    Q_INVOKABLE void createTag(QString title);

    Q_INVOKABLE void deleteTag(int tagId);

protected:

    void componentComplete();

signals:

    void workIdChanged();
    void controlWorkChanged();
    void taskNameChanged();
    void taskIdChanged();
    void taskOpened(QString content, QString answer);
    void taskDeleted(int taskId);
};

#endif // CONTROLWORKEDITORCOMPONENT_H
