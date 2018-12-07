#ifndef CONNECTIONFACTORY_H
#define CONNECTIONFACTORY_H

#include <QObject>
#include <QVector>
#include <QMutex>
#include <memory>
#include "interfaces/ioAbstract.h"

class ConnectionFactory : public QObject
{
    Q_OBJECT
public:
    explicit ConnectionFactory();
    ~ConnectionFactory();

public slots:

    IoAbstract* createConnection(const std::string ioTypeName, const std::string ioName, const std::pair<std::list<std::string>,std::list<std::string>> param);
    std::list<std::string> getAvailableName(const std::string ioTypeName) const;

private:
    std::shared_ptr<QMutex> lockInterface;
};

#endif // CONNECTIONFACTORY_H
