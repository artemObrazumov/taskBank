#ifndef VARIANTSMODEL_H
#define VARIANTSMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QVariantMap>

class VariantsModel : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(QList<QVariantMap> variants READ variants NOTIFY variantsChanged)

private:

    QList<QVariantMap> _variants;

public:
    enum Roles {
        Variant = Qt::UserRole + 1
    };

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return _variants.size();
    }

    QVariant data(const QModelIndex& index, int role) const override {
        if (role == Variant) {
            return _variants[index.row()];
        }
        return QVariant();
    }

    QList<QVariantMap> variants() const {
        return _variants;
    }

    QHash<int, QByteArray> roleNames() const override {
        return {
            {Variant, "variant"}
        };
    }

    void addVariant(QVariantMap variantMap) {
        for (int i = 0; i < _variants.size(); ++i) {
            if (_variants[i]["id"] == variantMap["id"]) {
                return;
            }
        }
        beginInsertRows(QModelIndex(), _variants.size(), _variants.size());
        _variants.append(variantMap);
        endInsertRows();
    }

    void clearAll() {
        if (_variants.isEmpty()) {
            return;
        }

        beginRemoveRows(QModelIndex(), 0, _variants.size() - 1);
        _variants.clear();
        endRemoveRows();
        emit variantsChanged();
    }

    VariantsModel() {}
    ~VariantsModel() {}

signals:

    void variantsChanged();
};

#endif // VARIANTSMODEL_H
