#ifndef CONNECTIONFACTORY_H
#define CONNECTIONFACTORY_H

#include <QObject>
#include <QMultiMap>
#include "interfaces/interface.h"

class ConnectionFactory : public QObject
{
    Q_OBJECT
public:
    explicit ConnectionFactory();
    ~ConnectionFactory();

    typedef enum {
        Type_Update_Removed,
        Type_Update_Add,
    }E_ConnectionUpdateType;

public slots:

    bool addConnection(interfacesAbstract::eInterfaceTypes type, QString name, QStringList param);
    void removeConnection(QString name);
    void removeConnection(int index);

    QStringList getAvailableName();

    int getCountConnection();

    QString getInteraceNameFromIndex(int index);

    Interface* getInterace(QString name);
    Interface* getInterace(int index);

    void errorFromConnection(interfacesAbstract::eInterfaceTypes, QString name);

signals:
    void updateTree(ConnectionFactory::E_ConnectionUpdateType type);

private:

    QVector<Interface*>interface;

};

#endif // CONNECTIONFACTORY_H
