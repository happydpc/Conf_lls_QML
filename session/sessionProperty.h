#ifndef SESSION_PROPERTY_H
#define SESSION_PROPERTY_H

#include <QObject>
#include <QVector>

class SessionProperty
{
public:
    SessionProperty();
    SessionProperty(std::string sessionName);

    typedef struct {
        std::string typeName;
        std::list<std::string> propKey;
        std::list<std::string> propValue;
    }sDevices;

    typedef struct {
        std::string name;
        std::string typeName;
        std::list<std::string> propKey;
        std::list<std::string> propValue;
        QList<sDevices>devices;
    }sInterface;

    void setSessionName(std::string sessionName);
    std::string getSessionName();

    void addInterface(sInterface value);
    void addDevice(sDevices device);

    void setIsValid(bool value);
    bool getIsValid();

    QList<sInterface> getInterfaces();

private:
    bool isValid;
    std::string sessionName;

    QList<sInterface> session;
};

#endif
