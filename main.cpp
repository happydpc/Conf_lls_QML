#include <QtWidgets/QApplication>
#include <QtQml>
#include <QQmlApplicationEngine>
#include <QtQuick/QQuickView>
#include <QtCore/QDir>
#include <QtQml/QQmlEngine>
#include <QtGui/QGuiApplication>
#include <QQmlContext>
#include "./view/viewController.h"
#include "view/radialbar.h"
#include "./translate/qmltranslator.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQuickView viewer;

    QmlTranslator qmlTranslator;

    QQmlApplicationEngine engine;
    // and register it as a context in Qml layer
    engine.rootContext()->setContextProperty("qmlTranslator", &qmlTranslator);

    QObject::connect(viewer.engine(), &QQmlEngine::quit, &viewer, &QWindow::close);

    Model *interfaceModel = new Model();
    ViewController *viewController = new ViewController(interfaceModel);

    viewer.rootContext()->setContextProperty("viewController", viewController);
    qmlRegisterType<RadialBar>("CustomControls", 1, 0, "RadialBar");

    viewer.rootContext()->setContextProperty("programmModel", interfaceModel);

    viewer.setSource(QUrl("qrc:/qml/app.qml"));

    return app.exec();
}
