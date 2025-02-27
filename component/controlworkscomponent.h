#ifndef CONTROLWORKSCOMPONENT_H
#define CONTROLWORKSCOMPONENT_H

#include "repositories/ControlWorksRepository.h"
#include <QObject>
#include <QVariantList>

class ControlWorksComponent : public QObject {
    Q_OBJECT
    Q_PROPERTY(QList<QVariantMap> test READ works NOTIFY valueChanged)

private:
    ControlWorksRepository repository;

public:
    QList<QVariantMap> workss;
    QList<QVariantMap> works() {
        return this->workss;
    }
    ControlWorksComponent();
    ~ControlWorksComponent();
    Q_INVOKABLE QList<QVariantMap> getControlWorksList();
    Q_INVOKABLE unsigned int createControlWork(QString title, QString path);
signals:
    void valueChanged();
};

#endif // CONTROLWORKSCOMPONENT_H
