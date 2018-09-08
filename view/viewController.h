#ifndef VIEWCONTROLLER_H
#define VIEWCONTROLLER_H

#include <QObject>

#include "connection/connectionFactory.h"

class ViewController : public QObject
{
    Q_OBJECT
public:
    explicit ViewController(QObject *parent = nullptr);

    Q_INVOKABLE bool addConnectionSerialPort(QString name, QString baudrate);
    Q_INVOKABLE bool removeActiveConnectionSerialPort();

    Q_INVOKABLE QStringList getAvailableNameToSerialPort();
    Q_INVOKABLE QStringList getAvailableDeviceNameToSerialPort();

    Q_INVOKABLE bool addDeviceToConnection(QString devTypeName, QString idNum, QString password);
    Q_INVOKABLE void removeActiveDevice();

    Q_INVOKABLE void setChangedIndexDevice(int index);
    Q_INVOKABLE void setChangedIndexInteface(int index);

    Q_INVOKABLE QList<int> getCurrentDevChart();
    Q_INVOKABLE QList<QString> getCurrentDevOtherData();

    Q_INVOKABLE QString getCurrentInterfaceNameToSerial();

    Q_INVOKABLE int getDeviceCount();
    Q_INVOKABLE QStringList getDeviceHeaderByIndex(int index);

    Q_INVOKABLE QStringList getCurrentDevPropertyByIndex();

    Q_INVOKABLE void setCurrentDevLevelAsEmpty();
    Q_INVOKABLE void setCurrentDevLevelAsFull();

signals:
    void remakeInterfaceTree(QStringList list, QList<int>status);
    void changeInterfaceTreeStatus(int index, int status);

    void remakeDeviceTree(QStringList list, QList<int>status);
    void changeDeviceTreeStatus(int index, int status);

    void updatePropertiesSerialPort(QStringList properties);

    void addConnectionFail(QString devName);
    void addDeviceFail(QString devName);

    void devConnectedTmk24();
    void devConnectedTmk13();
    void devDisconnectedTmk24();
    void devDisconnectedTmk13();

    void devReadyPropertiesTmk24(QStringList data);
    void devReadyPropertiesTmk13(QStringList data);

    void devReadyOtherDataTmk24(QStringList data);
    void devReadyOtherDataTmk13(QStringList data);

    void devFullReadyTmk24(QStringList data);
    void devFullReadyTmk13(QStringList data);

    void devUpdatePasswordIncorrect(QString devNameId);

    void devUpdateTypeDevIncorrect(QString devNameId);

    void devUpdateTree(QStringList devNames, QList<int>status);

private slots:
    void deviceConnected(DevicesFactory::E_DeviceType, QString uniqNameId);
    void deviceDisconnected(DevicesFactory::E_DeviceType, QString uniqNameId);
    void deviceReadyCurrentData(DevicesFactory::E_DeviceType, QString uniqNameId);
    void deviceReadyProperties(DevicesFactory::E_DeviceType, QString uniqNameId);
    void deviceReadyInit(DevicesFactory::E_DeviceType, QString uniqNameId);

    void interfaceTreeChanged(ConnectionFactory::E_ConnectionUpdateType type);
    void deviceTreeChanged(DevicesFactory::E_DeviceUpdateType type, int index);

    bool isCurrentDevice(QString uniqNameId);

    void connectToDevSignals();
    void disconnectToDevSignals();

    DevicesFactory* getDeviceFactoryByIndex(int index);

    int getInterfaceCount();

private:
    ConnectionFactory *connFactory;

    typedef struct {
        int interfaceIndex;
        int deviceIndex;
    }sCurrentIndex;
    sCurrentIndex index = {0, 0};
};

#endif // VIEWCONTROLLER_H
