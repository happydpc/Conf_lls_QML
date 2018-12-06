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
    bool addIo(const QString typeIoName, const QString ioName, const QStringList keyParam, const QStringList valueParam);
    void removeIo(int ioIndex);
    QPair<QStringList, QStringList> getIoProperty(int ioIndex) const;
    QStringList getAvailableIo(const QString IoTypeName) const;

    // dev
    bool addDev(int ioIndex, const QString devTypeName, const QStringList keyParam, const QStringList valueParam);
    void removeDev(int ioIndex, int devIndex);
    QPair<QStringList, QStringList> getDevProperty(int ioIndex, int devIndex) const;
    QStringList getAvailableDev() const;

    bool devExecCommand(int ioIndex, int devIndex,
                        QString comandType, QStringList keys, QStringList params);

signals:
    // io
    void ioUpdatePropertySignal(QString ioType, int ioIndex, QStringList keyProperty, QStringList valueProperty);
    void ioActivateSignal(int ioIndex, QStringList keyProperty, QStringList valueProperty);
    void ioTreeIsEmptySignal();
    // dev
    void devExecComamndReadySignal(int ioIndex, int devIndex, QStringList keys, QStringList values);
    void devConnectedSignal(int ioIndex, int devIndex, QString typeDev);
    void devReadySignal(int ioIndex, int devIndex, QString typeDev);
    void devDisconnectedSignal(int ioIndex, int devIndex, QString typeDev);
    void devActivatePropertySignal(QString devType, int ioIndex, int devIndex);
    void devUpdatePeriodicDataSignal(QString devType, int ioIndex, int devIndex, QStringList keys, QStringList values);
    void devUpdateLogMessageSignal(int ioIndex, int devIndex, QString codeMessage, QString message);

private:
    std::shared_ptr<ConnectionFactory> connFactory;
    std::shared_ptr<ConnectionComposition> connComposition;
};

#endif // PERIPHERALS_H
