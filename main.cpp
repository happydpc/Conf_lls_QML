#include "./view/viewController.h"

#include <QtWidgets/QApplication>
#include <QtQuick/QQuickView>
#include <QtCore/QDir>
#include <QtQml/QQmlEngine>

#include <QtGui/QGuiApplication>
#include <QQmlContext>
//#include "qtquick2applicationviewer.h"
//#include "model.h"

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

    Model interfaceListModel;

    qmlRegisterType<ViewController>("viewController", 0, 0, "ViewController");
    viewer.rootContext()->setContextProperty("programmModel", &interfaceListModel);
//    viewer.set "programmModel", &m);
    viewer.setSource(QUrl("qrc:/qml/app.qml"));

    return app.exec();
}
