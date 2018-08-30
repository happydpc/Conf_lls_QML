#ifndef DEVICECONTROLLER_H
#define DEVICECONTROLLER_H

#include <QObject>

class DeviceController : public QObject
{
    Q_OBJECT
public:
    explicit DeviceController(QObject *parent = nullptr);

signals:

public slots:
};

#endif // DEVICECONTROLLER_H