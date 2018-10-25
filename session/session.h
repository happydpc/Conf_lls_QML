#ifndef SESSION_H
#define SESSION_H

#include <QObject>
#include <QVector>
#include <QPair>

class Session
{
public:
    Session();
    Session(QString sessionName);

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
//    QList<sDevices> getDevices();

private:
    bool isValid;
    QString sessionName;

    QList<sInterface> session;
};

#endif // SESSION_H
