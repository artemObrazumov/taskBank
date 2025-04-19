#ifndef TASKTABSMODEL_H
#define TASKTABSMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QVariantMap>

class TaskTabsModel : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(QList<QVariantMap> taskTabs READ taskTabs NOTIFY taskTabsChanged)

private:

    QList<QVariantMap> _taskTabs;

public:
    enum Roles {
        TabDataRole = Qt::UserRole + 1
    };

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return _taskTabs.size();
    }

    QVariant data(const QModelIndex& index, int role) const override {
        if (role == TabDataRole) {
            return _taskTabs[index.row()];
        }
        return QVariant();
    }

    QList<QVariantMap> taskTabs() const {
        return _taskTabs;
    }

    QHash<int, QByteArray> roleNames() const override {
        return {
            {TabDataRole, "tabData"}
        };
    }

    void addTab(QVariantMap tabMap) {
        for (int i = 0; i < _taskTabs.size(); ++i) {
            if (_taskTabs[i]["taskId"] == tabMap["taskId"]) {
                return;
            }
        }
        beginInsertRows(QModelIndex(), _taskTabs.size(), _taskTabs.size());
        _taskTabs.append(tabMap);
        endInsertRows();
    }

    void changeTabTitle(int taskId, QString newTitle) {
        for (int i = 0; i < _taskTabs.size(); ++i) {
            if (_taskTabs[i]["taskId"] == taskId) {
                _taskTabs[i]["title"] = newTitle;
                emit dataChanged(index(i), index(i), { TabDataRole });
                return;
            }
        }
    }

    void deleteTask(int taskId) {
        for (int i = 0; i < _taskTabs.size(); ++i) {
            if (_taskTabs[i]["taskId"] == taskId) {
                beginRemoveRows(QModelIndex(), i, i);
                _taskTabs.removeAt(i);
                endRemoveRows();
                return;
            }
        }
    }

    TaskTabsModel() {}
    ~TaskTabsModel() {}

signals:

    void taskTabsChanged();
};

#endif // TASKTABSMODEL_H
