#ifndef SESSION_PROPERTY_H
#define SESSION_PROPERTY_H

#include <QObject>
#include <QVector>
#include <QPair>

class SessionProperty
{
public:
    SessionProperty();
    SessionProperty(QString sessionName);

    typedef struct {
        QString typeName;
        QStringList propKey;
        QStringList propValue;
    }sDevices;

    typedef struct {
        QString name;
        QString typeName;
        QStringList propKey;
        QStringList propValue;
        QList<sDevices>devices;
    }sInterface;

    void setSessionName(QString sessionName);
    QString getSessionName();

    void addInterface(sInterface value);
    void addDevice(sDevices device);

    void setIsValid(bool value);
    bool getIsValid();

    QList<sInterface> getInterfaces();

private:
    bool isValid;
    QString sessionName;

    QList<sInterface> session;
};

#endif
