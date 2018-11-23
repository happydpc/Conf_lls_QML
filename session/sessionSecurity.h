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
    QStringList getAvailableSessions() const;
    bool removeSession(const QString sessionName);
    QList<SessionProperty> getSessionAll() const;
    SessionProperty getSessionByName(const QString name);
    QString saveSession(SessionProperty & session);

signals:

public slots:

private:

    SessionProperty sess;
    std::unique_ptr<Database> database;
};

#endif // SESSIONSECURITY_H
