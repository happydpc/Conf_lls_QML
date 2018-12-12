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

    IoAbstract* createConnection(const std::pair<std::vector<std::string>,std::vector<std::string>> param);
    std::vector<std::string> getAvailableName(const std::string ioTypeName) const;

private:
    std::shared_ptr<QMutex> lockInterface;
};

#endif // CONNECTIONFACTORY_H
