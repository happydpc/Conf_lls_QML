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
    bool removeSession(QString sessionName);
    QList<Session> getSessionAll();
    Session getSessionByName(QString name);

    QString saveSession(Session & session);

signals:

public slots:

private:
    Database *database;
};

#endif // SESSIONSECURITY_H
