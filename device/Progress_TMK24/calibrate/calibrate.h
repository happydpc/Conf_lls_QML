#ifndef CALIBRATE_H
#define CALIBRATE_H

#include <QObject>
#include <QList>
#include <QPair>
#include <QString>

class Calibrate : public QObject
{
    Q_OBJECT
public:
    explicit Calibrate(QObject *parent = nullptr);

public slots:

    bool addDevice(QString devTypeName, QString devId, QString devSn);
    void removeDevice(int index);

    int getDeviceCount();
    QStringList getDeviceProperty(int index);

    QList<QStringList> getCalibrateList();

    void reset();

    bool addStep(uint32_t valueLiters, QList<uint32_t>valueCntDevs);
    bool changeStep(int index, uint32_t valueLiters, QList<uint32_t>valueCntDevs);
    void removeStep(int index);

    QString getLastError();

signals:

private:

    typedef struct {
        uint32_t valueCnt;
        uint32_t valueLiters;
    }sDevValues;

    typedef struct {
        QString devTypeName;
        QString devId;
        QString devSn;
    }sDevIdentBlock;

    QList<QPair<sDevIdentBlock, sDevValues>>devList;

    QString lastError;
};

#endif // CALIBRATE_H
