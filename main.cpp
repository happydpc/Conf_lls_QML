#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "timegame.h"
#include "settings.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<TimeGame>("timeGame", 1, 0, "TimeGame");
    qmlRegisterType<Settings>("settings", 1, 0, "Settings");

    QQmlApplicationEngine engine;

    engine.load(QUrl(QStringLiteral("qrc:/app.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
