#ifndef PERIPHERALS_H
#define PERIPHERALS_H

#include <QObject>
#include "connection/connectionFactory.h"
#include "connection/connectionComposition.h"
#include "device/devicesFactory.h"

class Peripherals : public QObject
{
    Q_OBJECT
public:
    explicit Peripherals(QObject *parent = nullptr);

    // io
    bool addIo(const std::string typeIoName, const std::string ioName, const std::list<std::string> keyParam, const std::list<std::string> valueParam);
    void removeIo(int ioIndex);
    std::pair<std::list<std::string>, std::list<std::string>> getIoProperty(int ioIndex) const;
    std::list<std::string> getAvailableIo(const std::string IoTypeName) const;

    // dev
    bool addDev(int ioIndex, const std::string devTypeName, const std::list<std::string> keyParam, const std::list<std::string> valueParam);
    void removeDev(int ioIndex, int devIndex);
    std::pair<std::list<std::string>, std::list<std::string>> getDevProperty(int ioIndex, int devIndex) const;
    std::list<std::string> getAvailableDev() const;

    bool devExecCommand(int ioIndex, int devIndex,
                        std::string comandType, std::list<std::string> keys, std::list<std::string> params);

signals:
    // io
    void ioUpdatePropertySignal(std::string ioType, int ioIndex, std::list<std::string> keyProperty, std::list<std::string> valueProperty);
    void ioActivateSignal(int ioIndex, std::list<std::string> keyProperty, std::list<std::string> valueProperty);
    void ioTreeIsEmptySignal();
    // dev
    void devExecComamndReadySignal(int ioIndex, int devIndex, std::list<std::string> keys, std::list<std::string> values);
    void devConnectedSignal(int ioIndex, int devIndex, std::string typeDev);
    void devReadySignal(int ioIndex, int devIndex, std::string typeDev);
    void devDisconnectedSignal(int ioIndex, int devIndex, std::string typeDev);
    void devActivatePropertySignal(std::string devType, int ioIndex, int devIndex);
    void devUpdatePeriodicDataSignal(std::string devType, int ioIndex, int devIndex, std::list<std::string> keys, std::list<std::string> values);
    void devUpdateLogMessageSignal(int ioIndex, int devIndex, std::string codeMessage, std::string message);

private:
    std::shared_ptr<ConnectionFactory> connFactory;
    std::shared_ptr<ConnectionComposition> connComposition;
};

#endif // PERIPHERALS_H
