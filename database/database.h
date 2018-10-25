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

    QStringList getSessionsCountAvailable();
    bool getSessionsAll(QStringList &jsonResult);
    bool sendRemoveSession(QString sessionName);
    bool sendSaveSession(QString sessionName, QString jsonData);

private:

    QSqlDatabase database;

signals:

public slots:
};

#endif // DATABASE_H
