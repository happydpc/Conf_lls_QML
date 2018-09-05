#ifndef VIEWCONTROLLER_H
#define VIEWCONTROLLER_H

#include <QObject>

#include "connection/connectionFactory.h"

class ViewController : public QObject
{
    Q_OBJECT
public:
    explicit ViewController(QObject *parent = nullptr);

    Q_INVOKABLE QStringList getAvailableNameToSerialPort();
    Q_INVOKABLE bool addConnectionSerialPort(QString name, QString baudrate);

    Q_INVOKABLE QStringList getAvailableDeviceNameToSerialPort();

    Q_INVOKABLE bool addDeviceToConnection(QString devTypeName, QString idNum);

    Q_INVOKABLE void setChangedIndexDevice(int index);
    Q_INVOKABLE void setChangedIndexInteface(int index);

    Q_INVOKABLE QList<int> getCurrentDevChart();
    Q_INVOKABLE QList<QString> getCurrentDevOtherData();

    Q_INVOKABLE QString getCurrentInterfaceNameToSerial();

    Q_INVOKABLE int getDeviceCount();
    Q_INVOKABLE QStringList getDeviceHeaderByIndex(int index);

    Q_INVOKABLE QStringList getCurrentDevPropertyByIndex();

signals:
    void addDeviceSignal(QString name, bool is_checked);
    void addInterfaceSignal(QString name, bool is_checked);

    void updatePropertiesSerialPort_Signal(QStringList data);
    void updatePropertiesDevTmk24_Signal(QStringList data);
    void updatePropertiesDevTmk13_Signal(QStringList data);

    void updateDataDevTmk24_Signal(QStringList data);
    void updateDataDevTmk13_Signal(QStringList data);

    void updateDevTmk24_NoReady_Signal();
    void updateDevTmk13_NoReady_Signal();

private slots:
    void updateCurrentDataSlot();
    void connectionIsLost(interfacesAbstract::eInterfaceTypes, QString nameInterface);

private:
    ConnectionFactory *connFactory;

    typedef struct {
        int interfaceIndex;
        int deviceIndex;
    }sCurrentIndex;
    sCurrentIndex index = {0, 0};
    QTimer *updateCurrentDataDevTimer;
};

#endif // VIEWCONTROLLER_H
