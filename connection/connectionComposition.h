#ifndef CONNECTION_COMPOSITION_H
#define CONNECTION_COMPOSITION_H

#include <QObject>
#include "interfaces/ioAbstract.h"
#include "device/deviceAbstract.h"
#include <memory.h>

class ConnectionComposition : public QObject {
    Q_OBJECT
public:
    explicit ConnectionComposition();

    bool addIo(IoAbstract * io);
    void removeIo(int ioIndex);
    void removeIoAll();
    uint16_t getIoCount() const ;
    QPair<QString, QString> getIoProperty(int ioIndex) const;

    bool addDev(int ioIndex, DeviceAbstract* dev);
    void removeDev(int ioIndex, int devIndex);
    uint16_t getDevCount(int ioIndex) const;

    bool getIoIsConnected(int ioIndex) const;
    bool getDevIsConnected(int ioIndex, int devIndex) const;

    QPair<QString, QString> getDevProperty(int ioIndex, int devIndex) const;

    bool devExecFutureCommand(int ioIndex, int devIndex, const QString &comandType,
                              const QStringList &keys, const QStringList &params);

private:
    std::vector<IoAbstract*> ioList;
};

#endif // CONNECTION_COMPOSITION_H
