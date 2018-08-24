#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "connectionFactory.h"

//#include "timegame.h"
#include "settings.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<ConnectionFactory>("ConnectionFactory", 0, 0, "ConnectionFactory");
    qmlRegisterType<Settings>("Settings", 0, 0, "Settings");

    QQmlApplicationEngine engine;

    engine.load(QUrl(QStringLiteral("qrc:/app.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
