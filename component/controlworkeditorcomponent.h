#ifndef CONTROLWORKEDITORCOMPONENT_H
#define CONTROLWORKEDITORCOMPONENT_H

#include "component/utils/taskgroupsmodel.h"
#include "component/utils/tasktabsmodel.h"
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
    Q_PROPERTY(QString taskName READ taskName NOTIFY taskNameChanged)

private:

    controlWorkEditorRepository* repository = nullptr;
    int _workId;
    QVariantMap _controlWork;
    void loadControlWork();
    TaskGroupModel _taskGroups;
    TaskTabsModel _taskTabs;
    std::unordered_map<int, Task> taskContentMap;
    std::string _taskName;

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
        }
    }

    TaskGroupModel* taskGroups() {
        return &_taskGroups;
    }

    TaskTabsModel* taskTabs() {
        return &_taskTabs;
    }

    QString taskName() {
        return QString::fromStdString(_taskName);
    }

    Q_INVOKABLE void addTaskGroup();

    Q_INVOKABLE void addTaskToGroup(int groupId);

    Q_INVOKABLE void deleteTask(int groupId, int taskId);

    Q_INVOKABLE void addTaskTab(int taskId);

    Q_INVOKABLE void openTask(int taskId);

protected:

    void componentComplete();

signals:

    void workIdChanged();
    void controlWorkChanged();
    void taskNameChanged();
};

#endif // CONTROLWORKEDITORCOMPONENT_H
