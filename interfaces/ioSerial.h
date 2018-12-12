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
    IoSerial(std::string name, std::pair<std::vector<std::string>,std::vector<std::string>>param);
    ~IoSerial() override;

public slots:
    void initInterface() override;
    bool openInterface() override;
    bool isOpen() override;
    void closeInterface() override;
    bool sendData(QByteArray pData) override;
    bool readData(QByteArray &pData) override;
    std::string getInterfaceName() override;
    std::pair<std::vector<std::string>,std::vector<std::string>> getInterfaceProperty() override;
    std::vector<std::string> getAvailableList() override;
    std::string getType() override;

private slots:
    void errorHanler(QSerialPort::SerialPortError err);
private:
    static constexpr char* typeName = (char*)"serial";
    bool isManualClosed;
    std::shared_ptr<QSerialPort> portHandler = nullptr;
    std::string name;
    std::pair<std::vector<std::string>,std::vector<std::string>>param;
};

#endif
