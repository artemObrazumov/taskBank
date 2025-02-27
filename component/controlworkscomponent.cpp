#include "controlworkscomponent.h"

ControlWorksComponent::ControlWorksComponent() {
    getControlWorksList();
}
ControlWorksComponent::~ControlWorksComponent() {}

Q_INVOKABLE QList<QVariantMap> ControlWorksComponent::getControlWorksList() {
    QList<QVariantMap> worksList;
    auto works = this->repository.getControlWorks();

    for (const auto& work : works) {
        QVariantMap workMap;
        workMap["id"] = work.id;
        workMap["title"] = QString::fromStdString(work.title);
        worksList.append(workMap);
    }

    this->workss = worksList;
    emit valueChanged();

    return worksList;
}

Q_INVOKABLE unsigned int ControlWorksComponent::createControlWork(QString title, QString path) {
    return this->repository.createControlWork(title.toStdString(), path.toStdString());
}
