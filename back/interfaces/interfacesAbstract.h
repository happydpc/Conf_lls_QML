#ifndef INTERFACES_H
#define INTERFACES_H

#include <QObject>
#include <QStringList>

class interfacesAbstract : public QObject
{
    Q_OBJECT
public:
    explicit interfacesAbstract();
    ~interfacesAbstract();

    typedef enum {
        InterfaceTypeSerialPort,
        InterfaceTypeBle,
        InterfaceTypeEthrnet,
    }eInterfaceTypes;

public slots:

    virtual void initInterface() = 0;
    virtual bool openInterface(QString name, QStringList arg) = 0;
    virtual bool isOpen() = 0;
    virtual void closeInterface() = 0;
    virtual bool sendData(QByteArray &pData) = 0;
    virtual bool readData(QByteArray &pData) = 0;
    virtual QString getInterfaceName() = 0;
    virtual QStringList getInterfaceProperty() = 0;
    virtual QStringList getAvailableList() = 0;

private slots:
    virtual void aboutClose() = 0;

signals:
    void errorInterface(QString errorMessage);
    void openIsNormam();
    void closeIsNormal();

};

#endif // INTERFACES_H
