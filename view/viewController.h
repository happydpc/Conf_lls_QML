#ifndef VIEWCONTROLLER_H
#define VIEWCONTROLLER_H

#include <QObject>

#include "connection/connectionFactory.h"

class ViewController : public QObject
{
    Q_OBJECT
public:
    explicit ViewController(QObject *parent = nullptr);

    Q_INVOKABLE QStringList getAvailableNameToSerialPort();
    Q_INVOKABLE bool addConnectionSerialPort(QString name, QString baudrate);

    Q_INVOKABLE QStringList getAvailableDeviceNameToSerialPort();

    Q_INVOKABLE bool addDeviceToConnection(QString devTypeName, QString idNum);

    Q_INVOKABLE void setChangedIndexDevice(int index);
    Q_INVOKABLE void setChangedIndexInteface(int index);

    Q_INVOKABLE QList<int> getCurrentDevChart();
    Q_INVOKABLE QList<QString> getCurrentDevOtherData();

    Q_INVOKABLE QString getCurrentInterfaceNameToSerial();

    Q_INVOKABLE int getDeviceCount();
    Q_INVOKABLE QStringList getDeviceHeaderByIndex(int index);

    Q_INVOKABLE QStringList getCurrentDevPropertyByIndex();

signals:
    void addDeviceSignal(QString name);
    void addInterfaceSignal(QString name);

    void updatePropertiesSerialPort(QStringList properties);

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

private slots:
    void connectionIsLost(interfacesAbstract::eInterfaceTypes, QString nameInterface);

    void deviceConnected(DevicesFactory::E_DeviceType, QString uniqNameId);
    void deviceDisconnected(DevicesFactory::E_DeviceType, QString uniqNameId);
    void deviceReadyCurrentData(DevicesFactory::E_DeviceType, QString uniqNameId);
    void deviceReadyProperties(DevicesFactory::E_DeviceType, QString uniqNameId);
    void deviceReadyInit(DevicesFactory::E_DeviceType, QString uniqNameId);

    bool isCurrentDevice(QString uniqNameId);

    void reconnectToDevSignals();

    DevicesFactory* getDeviceFactoryByIndex(int index);

private:
    ConnectionFactory *connFactory;

    typedef struct {
        int interfaceIndex;
        int deviceIndex;
    }sCurrentIndex;
    sCurrentIndex index = {0, 0};
};

#endif // VIEWCONTROLLER_H
