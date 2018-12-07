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
    std::pair<std::list<std::string>, std::list<std::string>> getIoProperty(int ioIndex) const;

    bool addDev(int ioIndex, DeviceAbstract* dev);
    void removeDev(int ioIndex, int devIndex);
    uint16_t getDevCount(int ioIndex) const;

    bool getIoIsConnected(int ioIndex) const;
    bool getDevIsConnected(int ioIndex, int devIndex) const;

    std::pair<std::list<std::string>, std::list<std::string>> getDevProperty(int ioIndex, int devIndex) const;

    bool devExecFutureCommand(int ioIndex, int devIndex, const std::string &comandType,
                              const std::list<std::string> &keys, const std::list<std::string> &params);

private:
    std::vector<IoAbstract*> ioList;
};

#endif // CONNECTION_COMPOSITION_H
