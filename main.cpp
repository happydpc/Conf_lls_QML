#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "./connection/connection.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<Connection>("Connection", 0, 0, "Connection");

    QQmlApplicationEngine engine;

    engine.load(QUrl(QStringLiteral("qrc:/qml/app.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
