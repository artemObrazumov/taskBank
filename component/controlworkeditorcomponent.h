#ifndef CONTROLWORKEDITORCOMPONENT_H
#define CONTROLWORKEDITORCOMPONENT_H

#include "component/utils/taskgroupsmodel.h"
#include "repositories/controlworkeditorrepository.h"
#include <QObject>
#include <QVariantList>
#include <QtCore/qabstractitemmodel.h>

class ControlWorkEditorComponent : public QObject {
    Q_OBJECT
    Q_PROPERTY(int workId READ workId WRITE setWorkId NOTIFY workIdChanged)
    Q_PROPERTY(QVariantMap controlWork READ controlWork NOTIFY controlWorkChanged)
    Q_PROPERTY(TaskGroupModel* taskGroups READ taskGroups CONSTANT)

private:

    controlWorkEditorRepository* repository = nullptr;
    int _workId;
    QVariantMap _controlWork;
    void loadControlWork();
    TaskGroupModel _taskGroups;

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

    Q_INVOKABLE void addTaskGroup();

    Q_INVOKABLE void addTaskToGroup(int groupId);

    Q_INVOKABLE void deleteTask(int groupId, int taskId);

protected:

    void componentComplete();

signals:

    void workIdChanged();
    void controlWorkChanged();
    void taskGroupsChanged();
};

#endif // CONTROLWORKEDITORCOMPONENT_H
