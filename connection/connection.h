#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include "interfaces/interfacesAbstract.h"
#include "device/deviceController.h"
#include <memory.h>

class Connection : public QObject {
    Q_OBJECT
public:
    explicit Connection(const QString typeName, const QString name, const QPair<QStringList,QStringList> param);
    interfacesAbstract* getInterfaceAbstract();
    DeviceController* getDeviceController();
    void closeAndClear();

signals:
    void errorConnection(const QString ioType, const QString message);

private:
    std::shared_ptr<interfacesAbstract> connAbstract;
    std::shared_ptr<DeviceController> deviceController;
};

#endif // CONNECTION_H
