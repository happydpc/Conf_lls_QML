#ifndef INTERFACEBLE_H
#define INTERFACEBLE_H

#include <QObject>
#include "interfacesAbstract.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class InterfaceBLE : public interfacesAbstract
{
    Q_OBJECT
public:
    explicit InterfaceBLE();
    ~InterfaceBLE();

public slots:

    void initInterface() override;
    bool openInterface() override;
    bool isOpen() override;
    void closeInterface() override;
    bool sendData(QByteArray &pData) override;
    bool readData(QByteArray &pData) override;
    QString getInterfaceName() override;
    QPair<QStringList,QStringList> getInterfaceProperty() override;
    QStringList getAvailableList() override;
    QString getType() override;

private:

    static constexpr char* typeName = "BLE";
};

#endif // INTERFACEBLE_H
