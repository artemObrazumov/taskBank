#include "AttachmentSaver.h"
#include <QCryptographicHash>
#include <QDateTime>

AttachmentSaver::AttachmentSaver(QObject *parent) : QObject(parent) {}

QString AttachmentSaver::saveImageToAppDir(const QString &sourceFilePath) {
    QString fileName = QString::fromStdString(std::to_string(this->_taskId) + ".jpg");
    QString destDir = this->_path + "/attachment/";

    QDir dir(destDir);
    if (!dir.exists()) {
        if (!dir.mkpath(".")) {
            return "";
        }
    }

    QString destPath = destDir + fileName;

    QFile destFile(destPath);
    if (destFile.exists()) {
        if (!destFile.remove()) {
            return "";
        }
    }

    if (QFile::copy(sourceFilePath, destPath)) {
        emit imageSaved(destPath);
        return destPath;
    } else {
        return "";
    }
}
