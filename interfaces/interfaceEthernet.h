#ifndef INTERFACEETHERNET_H
#define INTERFACEETHERNET_H

#include <QObject>
#include "interfacesAbstract.h"

class InterfaceEthernet : public interfacesAbstract
{
    Q_OBJECT
public:
    explicit InterfaceEthernet();
//    InterfaceEthernet(const InterfaceEthernet & interface);
    ~InterfaceEthernet();

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

private slots:
    void aboutClose() override;

private:
    static constexpr char* typeName = "Ethernet";

};

#endif // INTERFACEETHERNET_H
