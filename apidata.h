#ifndef APIDATA_H
#define APIDATA_H

#include <QObject>

class ApiData : public QObject
{
    Q_OBJECT
public:
    explicit ApiData(QObject *parent = nullptr);

    int getBattleCount();

signals:

public slots:
};

#endif // APIDATA_H
