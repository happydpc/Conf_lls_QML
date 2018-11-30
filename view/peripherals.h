#ifndef PERIPHERALS_H
#define PERIPHERALS_H

#include <QObject>
#include <future>
#include "connection/connectionFactory.h"
#include "device/deviceController.h"

class Peripherals : public QObject
{
    Q_OBJECT
public:
    explicit Peripherals(QObject *parent = nullptr);

    // io
    QStringList getAvailableIo(const QString typeIoName) const ;
    std::future<bool> addIo(const QString typeIoName, const QString ioName, const QStringList keyParam, const QStringList valueParam);
    bool removeIo(const QString ioName);
    QString getCurrentIoName() const;

    // dev
    std::future<bool> addDev(const QString ioName, const QString devName, const QStringList keyParam, const QStringList valueParam);
    bool removeDev(const QString ioName, const QString devName);
    QString getCurrentDevName() const;
    QString getDevType() const;
    QPair<QString, QString> getDevProperty(const QString ioName, const QString devName) const;

    bool devSendCustomCommand(const QString ioName, const QString devName,
                              QString comandType, QStringList keys, QStringList params);

public slots:
    void indexDevIsChanged(int ioIndex, int devIndex);
    void indexIoIsChanged(int ioIndex, int devIndex);
private:
    std::shared_ptr<ConnectionFactory> connFactory;
    std::shared_ptr<DeviceController> deviceController;
    std::shared_ptr<QTimer> updateIoStatusTimer;
};

#endif // PERIPHERALS_H
