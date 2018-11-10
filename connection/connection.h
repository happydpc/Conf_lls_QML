#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include "interfaces/interfacesAbstract.h"
#include "device/deviceController.h"
#include <memory.h>

class Connection : public QObject {
    Q_OBJECT
public:
    explicit Connection(QString typeName, QString name, QPair<QStringList,QStringList> param);
    interfacesAbstract* getInterfaceAbstract();
    void closeAndClear();

    DeviceController* getDeviceController();

signals:
    void errorConnection(QString ioType, QString message);

private:
    std::shared_ptr<interfacesAbstract> connAbstract;
    std::shared_ptr<DeviceController> deviceController;
};

#endif // CONNECTION_H
