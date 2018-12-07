#ifndef PROGRESS_TMK24SERVICE_H
#define PROGRESS_TMK24SERVICE_H

#include <QObject>
#include "../service/serviceDevicesAbstract.h"

class Progress_tmk24Service : public ServiceDevicesAbstract
{
public:
    Progress_tmk24Service(std::string ownDeviceName);
    ~Progress_tmk24Service();

    bool addDevice(std::string devTypeName, std::string devId, std::string devSn);
    void removeDevice(std::string devTypeName, std::string devId);

    // сколько всего dev
    int getDeviceCount();
    std::list<std::string> getDeviceProperty(int index);

    // запрос для считывание таблицы со всех уст-в
    QList<std::string> requestGetTableFromAllDevice();
    void placeTableFromDevice(std::string deviceIdentName, std::list<std::string> keys, std::list<std::string> values);
    bool readTableAllDeviceIsReady();

    QList<std::string> requestWriteTableToAllDevice();
    void placeTableFromFrontEnd(std::string deviceIdentName, std::list<std::string> valueLiters, std::list<std::string> valueFuelLevel);
    void placeAckReplyOfWriteTableFromDevice(std::string deviceIdentName, bool writeIsNormal);
    bool getAckStatusDeviceAffterWriteTable(std::string deviceIdentName);

    void placeCurrenDataFromDevice(std::string deviceIdentName, std::pair<std::list<std::string>,std::list<std::string>>);
    void placeCurrentChartDataFromDevice(std::string deviceIdentName, QList<int> currentChartData);

    std::list<std::string> getCurrentDataDevice(int index);
    QList<int> getCurrentChartDataDevice(int index);

    std::list<std::string> getTableAtDevice(int index);
    std::pair<std::list<std::string>,std::list<std::string>> getTableAtDeviceToPair(std::string uniqDevNameId);

    // сколько самое больше кол-во ячеек в тарировки
    // для резервирования array в qml
    int getMaxCountStep();

    std::string getLastError();

private:

    typedef enum {
        OPERATION_IDLE,
        OPERATION_WHITE_GET,
        OPERATION_WHITE_WRITE,
    }eTypOperation;

    typedef struct {
        uint32_t valueFuelLevel;
        uint32_t valueLiters;
        uint32_t valueCnt;
    }sDevValues;

    typedef struct {
        std::string devTypeName;
        std::string devId;
        std::string devSn;
        bool isWhitedResult;
        bool writeIsNormal;
        struct {
            uint32_t fuelLevel;
            uint32_t liters;
            uint32_t cntValue;
            bool isValid;
        }currData;
        QList<int>chartData;
    }sDevIdentBlock;

    QList<std::pair<sDevIdentBlock, QList<sDevValues>*>*>devList;

    std::string lastError;

    Progress_tmk24Service* m_pinstance;

    eTypOperation operation = eTypOperation::OPERATION_IDLE;
};

#endif // PROGRESS_TMK24SERVICE_H
