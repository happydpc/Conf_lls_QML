#ifndef INTERFACEETHERNET_H
#define INTERFACEETHERNET_H

#include <QObject>

class InterfaceEthernet : public QObject
{
    Q_OBJECT
public:
    explicit InterfaceEthernet(QObject *parent = nullptr);

signals:

public slots:
};

#endif // INTERFACEETHERNET_H