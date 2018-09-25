#ifndef INTERFACESERIAL_H
#define INTERFACESERIAL_H

#include <QObject>
#include "interfacesAbstract.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTimer>
#include "device/devicesFactory.h"

class InterfaceSerial : public interfacesAbstract
{
    Q_OBJECT
public:
    InterfaceSerial(QString devName, QStringList arg);
    ~InterfaceSerial();
public slots:

    void initInterface() override;
    bool openInterface(QString name, QStringList arg) override;
    bool isOpen() override;
    void closeInterface() override;
    bool sendData(QByteArray &pData) override;
    bool readData(QByteArray &pData) override;
    QString getInterfaceName() override;
    QStringList getInterfaceProperty() override;
    QStringList getAvailableList() override;
    QString getType() override;

    DevicesFactory* getDeviceFactory() override;

private slots:
    bool writeData(QByteArray data);
    void readData();

   void errorInterface(QString errorMessage);

private:
    DevicesFactory *deviceFactory;

private slots:
    void aboutClose() override;

private:

    static constexpr char* typeName = "Serial";

    QSerialPort *portHandler = nullptr;

};

#endif // INTERFACESERIAL_H
