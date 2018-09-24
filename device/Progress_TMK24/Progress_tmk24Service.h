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

    // сколько всего dev
    int getDeviceCount();
    QStringList getDeviceProperty(int index);

    // запрос для считывание таблицы со всех уст-в
    QList<QString> requestGetTableFromAllDevice();
    void placeTableFromDevice(QString deviceIdentName, QStringList table);
    bool readTableAllDeviceIsReady();

    QList<QString> requestWriteTableToAllDevice();
    void placeTableFromFrontEnd(QString deviceIdentName, QStringList valueLiters, QStringList valueCnts);
    void placeAckReplyOfWriteTableFromDevice(QString deviceIdentName, bool writeIsNormal);
    bool getAckStatusDeviceAffterWriteTable(QString deviceIdentName);

    void placeCurrenDataFromDevice(QString deviceIdentName, QList<QString> currentData);
    void placeCurrentChartDataFromDevice(QString deviceIdentName, QList<int> currentChartData);

    QStringList getCurrentDataDevice(int index);
    QList<int> getCurrentChartDataDevice(int index);

    QStringList getTableAtDevice(int index);
    QPair<QStringList,QStringList> getTableAtDeviceToPair(QString uniqDevNameId);

    // сколько самое больше кол-во ячеек в тарировки
    // для резервирования array в qml
    int getMaxCountStep();

    QString getLastError();

private:

    typedef enum {
        OPERATION_IDLE,
        OPERATION_WHITE_GET,
        OPERATION_WHITE_WRITE,
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
        bool writeIsNormal;
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
