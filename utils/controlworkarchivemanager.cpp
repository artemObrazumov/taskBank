#include "controlworkarchivemanager.h"
#include <quazip/JlCompress.h>
#include <QDir>
#include <QFileInfo>

ControlWorkArchiveManager::ControlWorkArchiveManager() {}

void ControlWorkArchiveManager::exportToZip(const std::string& workPath, const std::string& exportPath) {
    QString qWorkPath = QString::fromStdString(workPath);
    QString qExportPath = QString::fromStdString(exportPath);

    if (!QDir(qWorkPath).exists()) {
        return;
    }

    JlCompress::compressDir(qExportPath, qWorkPath);
}

void ControlWorkArchiveManager::importFromZip(const std::string& importPath, const std::string& projectPath) {
    QString qImportPath = QString::fromStdString(importPath);
    QString qProjectPath = QString::fromStdString(projectPath);

    if (!QFile::exists(qImportPath)) {
        return;
    }

    QFileInfo archiveInfo(qImportPath);
    QString archiveBaseName = archiveInfo.completeBaseName();
    if (archiveBaseName.isEmpty()) {
        return;
    }

    QString targetFolderPath = QDir(qProjectPath).filePath(archiveBaseName);
    QDir targetDir(targetFolderPath);

    if (!targetDir.exists()) {
        if (!targetDir.mkpath(".")) {
            return;
        }
    }

    JlCompress::extractDir(qImportPath, targetFolderPath);
}
