#ifndef PROGRESS_TMK24SERVICE_H
#define PROGRESS_TMK24SERVICE_H

#include <QObject>
#include "../service/serviceDevicesAbstract.h"

class Progress_tmk24Service : public ServiceDevicesAbstract
{
public:
    explicit Progress_tmk24Service(QString owDeviceName);

    bool addDevice(QString devTypeName, QString devId, QString devSn);
    void removeDevice(QString devTypeName, QString devId);

    int getDeviceCount();
    QStringList getDeviceProperty(int index);
    QList<QStringList> getCalibrateList();

    QList<QString> requestGetTableFromAllDevice();
    void placeTableFromDevice(QString deviceIdentName, QStringList table);
    bool readTableAllDeviceIsReady();

    void placeCurrenDataFromDevice(QString deviceIdentName, QList<QString> currentData);
    void placeCurrentChartDataFromDevice(QString deviceIdentName, QList<int> currentChartData);

//    void setLastRealTimeValuesToStep(int indexStep);

    QStringList getCurrentDataDevice(int index);
    QList<int> getCurrentChartDataDevice(int index);

    QStringList getTableAtDevice(int index);

    // сколько самое больше кол-во ячеек в тарировки
    // для резервирования array в qml
    int getMaxCountStep();

    QString getLastError();

private:

    typedef enum {
        OPERATION_IDLE,
        OPERATION_WHITE_GET
    }eTypOperation;

    typedef struct {
        uint32_t valueCnt;
        uint32_t valueLiters;
    }sDevValues;

    typedef struct {
        QString devTypeName;
        QString devId;
        QString devSn;
        bool isWhitedResult;
        struct {
            uint32_t cnt;
            uint32_t liters;
            bool isValid;
        }currData;
        QList<int>chartData;
    }sDevIdentBlock;

    QList<QPair<sDevIdentBlock, QList<sDevValues>*>*>devList;

    QString lastError;

    Progress_tmk24Service* m_pinstance;

    eTypOperation operation = eTypOperation::OPERATION_IDLE;
};

#endif // PROGRESS_TMK24SERVICE_H


//#ifndef CALIBRATE_H
//#define CALIBRATE_H

//#include <QObject>
//#include <QList>
//#include <QPair>
//#include <command/commandController.h>

//class Calibrate : public QObject
//{
//    Q_OBJECT
//public:
//    static Calibrate &Instance();

//    typedef enum {
//        CALIBRATE_STATUS_IDLE,
//        CALIBRATE_STATUS_NEED_GET_TABLE_FROM_DEVICES,
//        CALIBRATE_STATUS_WHITE_REPLY_READ_TABLE_FROM_DEVICES,
//        CALIBRATE_STATUS_GET_TABLE_FROM_DEVICE_NORMAL_READY
//    }eStatus;

//public:

//    typedef enum {
//        EventType_ReadyReadTableAtDevices
//    }eTypeEvents;

//signals:
//    void calibrateEvents(eTypeEvents type);



//private:


//    eStatus status = CALIBRATE_STATUS_IDLE;

//};

//#endif // CALIBRATE_H
