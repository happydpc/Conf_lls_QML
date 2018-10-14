#ifndef CONNECTIONFACTORY_H
#define CONNECTIONFACTORY_H

#include <QObject>
#include <QVector>
#include <QMutex>
#include "interfaces/interfacesAbstract.h"
#include "interfaces/interfaceSerial.h"
#include "interfaces/interfaceBLE.h"
#include "interfaces/interfaceEthernet.h"

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

    bool addConnection(QString typeName, QString name, QPair<QStringList,QStringList> param);
    void removeConnection(QString name);
    void removeConnection(int index);

    QStringList getAvailableName(QString typeName);

    int getCountConnection();

    QString getInteraceNameFromIndex(int index);

    interfacesAbstract* getInterace(QString name);
    interfacesAbstract* getInterace(int index);

    void errorFromConnection(QString type, QString name);

signals:
    void updateTree(ConnectionFactory::E_ConnectionUpdateType type);

private:

    QVector<interfacesAbstract*>interfaceList;

    QMutex *lockInterface;

};

#endif // CONNECTIONFACTORY_H
