#ifndef CHECKBOXLISTMODEL_H
#define CHECKBOXLISTMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QVariantMap>

class CheckBoxListModel : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(QList<QVariantMap> checkboxes READ checkboxes NOTIFY checkboxesChanged)

private:

    QList<QVariantMap> _checkboxes;

public:
    enum Roles {
        CheckboxRole = Qt::UserRole + 1
    };

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return _checkboxes.size();
    }

    QVariant data(const QModelIndex& index, int role) const override {
        if (role == CheckboxRole) {
            return _checkboxes[index.row()];
        }
        return QVariant();
    }

    QList<QVariantMap> checkboxes() const {
        return _checkboxes;
    }

    QHash<int, QByteArray> roleNames() const override {
        return {
            {CheckboxRole, "checkboxData"}
        };
    }

    Q_INVOKABLE void toggleCheckbox(int checkboxId) {
        for (int i = 0; i < _checkboxes.size(); ++i) {
            if (_checkboxes[i]["id"] == checkboxId) {
                _checkboxes[i]["checked"] = _checkboxes[i]["checked"] == false;
                QModelIndex modelIndex = index(i);
                emit dataChanged(modelIndex, modelIndex, {});
                break;
            }
        }
    }

    void addСheckbox(QVariantMap checkboxMap) {
        for (int i = 0; i < _checkboxes.size(); ++i) {
            if (_checkboxes[i]["id"] == checkboxMap["id"]) {
                return;
            }
        }
        beginInsertRows(QModelIndex(), _checkboxes.size(), _checkboxes.size());
        _checkboxes.append(checkboxMap);
        endInsertRows();
    }

    std::vector<int> getCheckedId() {
        std::vector<int> ids;
        for (int i = 0; i < _checkboxes.size(); ++i) {
            if (_checkboxes[i]["checked"] == true) {
                ids.push_back((_checkboxes[i]["id"].toInt()));
            }
        }
        return ids;
    }

signals:

    void checkboxesChanged();
};

#endif // CHECKBOXLISTMODEL_H
