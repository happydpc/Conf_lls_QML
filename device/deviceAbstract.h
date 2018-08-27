#ifndef DEVICEABSTRACT_H
#define DEVICEABSTRACT_H

#include <QObject>

class DeviceAbstract : public QObject
{
    Q_OBJECT
public:
    explicit DeviceAbstract(QObject *parent = nullptr);

signals:

public slots:
};

#endif // DEVICEABSTRACT_H