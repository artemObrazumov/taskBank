#include "controlworkscomponent.h"
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <filesystem>
#include <string>

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
        workMap["tasks"] = work.tasks;
        workMap["variants"] = work.variants;
        workMap["isValid"] = work.isValid;
        std::stringstream dateStream;
        dateStream << std::put_time(std::localtime(&work.lastEdited), "%d.%m.%Y");
        workMap["lastEdited"] = QString::fromStdString(dateStream.str());
        worksList.append(workMap);
    }

    this->workss = worksList;
    emit valueChanged();

    return worksList;
}

Q_INVOKABLE unsigned int ControlWorksComponent::createControlWork(QString title, QString path) {
    return this->repository.createControlWork(title.toStdString(), path.toStdString());
}

Q_INVOKABLE void ControlWorksComponent::archiveWork(int workId, QString path) {
    ControlWork* work = this->repository.getControlWork(workId);
    this->archiver.exportToZip(work->path + "/" + work->title, path.toStdString());
}

Q_INVOKABLE void ControlWorksComponent::importWork(QString archive, QString path) {
    this->archiver.importFromZip(archive.toStdString(), path.toStdString());
    std::filesystem::path fsPath(archive.toStdString());
    std::string name = fsPath.stem().string();
    std::cout << name;
    this->repository.addControlWork(name, path.toStdString());
    this->getControlWorksList();
}
