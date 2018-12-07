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

    std::list<std::string> getSessionsCountAvailable() const;
    std::list<std::string> getSessionsAll() const;
    bool sendRemoveSession(const std::string sessionName);
    bool sendSaveSession(const std::string sessionName, const std::string jsonData);

private:

    QSqlDatabase database;

signals:

public slots:
};

#endif // DATABASE_H
