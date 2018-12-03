#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "view/module/modelDevTree.h"
#include "view/peripherals.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);

    // io
    Q_INVOKABLE bool addIo(const QString typeIoName, const QString ioName, const QStringList keys, const QStringList params);
    Q_INVOKABLE void removeIo(int ioIndex);
    Q_INVOKABLE QStringList getIoAddTypes(const QString typeName);
    // dev
    Q_INVOKABLE bool addDevToIo(const int ioIndex, const QString devTypeName, const QStringList keyParam, const QStringList valueParam);
    Q_INVOKABLE void removeDev(int ioIndex, int devIndex);
    Q_INVOKABLE QStringList getDevAddTypes() const;
    Q_INVOKABLE bool devExecCommand(int ioIndex, int devIndex, const QString commandType,
                                    const QStringList keys, const QStringList params);
    // logo, form
    Q_INVOKABLE QString getTypeLogo() const;

    // io/dev tree
    Q_INVOKABLE ModelDevTree* getIoTreeModel();

signals:
    // io
    void addIoSucces(QString ioType, QStringList keyProperty, QStringList valueProperty);
    void addIoFail(QString ioType, QString ioName);
    void ioUpdateProperty(QString ioType, int ioIndex, QStringList keyProperty, QStringList valueProperty);
    void removeIoSucces(int ioIndex);
    void ioActivate(int ioIndex, QStringList keyProperty, QStringList valueProperty);
    void ioTreeIsEmpty();

    // dev
    void addDevSucces(int ioIndex, QString devType, QStringList devKeyProperty, QStringList devValueProperty);
    void addDeviceFail(QString devName, QString errorMessage);
    void removeDevSucces(int ioIndex, int devIndex);
    void devExecComamndReady(int ioIndex, int devIndex, QStringList keys, QStringList values);
    void devConnected(int ioIndex, int devIndex, QString typeDev);
    void devReady(int ioIndex, int devIndex, QString typeDev);
    void devDisconnected(int ioIndex, int devIndex, QString typeDev);
    void devActivateProperty(QString devType, int ioIndex, int devIndex);
    void devUpdatePeriodicData(QString devType, int ioIndex, int devIndex, QStringList keys, QStringList values);
    void devUpdateLogMessage(int ioIndex, int devIndex, QString codeMessage, QString message);
    void ioAndDeviceFullFlushData();

    // update
    void isAvailableNewVersion(QString downloadUrl);

private:
    ModelDevTree ioTreeModel;
    std::shared_ptr<Peripherals> peripherals;
};

#endif // CONTROLLER_H
