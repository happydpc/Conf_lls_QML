#ifndef SESSIONSECURITY_H
#define SESSIONSECURITY_H

#include <QObject>
#include <memory>
#include "session.h"
#include "database/database.h"
#include <QList>

class SessionSecurity : public QObject
{
    Q_OBJECT
public:
    explicit SessionSecurity(QObject *parent = nullptr);
    ~SessionSecurity();
    QStringList getAvailableSessions() const;
    bool removeSession(const QString sessionName);
    QList<Session> getSessionAll() const;
    Session getSessionByName(const QString name);
    QString saveSession(Session & session);

signals:

public slots:

private:
    std::unique_ptr<Database> database;
};

#endif // SESSIONSECURITY_H
