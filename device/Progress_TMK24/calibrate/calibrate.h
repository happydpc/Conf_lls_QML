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
    void reset();

    bool addDevice(QString caption, QString uniqNameId);
    void removeDevice(int index);

    bool addStep(uint32_t valueLiters, QList<uint32_t>valueCntDevs);
    bool changeStep(int index, uint32_t valueLiters, QList<uint32_t>valueCntDevs);
    void removeStep(int index);

    QString getLastError();

signals:

private:

    typedef struct {
        uint32_t valueCnt;
        uint32_t valueLiters;
    }sValues;

    QList<QPair<QString, sValues>>devList;

    QString lastError;

};

#endif // CALIBRATE_H
