#ifndef CONTROLWORKSCOMPONENT_H
#define CONTROLWORKSCOMPONENT_H

#include "repositories/ControlWorksRepository.h"
#include "utils/controlworkarchivemanager.h"
#include <QObject>
#include <QVariantList>

class ControlWorksComponent : public QObject {
    Q_OBJECT
    Q_PROPERTY(QList<QVariantMap> test READ works NOTIFY valueChanged)

private:
    ControlWorksRepository repository;
    ControlWorkArchiveManager archiver;

public:
    QList<QVariantMap> workss;
    QList<QVariantMap> works() {
        return this->workss;
    }
    ControlWorksComponent();
    ~ControlWorksComponent();
    Q_INVOKABLE QList<QVariantMap> getControlWorksList();
    Q_INVOKABLE unsigned int createControlWork(QString title, QString path);
    Q_INVOKABLE void archiveWork(int workId, QString path);
    Q_INVOKABLE void importWork(QString archive, QString path);
signals:
    void valueChanged();
};

#endif // CONTROLWORKSCOMPONENT_H
