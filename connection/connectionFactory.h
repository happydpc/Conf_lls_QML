#ifndef CONNECTIONFACTORY_H
#define CONNECTIONFACTORY_H

#include <QObject>
#include <QVector>
#include <QMutex>
#include <memory>
#include "connection/connection.h"

class ConnectionFactory : public QObject
{
    Q_OBJECT
public:
    explicit ConnectionFactory();
    ~ConnectionFactory();

    typedef enum {
        Type_Update_ChangedIndex,
        Type_Update_Removed,
        Type_Update_Add,
    }E_ConnectionUpdateType;

public slots:

    bool addConnection(const QString typeName, const QString name, const QPair<QStringList,QStringList> param);
    void removeConnection(const QString name);
    void removeConnection(const int index);
    void removeAll();

    QStringList getAvailableName(const QString typeName) const;

    int getCountConnection() const;

    QString getInteraceNameFromIndex(const int index) const;

    interfacesAbstract* getInterace(const QString name) const;
    interfacesAbstract* getInterace(const int index) const;

    void errorFromConnection(const QString conTypeName, const QString errMessage);

    DeviceController* getDeviceController(const int ioIndex);

signals:
    void updateTree(const int ioIndex, const ConnectionFactory::E_ConnectionUpdateType type);

private:
    QVector<std::shared_ptr<Connection>> connectionList;
    std::unique_ptr<QMutex> lockInterface;
};

#endif // CONNECTIONFACTORY_H
