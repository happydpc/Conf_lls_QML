#ifndef SESSIONSECURITY_H
#define SESSIONSECURITY_H

#include <QObject>
#include <memory>
#include "sessionProperty.h"
#include "database/database.h"
#include <QList>

class SessionSecurity : public QObject
{
    Q_OBJECT
public:
    explicit SessionSecurity(QObject *parent = nullptr);
    ~SessionSecurity();
    std::list<std::string> getAvailableSessions() const;
    bool removeSession(const std::string sessionName);
    QList<SessionProperty> getSessionAll() const;
    SessionProperty getSessionByName(const std::string name);
    std::string saveSession(SessionProperty & session);

signals:

public slots:

private:

    SessionProperty sess;
    std::unique_ptr<Database> database;
};

#endif // SESSIONSECURITY_H
