#ifndef DEVICECONTROLLER_H
#define DEVICECONTROLLER_H

#include <QObject>
#include "device/deviceCollector.h"
#include "device/devicesFactory.h"
#include "interfaces/interfacesAbstract.h"
#include <memory>
#include <QTimer>

class DeviceController : public QObject {
    Q_OBJECT
public:
    explicit DeviceController(interfacesAbstract *p_int_abstract);

public slots:
    bool addDevice(QString devTypeName, QStringList keyParam, QStringList valueParam);
    bool removeDevice(QString devId);
    DevicesFactory* getDeviceFactory();
    DeviceCollector* getDeviceCollector();
    void resetAll();

    bool sendCustomCommadToDev(int indexDev, QString operation, QStringList keys, QStringList values);
//    bool sendCustomCommadToDev(int indexDev, QString operation);
//    void setDeviceCommandUpdateByIndex(int index);
//    void setDeviceInitCommandByIndex(int index);
    void setDeviceReInitByIndex(int indexDev);
//    void sendCustomCommandUseCallback(QString devType, QString operation, QStringList keys, QStringList values);
private slots:
    void updater();
signals:
    void readySendData(QByteArray data);
    void readyGetData();

private:
    std::shared_ptr<DevicesFactory> deviceFactory;
    std::shared_ptr<DeviceCollector> deviceCollector;
    // services create at interfaces
    // root - interfaces
    // second list - same types services (tmk24, nozzle...and etc)
    QList<std::shared_ptr<ServiceDevicesAbstract>> serviceList;
    std::unique_ptr<QTimer> updateTimer;
    std::unique_ptr<QMutex> devMutex;
};

#endif // DEVICECONTROLLER_H
