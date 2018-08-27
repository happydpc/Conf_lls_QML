#ifndef INTERFACES_H
#define INTERFACES_H

#include <QObject>
#include <QStringList>

class interfacesAbstract : public QObject
{
    Q_OBJECT
public:
    explicit interfacesAbstract(QObject *parent = nullptr);
    ~interfacesAbstract();

    typedef enum {
        InterfaceTypeSerialPort,
        InterfaceTypeBle,
        InterfaceTypeEthrnet,
    }eInterfaceTypes;

    typedef enum {
        IntefaceMessage_Opened,
        IntefaceMessage_Closed,
        IntefaceMessage_ErrorWithClose
    }eInterfaceMessageType;

    virtual QStringList getAvailableInterfaceList() = 0;
    virtual bool openInterface(QString, int *arg) = 0;
    virtual bool closeInterface() = 0;

public slots:
};

#endif // INTERFACES_H
