#ifndef GROUPDETAILSMODEL_H
#define GROUPDETAILSMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QVariantMap>

class GroupDetailsModel : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(QList<QVariantMap> groups READ groups NOTIFY groupsChanged)

private:

    QList<QVariantMap> _groups;

public:
    enum Roles {
        Group = Qt::UserRole + 1
    };

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return _groups.size();
    }

    QVariant data(const QModelIndex& index, int role) const override {
        if (role == Group) {
            return _groups[index.row()];
        }
        return QVariant();
    }

    QList<QVariantMap> groups() const {
        return _groups;
    }

    QHash<int, QByteArray> roleNames() const override {
        return {
            {Group, "variant"}
        };
    }

    void addVariant(QVariantMap groupMap) {
        for (int i = 0; i < _groups.size(); ++i) {
            if (_groups[i]["id"] == groupMap["id"]) {
                return;
            }
        }
        beginInsertRows(QModelIndex(), _groups.size(), _groups.size());
        _groups.append(groupMap);
        endInsertRows();
    }

    void clearAll() {
        if (_groups.isEmpty()) {
            return;
        }

        beginRemoveRows(QModelIndex(), 0, _groups.size() - 1);
        _groups.clear();
        endRemoveRows();
        emit groupsChanged();
    }

    GroupDetailsModel() {}
    ~GroupDetailsModel() {}

signals:

    void groupsChanged();
};

#endif // GROUPDETAILSMODEL_H
