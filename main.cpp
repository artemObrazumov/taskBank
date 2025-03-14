#include "component/ControlWorksComponent.h"
#include "component/controlworkeditorcomponent.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QStandardItemModel>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<ControlWorksComponent>("components.controlWorks", 1, 0, "ControlWorksComponent");
    qmlRegisterType<ControlWorkEditorComponent>("components.controlWorkEditor", 1, 0, "ControlWorkEditorComponent");

    QQmlApplicationEngine engine;
    const QUrl url("qrc:/path/main.qml");
    engine.load(url);

    return app.exec();
}
