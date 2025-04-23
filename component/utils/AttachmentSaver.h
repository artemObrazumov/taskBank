#ifndef ATTACHMENTSAVER_H
#define ATTACHMENTSAVER_H

#include <QObject>
#include <QString>
#include <QDir>
#include <QFile>

class AttachmentSaver : public QObject{
    Q_OBJECT
    Q_PROPERTY(int taskId READ taskId WRITE newTaskId NOTIFY taskIdChanged)
    Q_PROPERTY(QString path READ path WRITE newPath NOTIFY pathChanged)

private:
    QString _path;
    int _taskId;

    QString destPath() {
        QString fileName = QString::fromStdString(std::to_string(this->_taskId) + ".jpg");
        QString destDir = this->_path + "/attachment/";
        return destDir + fileName;
    }

public:

    explicit AttachmentSaver(QObject *parent = nullptr);

    QString path() {
        return _path;
    }

    int taskId() {
        return _taskId;
    }

    void newTaskId(int newId) {
        this->_taskId = newId;
        emit imageSaved(destPath());
    }

    void newPath(QString newPath) {
        this->_path = newPath;
        emit imageSaved(destPath());
    }

public slots:

    QString saveImageToAppDir(const QString &sourceFilePath);

    Q_INVOKABLE void deleteAttachment();

signals:

    void imageSaved(const QString &path);
    void taskIdChanged();
    void pathChanged();
};

#endif // ATTACHMENTSAVER_H
