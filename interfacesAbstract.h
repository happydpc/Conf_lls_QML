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

    virtual QStringList getAvailableInterfaceList() = 0;

signals:

public slots:
};

#endif // INTERFACES_H
