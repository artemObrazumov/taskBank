#include "component/ControlWorksComponent.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<ControlWorksComponent>("components.controlWorks", 1, 0, "ControlWorksComponent");

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("applicationDirPath", QGuiApplication::applicationDirPath());

    const QUrl url("qrc:/path/main.qml"); // ссылка на файл qml
    engine.load(url);   // загружаем файл qml

    return app.exec();
}
