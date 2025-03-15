#ifndef TASKGROUPSMODEL_H
#define TASKGROUPSMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QVariantMap>

class TaskGroupModel : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(QList<QVariantMap> taskGroups READ taskGroups NOTIFY taskGroupsChanged)

private:

    QList<QVariantMap> _taskGroups;

public:
    enum Roles {
        GroupDataRole = Qt::UserRole + 1
    };

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return _taskGroups.size();
    }

    QVariant data(const QModelIndex& index, int role) const override {
        if (role == GroupDataRole) {
            return _taskGroups[index.row()];
        }
        return QVariant();
    }

    QList<QVariantMap> taskGroups() const {
        return _taskGroups;
    }

    QHash<int, QByteArray> roleNames() const override {
        return {
            {GroupDataRole, "groupData"}
        };
    }

    Q_INVOKABLE void toggleGroupShow(int groupId) {
        for (int i = 0; i < _taskGroups.size(); ++i) {
            if (_taskGroups[i]["id"] == groupId) {
                _taskGroups[i]["show"] = _taskGroups[i]["show"] == false;
                QModelIndex modelIndex = index(i);
                emit dataChanged(modelIndex, modelIndex, {});
                break;
            }
        }
    }

    void addGroup(QVariantMap groupMap) {
        beginInsertRows(QModelIndex(), _taskGroups.size(), _taskGroups.size());
        _taskGroups.append(groupMap);
        endInsertRows();
    }

    void addTaskToGroup(int groupId, QVariantMap taskMap) {
        for (int i = 0; i < _taskGroups.size(); ++i) {
            if (_taskGroups[i]["id"] == groupId) {
                QList<QVariantMap> newTaskVariants = _taskGroups[i]["taskVariants"].value<QList<QVariantMap>>();
                newTaskVariants.append(taskMap);
                _taskGroups[i]["taskVariants"] = QVariant::fromValue(newTaskVariants);
                QModelIndex modelIndex = index(i);
                emit dataChanged(modelIndex, modelIndex, {GroupDataRole});
                break;
            }
        }
    }

    void deleteTask(int groupId, int taskId) {
        for (int i = 0; i < _taskGroups.size(); ++i) {
            if (_taskGroups[i]["id"] == groupId) {
                QList<QVariantMap> newTaskVariants = _taskGroups[i]["taskVariants"].value<QList<QVariantMap>>();
                for (int j = 0; j < newTaskVariants.size(); ++j) {
                    if (newTaskVariants[j]["taskId"] == taskId) {
                        newTaskVariants.removeAt(j);
                        break;
                    }
                }
                _taskGroups[i]["taskVariants"] = QVariant::fromValue(newTaskVariants);
                QModelIndex modelIndex = index(i);
                emit dataChanged(modelIndex, modelIndex, {GroupDataRole});
                break;
            }
        }
    }

signals:

    void taskGroupsChanged();
};

#endif // TASKGROUPSMODEL_H
