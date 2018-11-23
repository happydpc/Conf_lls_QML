#include <QtWidgets/QApplication>
#include <QtQml>
#include <QQmlApplicationEngine>
#include <QtQuick/QQuickView>
#include <QtCore/QDir>
#include <QtQml/QQmlEngine>
#include <QtGui/QGuiApplication>
#include <QQmlContext>
#include "view/controller.h"
#include "view/module/radialbar.h"
#include "./translate/qmltranslator.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQuickView viewer;
    QmlTranslator qmlTranslator;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("qmlTranslator", &qmlTranslator);
    QObject::connect(viewer.engine(), &QQmlEngine::quit, &viewer, &QWindow::close);

    Controller *controller = new Controller();
    viewer.rootContext()->setContextProperty("controller", controller);
    viewer.rootContext()->setContextProperty("ioTreeModel", controller->getIoTreeModel());
    qmlRegisterType<RadialBar>("CustomControls", 1, 0, "RadialBar");
    viewer.setSource(QUrl("qrc:/qml/app.qml"));

    return app.exec();
}
