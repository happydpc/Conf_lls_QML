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
    bool addIo(const std::vector<std::string> keyParam, const std::vector<std::string> valueParam);
    void removeIo(int ioIndex);
    std::pair<std::vector<std::string>, std::vector<std::string>> getIoProperty(int ioIndex) const;
    std::string getIoStatus(int ioIndex) const;
    std::vector<std::string> getAvailableIo(const std::string IoTypeName) const;
    int getIoCount(const int ioIndex) const;

    // dev
    bool addDev(int ioIndex, const std::vector<std::string> keyParam, const std::vector<std::string> valueParam);
    void removeDev(int ioIndex, int devIndex);
    std::pair<std::vector<std::string>, std::vector<std::string>> getDevProperty(int ioIndex, int devIndex) const;
    std::string getDevStatus(int ioIndex, int devIndex) const;
    std::vector<std::string> getAvailableDev() const;
    int getDevCount(const int ioIndex, const int devIndex) const;
    bool devExecCommand(int ioIndex, int devIndex,
                        std::string comandType, std::vector<std::string> keys, std::vector<std::string> params);

signals:
    // io
    void ioUpdatePropertySignal(std::string ioType, int ioIndex, std::vector<std::string> keyProperty, std::vector<std::string> valueProperty);
    void ioActivateSignal(int ioIndex, std::vector<std::string> keyProperty, std::vector<std::string> valueProperty);
    void ioTreeIsEmptySignal();
    // dev
    void devExecComamndReadySignal(int ioIndex, int devIndex, std::vector<std::string> keys, std::vector<std::string> values);
    void devConnectedSignal(int ioIndex, int devIndex, std::string typeDev);
    void devReadySignal(int ioIndex, int devIndex, std::string typeDev);
    void devDisconnectedSignal(int ioIndex, int devIndex, std::string typeDev);
    void devActivatePropertySignal(std::string devType, int ioIndex, int devIndex);
    void devUpdatePeriodicDataSignal(std::string devType, int ioIndex, int devIndex, std::vector<std::string> keys, std::vector<std::string> values);
    void devUpdateLogMessageSignal(int ioIndex, int devIndex, std::string codeMessage, std::string message);

private:
    std::shared_ptr<ConnectionFactory> connFactory;
    std::shared_ptr<ConnectionComposition> connComposition;
};

#endif // PERIPHERALS_H
