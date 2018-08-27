#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include "./connection/connectionFactory.h"
#include "./connection/connectionController.h"

class Connection : public QObject
{
    Q_OBJECT
public:
    Connection();



signals:

public slots:
};

#endif // CONNECTION_H
