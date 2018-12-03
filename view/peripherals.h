#ifndef PERIPHERALS_H
#define PERIPHERALS_H

#include <QObject>
#include <future>
#include "connection/connectionFactory.h"
#include "connection/connectionComposition.h"
#include "device/deviceController.h"
#include "device/devicesFactory.h"
#include "command/commandController.h"

class Peripherals : public QObject
{
    Q_OBJECT
public:
    explicit Peripherals(QObject *parent = nullptr);

    // io
    bool addIo(const QString typeIoName, const QString ioName, const QStringList keyParam, const QStringList valueParam);
    void removeIo(int ioIndex);
    QStringList getAvailableIo(const QString IoTypeName) const;
    QPair<QStringList, QStringList> getIoProperty(int ioIndex) const;

    // dev
    bool addDev(int ioIndex, const QString devTypeName, const QStringList keyParam, const QStringList valueParam);
    void removeDev(int ioIndex, int devIndex);
    QString getDevType(int ioIndex, int devIndex) const;
    QPair<QString, QString> getDevProperty(int ioIndex, int devIndex) const;

    bool devExecCommand(int ioIndex, int devIndex,
                        QString comandType, QStringList keys, QStringList params);

public slots:
    void indexDevIsChanged(int ioIndex, int devIndex);
    void indexIoIsChanged(int ioIndex, int devIndex);

private:
    std::shared_ptr<ConnectionFactory> connFactory;
    std::shared_ptr<ConnectionComposition> connComposition;
    std::shared_ptr<CommandController> commands;
    std::shared_ptr<QTimer> updateStatusTimer;
};

#endif // PERIPHERALS_H
