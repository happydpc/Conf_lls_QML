#ifndef PROGRESS_TMK24SERVICE_H
#define PROGRESS_TMK24SERVICE_H

#include <QObject>
#include "../service/serviceDevicesAbstract.h"

class Progress_tmk24Service : public ServiceDevicesAbstract
{
public:
    Progress_tmk24Service();

    bool addDevice(QString devTypeName, QString devId, QString devSn);
    void removeDevice(int index);

    int getDeviceCount();
    QStringList getDeviceProperty(int index);
    QList<QStringList> getCalibrateList();

    void reset();

    bool addStep(uint32_t valueLiters, QList<uint32_t>valueCntDevs);
    bool changeStep(int index, uint32_t valueLiters, QList<uint32_t>valueCntDevs);
    void removeStep(int index);

    QList<QString> requestGetTableFromAllDevice();
    void placeTableFromDevice(QString deviceIdentName, QStringList table);
    bool readTableAllDeviceIsReady();

    QStringList getTableAtDevice(int index);

    //    QList<CommandController::sCommandData> getCommandList();
    //    void placeDeviceDataAtCurrentData(QString uniqNameId, uint32_t cntValue, uint32_t freq, uint32_t fuelLevel);
    //    void placeDeviceDataAtTableData(QString unqNameId, QStringList tarListValueLiters, QStringList tarListValueCnt);

    //    eStatus getStatus();
    //    void setStatus(Calibrate::eStatus status);

    QString getLastError();

private:

    typedef struct {
        uint32_t valueCnt;
        uint32_t valueLiters;
    }sDevValues;

    typedef struct {
        QString devTypeName;
        QString devId;
        QString devSn;
        bool isWhitedResult;
    }sDevIdentBlock;

    QList<QPair<sDevIdentBlock, QList<sDevValues>*>*>devList;

    QString lastError;

    Progress_tmk24Service* m_pinstance;
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
