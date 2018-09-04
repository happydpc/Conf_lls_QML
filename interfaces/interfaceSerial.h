#ifndef INTERFACESERIAL_H
#define INTERFACESERIAL_H

#include <QObject>
#include "interfacesAbstract.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTimer>

class InterfaceSerial : public interfacesAbstract
{
    Q_OBJECT
public:
    InterfaceSerial();
    ~InterfaceSerial();
    InterfaceSerial(const InterfaceSerial &);

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

private slots:
    void aboutClose() override;

private:
    QSerialPort *portHandler = nullptr;

};

#endif // INTERFACESERIAL_H
