#include "AttachmentSaver.h"
#include <QCryptographicHash>
#include <QDateTime>

AttachmentSaver::AttachmentSaver(QObject *parent) : QObject(parent) {}

QString AttachmentSaver::saveImageToAppDir(const QString &sourceFilePath) {
    QFileInfo sourceInfo(sourceFilePath);
    if (sourceInfo.suffix().toLower() != "png") {
        qWarning() << "Only PNG files are supported";
        return "";
    }
    QString fileName = QString::number(_taskId) + ".png";
    QString destDir = _path + "/attachment/";
    QDir dir(destDir);
    if (!dir.exists()) {
        if (!dir.mkpath(".")) {
            qWarning() << "Failed to create directory:" << destDir;
            return "";
        }
    }
    QString destPath = destDir + fileName;
    if (QFile::exists(destPath) && !QFile::remove(destPath)) {
        qWarning() << "Failed to remove existing file:" << destPath;
        return "";
    }
    if (!QFile::copy(sourceFilePath, destPath)) {
        qWarning() << "Failed to copy file from" << sourceFilePath << "to" << destPath;
        return "";
    }
    emit imageSaved(destPath);
    return destPath;
}

Q_INVOKABLE void AttachmentSaver::deleteAttachment() {
    QString fileName = QString::number(_taskId) + ".png";
    QString destDir = _path + "/attachment/";
    QDir dir(destDir);
    if (!dir.exists()) {
        return;
    }
    QString destPath = destDir + fileName;
    if (QFile::exists(destPath)) {
        QFile::remove(destPath);
    }
    emit imageSaved("");
}
