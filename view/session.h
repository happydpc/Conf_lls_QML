#ifndef SESSION_H
#define SESSION_H

#include <QObject>
#include "./session/sessionSecurity.h"

class Session : public QObject
{
    Q_OBJECT
public:
    explicit Session(QObject *parent = nullptr);

    void resetSession();
    bool removeSessionByName(std::string sessionName);
    std::list<std::string> getListSession();
    bool loadSession(std::string sessionName);
    std::string saveCurrentSession();
    std::string saveCurrentSessionAs(std::string sessionName);

private:
    SessionSecurity *sessionSecurity;
};

#endif // SESSION_H
