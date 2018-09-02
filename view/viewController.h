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

    Q_INVOKABLE QString getCurrentInterfaceNameToSerial();

    Q_INVOKABLE int getDeviceCount();
    Q_INVOKABLE QStringList getDeviceHeaderByIndex(int index);

    Q_INVOKABLE QStringList getCurrentDevPropertyByIndex();

signals:
    void addDeviceSignal(QString name, bool is_checked);
    void addInterfaceSignal(QString name, bool is_checked);
    void changedDevicePropertyStackViewIndex(QString nameProperty);

//    void updateDeviceListSignal(QStringList);

    // отсылает сколько каких коннектов можно создать
//    void readyCreateNewConnections(int connecionsCountTypes);
//    // горит что что-то там открылось
//    void connectionOpened(QString nameInterface, QString subName);
//    // закрылось штатно
//    void connectionClosed(QString name);
//    // закрылось изза ошибки
//    void connectionClosedWithError(QString name);

//    // говорит какой из коннектов сейчас активен на форме
//    void activeCurrentInterface(QString nameInterface, int indexInterface,
//                                int activeDeviceIndex);

private slots:
    void connectionIsLost(interfacesAbstract::eInterfaceTypes, QString nameInterface);

//    void currentActiveConnectionIsChanged(interfacesAbstract::eInterfaceTypes, QString name, int index);



signals:

public slots:


private:
    ConnectionFactory *connFactory;

    int currentIndexInterface = 0;
    int currentDeviceIndex = 0;
};

#endif // VIEWCONTROLLER_H
