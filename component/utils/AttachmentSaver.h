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
    }

    void newPath(QString newPath) {
        this->_path = newPath;
    }

public slots:

    QString saveImageToAppDir(const QString &sourceFilePath);

signals:

    void imageSaved(const QString &path);
    void taskIdChanged();
    void pathChanged();
};

#endif // ATTACHMENTSAVER_H
