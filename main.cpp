#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "./view/viewController.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<ViewController>("viewController", 0, 0, "ViewController");

    QQmlApplicationEngine engine;

    engine.load(QUrl(QStringLiteral("qrc:/qml/app.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
