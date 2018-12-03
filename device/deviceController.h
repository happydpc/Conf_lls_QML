#ifndef DEVICECONTROLLER_H
#define DEVICECONTROLLER_H

#include <QObject>
#include "device/deviceCollector.h"
#include "device/devicesFactory.h"
#include "interfaces/ioAbstract.h"
#include <memory>
#include <QTimer>

class DeviceController : public QObject {
    Q_OBJECT
public:
    explicit DeviceController(IoAbstract *p_int_abstract);

public slots:
    bool addDevice(const QString devTypeName, const QStringList keyParam, const QStringList valueParam);
    bool removeDevice(const QString devId);
    DevicesFactory* getDeviceFactory() const;
    DeviceCollector* getDeviceCollector() const;
    void resetAll();
    bool sendCommadToDev(const QString operation, const QStringList keys, const QStringList values);
    QStringList exeCommadToDev(const QString operation, const QStringList keys, const QStringList values);
    void setDeviceReInitByIndex(const int indexDev);
private slots:
    void updater();
signals:
    void readySendData(const QByteArray data);
    void readyGetData();

private:
    std::shared_ptr<DevicesFactory> deviceFactory;
    std::shared_ptr<DeviceCollector> deviceCollector;
    // services create at interfaces
    // root - interfaces
    // second list - same types services (tmk24, nozzle...and etc)
    QList<std::shared_ptr<ServiceDevicesAbstract>> serviceList;
    std::shared_ptr<QTimer> updateTimer;
    std::shared_ptr<QMutex> devMutex;
};

#endif // DEVICECONTROLLER_H
