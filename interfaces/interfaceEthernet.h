#ifndef INTERFACEETHERNET_H
#define INTERFACEETHERNET_H

#include <QObject>
#include "interfacesAbstract.h"

class InterfaceEthernet : public interfacesAbstract
{
    Q_OBJECT
public:
    explicit InterfaceEthernet();
    InterfaceEthernet(const InterfaceEthernet & interface);
    ~InterfaceEthernet();

public slots:

    void initInterface() override;
    bool openInterface(QString name, QStringList arg) override;
    bool isOpen() override;
    void closeInterface() override;
    bool sendData(QByteArray &pData) override;
    bool readData(QByteArray &pData) override;
    QString getInterfaceName() override;
    QStringList getInfoInterface(QString name) override;
    QStringList getAvailableList() override;

private slots:
    void aboutClose() override;

private:

};

#endif // INTERFACEETHERNET_H
