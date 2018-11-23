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
    bool removeSessionByName(QString sessionName);
    QStringList getListSession();
    bool loadSession(QString sessionName);
    QString saveCurrentSession();
    QString saveCurrentSessionAs(QString sessionName);

private:
    SessionSecurity *sessionSecurity;
};

#endif // SESSION_H
