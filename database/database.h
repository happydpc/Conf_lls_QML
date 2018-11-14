#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <memory>

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = nullptr);

    ~Database();

    QStringList getSessionsCountAvailable() const;
    QStringList getSessionsAll() const;
    bool sendRemoveSession(const QString sessionName);
    bool sendSaveSession(const QString sessionName, const QString jsonData);

private:

    QSqlDatabase database;

signals:

public slots:
};

#endif // DATABASE_H
