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
    std::pair<std::vector<std::string>, std::vector<std::string>> getIoProperty(int ioIndex) const;

    bool addDev(int ioIndex, DeviceAbstract* dev);
    void removeDev(int ioIndex, int devIndex);
    uint16_t getDevCount(int ioIndex) const;

    std::string getIoStatus(int ioIndex) const;
    std::string getDevStatus(int ioIndex, int devIndex) const;

    std::pair<std::vector<std::string>, std::vector<std::string>> getDevProperty(int ioIndex, int devIndex) const;

    bool devExecFutureCommand(int ioIndex, int devIndex, const std::string &comandType,
                              const std::vector<std::string> &keys, const std::vector<std::string> &params);

signals:
    void devExecReadyCommand(const std::string commandType);

private:
    std::vector<IoAbstract*> ioList;
};

#endif // CONNECTION_COMPOSITION_H
