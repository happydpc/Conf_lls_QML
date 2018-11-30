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

    Q_INVOKABLE QStringList getAvailableIoToAdd(const QString typeName);
    Q_INVOKABLE bool addIo(const QString typeIoName, const QString ioName, const QStringList keys, const QStringList params);
    Q_INVOKABLE void removeActiveIo();
    Q_INVOKABLE void removeActiveDev();
    Q_INVOKABLE bool addDevToIo(const QString ioName, const QString devTypeName, const QStringList keyParam, const QStringList valueParam);
    Q_INVOKABLE QStringList getDevAvailableType() const;
    Q_INVOKABLE bool devExecCommand(const QString ioName, const QString devIdName, const QString commandType,
                                    const QStringList keys, const QStringList params);

    Q_INVOKABLE QString getTypeLogo() const;

    Q_INVOKABLE ModelDevTree* getIoTreeModel();

signals:
    // io
    void addIoSucces(QString ioType, QStringList keyProperty, QStringList valueProperty);
    void addIoFail();
    void ioUpdateProperty(QString ioType, QStringList keyProperty, QStringList valueProperty);
    void ioReadyProperties(QString ioType, int ioIndex, QStringList keyProperty, QStringList valueProperty);
    void removeIoSucces(int ioIndex);
    void ioSetActiveProperty(int ioIndex, QString ioType);
    void ioTreeIsEmpty();

    // dev
    void addDevSucces(int ioIndex, QString devType, QStringList devKeyProperty, QStringList devValueProperty);
    void addDeviceFail(QString devName, QString errorMessage);
    void removeDeviceSucces(int ioIndex, int devIndex);
    void devSetActiveDeviceProperty(QString devType, int ioIndex, int devIndex);
    void devReadyProperties(QString typeDev, int ioIndex, int devIndex, QStringList keys, QStringList values);
    void devReadyPeriodicData(QString typeDev, int ioIndex, int devIndex, QStringList keys, QStringList values);
    void devConnected(int ioIndex, int devIndex, QString typeDev);
    void devReady(int ioIndex, int devIndex, QString typeDev);
    void devDisconnected(int ioIndex, int devIndex, QString typeDev);
    void devUpdateLogMessage(int ioIndex, int devIndex, QString codeMessage, QString message);
    void devReadyCheckCommand(int ioIndex, QString devTypeName, QString devId, QString devSn, QString result);
    void devReadyCheckCommand(int ioIndex, QString devTypeName, QString devId, QString devSn, bool result);
    void removeAllContent();
    void devUpdateLogMessage(int ioIndex, int devIndex, int codeMessage, QString message);

    void ioAndDeviceListIsEmpty();
    void isAvailableNewVersion(QString downloadUrl);

private slots:
    void eventFromPeripheral(const int ioIndex, const int devIndex, const QStringList keys, const QStringList param);

private:
    ModelDevTree ioTreeModel;
    std::shared_ptr<Peripherals> peripherals;
};

#endif // CONTROLLER_H
