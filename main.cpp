#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "connection.h"
#include "settings.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    qmlRegisterType<Settings>("Settings", 0, 0, "Settings");
    qmlRegisterType<Connection>("Connection", 0, 0, "Connection");
    //    qmlRegisterType<ConnectionFactory>("ConnectionFactory", 0, 0, "ConnectionFactory");

    engine.load(QUrl(QStringLiteral("qrc:/app.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
