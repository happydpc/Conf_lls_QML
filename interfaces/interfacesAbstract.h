#ifndef INTERFACES_H
#define INTERFACES_H

#include <QObject>
#include <QStringList>
#include "device/devicesFactory.h"

class interfacesAbstract : public QObject
{
    Q_OBJECT
public:
    explicit interfacesAbstract(QObject *parent = nullptr);

public slots:

    virtual void initInterface() = 0;
    virtual bool openInterface() = 0;
    virtual bool isOpen() = 0;
    virtual void closeInterface() = 0;
    virtual bool sendData(QByteArray &pData) = 0;
    virtual bool readData(QByteArray &pData) = 0;
    virtual QString getType() = 0;
    virtual QString getInterfaceName() = 0;
    virtual QStringList getInterfaceProperty() = 0;
    virtual QStringList getAvailableList() = 0;
    virtual DevicesFactory* getDeviceFactory() = 0;

private slots:
    virtual void aboutClose() = 0;

signals:
    void errorInterface(QString errorMessage);
    void openIsNormam();
    void closeIsNormal();

};

#endif // INTERFACES_H
