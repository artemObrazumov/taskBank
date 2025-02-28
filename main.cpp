#include "component/ControlWorksComponent.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<ControlWorksComponent>("components.controlWorks", 1, 0, "ControlWorksComponent");

    QQmlApplicationEngine engine;
    const QUrl url("qrc:/path/main.qml");
    engine.load(url);

    return app.exec();
}
