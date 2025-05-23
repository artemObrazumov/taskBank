#include "component/ControlWorksComponent.h"
#include "component/controlworkeditorcomponent.h"
#include "component/utils/AttachmentSaver.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QStandardItemModel>
#include <QQmlContext>
#include <QQuickWindow>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    qmlRegisterType<ControlWorksComponent>("components.controlWorks", 1, 0, "ControlWorksComponent");
    qmlRegisterType<ControlWorkEditorComponent>("components.controlWorkEditor", 1, 0, "ControlWorkEditorComponent");
    qmlRegisterType<TaskTagsModel>("utils.taskTagsModel", 1, 0, "TaskTagsModel");
    qmlRegisterType<CheckBoxListModel>("utils.checkboxModel", 1, 0, "CheckBoxModel");
    qmlRegisterType<AttachmentSaver>("utils.attachmentSaver", 1, 0, "AttachmentSaver");
    qmlRegisterType<GroupDetailsModel>("utils.groupDetailsModel", 1, 0, "GroupDetailsModel");

    QQmlApplicationEngine engine;
    const QUrl url("qrc:/path/main.qml");
    engine.load(url);

    return app.exec();
}
