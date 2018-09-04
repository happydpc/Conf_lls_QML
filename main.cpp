//#include <QGuiApplication>
//#include <QQmlApplicationEngine>

#include "./view/viewController.h"

#include <QtWidgets/QApplication>
#include <QtQuick/QQuickView>
#include <QtCore/QDir>
#include <QtQml/QQmlEngine>

int main(int argc, char *argv[])
{
    // Qt Charts uses Qt Graphics View Framework for drawing, therefore QApplication must be used.
    QApplication app(argc, argv);

    QQuickView viewer;
    // The following are needed to make examples run without having to install the module
    // in desktop environments.
#ifdef Q_OS_WIN
    QString extraImportPath(QStringLiteral("%1/../../../../%2"));
#else
    QString extraImportPath(QStringLiteral("%1/../../../%2"));
#endif
    QObject::connect(viewer.engine(), &QQmlEngine::quit, &viewer, &QWindow::close);

    qmlRegisterType<ViewController>("viewController", 0, 0, "ViewController");

    viewer.setSource(QUrl("qrc:/qml/app.qml"));

    return app.exec();
}


//int main(int argc, char *argv[])
//{
//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

//    QGuiApplication app(argc, argv);

//    qmlRegisterType<ViewController>("viewController", 0, 0, "ViewController");

//    QQmlApplicationEngine engine;

//    engine.load(QUrl(QStringLiteral("qrc:/qml/app.qml")));
//    if (engine.rootObjects().isEmpty())
//        return -1;

//    return app.exec();
//}
