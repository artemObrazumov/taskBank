#ifndef TASKTAGSMODEL_H
#define TASKTAGSMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QVariantMap>

class TaskTagsModel : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(QList<QVariantMap> taskTags READ taskTags NOTIFY taskTagsChanged)

private:

    QList<QVariantMap> _taskTags;

public:
    enum Roles {
        TagDataRole = Qt::UserRole + 1
    };

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return _taskTags.size();
    }

    QVariant data(const QModelIndex& index, int role) const override {
        if (role == TagDataRole) {
            return _taskTags[index.row()];
        }
        return QVariant();
    }

    QList<QVariantMap> taskTags() const {
        return _taskTags;
    }

    QHash<int, QByteArray> roleNames() const override {
        return {
            {TagDataRole, "tagData"}
        };
    }

    void addTag(QVariantMap tagMap) {
        for (int i = 0; i < _taskTags.size(); ++i) {
            if (_taskTags[i]["taskId"] == tagMap["taskId"]) {
                return;
            }
        }
        beginInsertRows(QModelIndex(), _taskTags.size(), _taskTags.size());
        _taskTags.append(tagMap);
        endInsertRows();
    }

    TaskTagsModel() {}
    ~TaskTagsModel() {}

signals:

    void taskTagsChanged();
};

#endif // TASKTAGSMODEL_H
