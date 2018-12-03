#ifndef CONNECTIONFACTORY_H
#define CONNECTIONFACTORY_H

#include <QObject>
#include <QVector>
#include <QMutex>
#include <memory>
#include "connection/connectionComposition.h"

class ConnectionFactory : public QObject
{
    Q_OBJECT
public:
    explicit ConnectionFactory();
    ~ConnectionFactory();

public slots:

    IoAbstract* createConnection(const QString ioTypeName, const QString ioName, const QPair<QStringList,QStringList> param);
    QStringList getAvailableName(const QString ioTypeName) const;

private:
    std::shared_ptr<QMutex> lockInterface;
};

#endif // CONNECTIONFACTORY_H
