#ifndef INTERFACEBLE_H
#define INTERFACEBLE_H

#include <QObject>

class InterfaceBLE : public QObject
{
    Q_OBJECT
public:
    explicit InterfaceBLE(QObject *parent = nullptr);

signals:

public slots:
};

#endif // INTERFACEBLE_H