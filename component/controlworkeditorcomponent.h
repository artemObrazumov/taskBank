#ifndef CONTROLWORKEDITORCOMPONENT_H
#define CONTROLWORKEDITORCOMPONENT_H

#include "repositories/controlworkeditorrepository.h"
#include <QObject>
#include <QVariantList>

class ControlWorkEditorComponent : public QObject {
    Q_OBJECT
    Q_PROPERTY(int workId READ workId WRITE setWorkId NOTIFY workIdChanged)
    Q_PROPERTY(QVariantMap controlWork READ controlWork NOTIFY controlWorkChanged)
    Q_PROPERTY(QList<QVariantMap> taskGroups READ taskGroups NOTIFY taskGroupsChanged)

private:

    controlWorkEditorRepository* repository = nullptr;
    int _workId;
    QVariantMap _controlWork;
    QList<QVariantMap> _taskGroups;
    void loadControlWork();

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
    QList<QVariantMap> taskGroups() {
        return _taskGroups;
    }

    Q_INVOKABLE void toggleGroupShow(int groupId);

protected:

    void componentComplete();

signals:

    void workIdChanged();
    void controlWorkChanged();
    void taskGroupsChanged();
};

#endif // CONTROLWORKEDITORCOMPONENT_H
