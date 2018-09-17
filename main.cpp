#include <QtWidgets/QApplication>
#include <QtQuick/QQuickView>
#include <QtCore/QDir>
#include <QtQml/QQmlEngine>
#include <QtGui/QGuiApplication>
#include <QQmlContext>

#include "./view/viewController.h"
#include "view/radialbar.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQuickView viewer;
#ifdef Q_OS_WIN
    QString extraImportPath(QStringLiteral("%1/../../../../%2"));
#else
    QString extraImportPath(QStringLiteral("%1/../../../%2"));
#endif
    QObject::connect(viewer.engine(), &QQmlEngine::quit, &viewer, &QWindow::close);

    Model *interfaceModel = new Model();
    ViewController *viewController = new ViewController(interfaceModel);

    viewer.rootContext()->setContextProperty("viewController", viewController);
    qmlRegisterType<RadialBar>("CustomControls", 1, 0, "RadialBar");

    viewer.rootContext()->setContextProperty("programmModel", interfaceModel);

    viewer.setSource(QUrl("qrc:/qml/app.qml"));

    return app.exec();
}
