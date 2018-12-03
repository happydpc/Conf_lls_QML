#ifndef PERIPHERALS_H
#define PERIPHERALS_H

#include <QObject>
#include <future>
#include "connection/connectionFactory.h"
#include "connection/connectionComposition.h"
#include "device/deviceController.h"

class Peripherals : public QObject
{
    Q_OBJECT
public:
    explicit Peripherals(QObject *parent = nullptr);

    // io
    bool addIo(const QString typeIoName, const QString ioName, const QStringList keyParam, const QStringList valueParam);
    bool removeIo(int ioIndex);
    QStringList getAvailableIo(const QString IoTypeName) const;
    QPair<QStringList, QStringList> getIoProperty(int ioIndex) const;

    // dev
    bool addDev(int ioIndex, const QString devName, const QStringList keyParam, const QStringList valueParam);
    bool removeDev(int ioIndex, int devIndex);
    QString getDevType(int ioIndex, int devIndex) const;
    QPair<QString, QString> getDevProperty(int ioIndex, int devIndex) const;

    bool devSendCustomCommand(const QString ioName, const QString devName, QString comandType,
                              QStringList keys, QStringList params);

public slots:
    void indexDevIsChanged(int ioIndex, int devIndex);
    void indexIoIsChanged(int ioIndex, int devIndex);

private:
    std::shared_ptr<ConnectionFactory> connFactory;
    std::shared_ptr<ConnectionComposition> connComposition;
    std::shared_ptr<QTimer> updateStatusTimer;
};

#endif // PERIPHERALS_H
