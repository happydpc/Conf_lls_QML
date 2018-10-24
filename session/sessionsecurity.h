#ifndef SESSIONSECURITY_H
#define SESSIONSECURITY_H

#include <QObject>
#include "session.h"
#include "database/database.h"
#include <QList>

class SessionSecurity : public QObject
{
    Q_OBJECT
public:
    explicit SessionSecurity(QObject *parent = nullptr);

    QStringList getAvailableSessions();
    QList<Session> getSessionAll();

    Session* getByName(QString sessionName);
    bool saveByName(QString sessionName);
    bool saveAuto();

//    Q_INVOKABLE QStringList getListSession();
//    Q_INVOKABLE QString saveCurrentSession();
//    Q_INVOKABLE QString saveCurrentSessionAs(QString sessionName);
//    Q_INVOKABLE bool loadSession(QString sessionName);

signals:

public slots:

private:
    Database *database;
};

#endif // SESSIONSECURITY_H
