#ifndef SESSION_H
#define SESSION_H

#include <QObject>
#include <QVector>
#include <QPair>

class Session
{
public:
    Session();

    typedef struct {
        QString name;
        QString typeName;
        QStringList propKey;
        QStringList propValue;
    }sInterface;

    typedef struct {
        QString typeName;
        QString header;
        QString idName;
        QStringList propKey;
        QStringList propValue;
    }sDevices;

    void addInterface(sInterface value);
    void addDevice(sDevices value);

private:

    sInterface interface;
    QList<sDevices>devices;
};

#endif // SESSION_H
