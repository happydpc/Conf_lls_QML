#ifndef DEVICECONTROLLER_H
#define DEVICECONTROLLER_H

#include <QObject>
#include "device/deviceCollector.h"
#include "device/devicesFactory.h"
#include <memory>
#include <QTimer>

class DeviceController : public QObject
{
    Q_OBJECT
public:
    explicit DeviceController();

signals:

public slots:
    DevicesFactory* getDeviceFactory();
    DeviceCollector* getDeviceCollector();

private slots:
    void updater();

private:
    std::shared_ptr<DevicesFactory> deviceFactory;
    std::shared_ptr<DeviceCollector> deviceCollector;

    std::unique_ptr<CommandController> commandController;
    std::unique_ptr<QTimer> updateTimer;
};

#endif // DEVICECONTROLLER_H
