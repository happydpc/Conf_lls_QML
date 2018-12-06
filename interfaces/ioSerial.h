#ifndef IO_CESERIAL_H
#define IO_SERIAL_H

#include <QObject>
#include <memory>
#include "ioAbstract.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTimer>

class IoSerial : public IoAbstract
{
    Q_OBJECT
public:
    IoSerial(QString name, QPair<QStringList,QStringList>param);
    ~IoSerial() override;

public slots:
    void initInterface() override;
    bool openInterface() override;
    bool isOpen() override;
    void closeInterface() override;
    bool sendData(QByteArray pData) override;
    bool readData(QByteArray &pData) override;
    QString getInterfaceName() override;
    QPair<QStringList,QStringList> getInterfaceProperty() override;
    QStringList getAvailableList() override;
    QString getType() override;

private slots:
    void errorHanler(QSerialPort::SerialPortError err);
private:
    static constexpr char* typeName = (char*)"serial";
    bool isManualClosed;
    std::shared_ptr<QSerialPort> portHandler = nullptr;
    QString name;
    QPair<QStringList,QStringList>param;
};

#endif
