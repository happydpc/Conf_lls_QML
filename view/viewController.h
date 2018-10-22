#ifndef VIEWCONTROLLER_H
#define VIEWCONTROLLER_H

#include <QObject>
#include "connection/connectionFactory.h"
#include "interfaceListControll/model.h"
#include "device/devicesFactory.h"

class ViewController : public QObject
{
    Q_OBJECT
public:
    explicit ViewController(Model *pInterfaceModel, QObject *parent = nullptr);

    Q_INVOKABLE bool addConnection(QString typeName, QString name, QStringList keyParam, QStringList valueParam);
    Q_INVOKABLE void removeActiveInterface();
    Q_INVOKABLE QStringList getInterfaceAvailableToAdd(QString typeName);

    Q_INVOKABLE bool addDeviceToConnection(QString devTypeName, QStringList keyParam, QStringList valueParam);
    Q_INVOKABLE void checkDeviceFromConnection(QString devTypeName, QStringList keyParam, QStringList valueParam);

    Q_INVOKABLE QStringList getDeviceAvailableType();
    Q_INVOKABLE void removeActiveDevice();
    Q_INVOKABLE QList<QString> getCurrentDevPeriodicDataKey();
    Q_INVOKABLE QList<QString> getCurrentDevPeriodicDataValue();

    Q_INVOKABLE QString getCurrentInterfaceName();

    Q_INVOKABLE int getDeviceCount();
    Q_INVOKABLE QStringList getCurrentDevPropertyKey();
    Q_INVOKABLE QStringList getCurrentDevPropertyValue();

    Q_INVOKABLE bool setCurrentDevCustomCommand(QString typeCommand, QStringList keys, QStringList values);

    DeviceAbstract *getCurrentDeviceToAbstract();


    //****************** Only PROGRESS TMK24 ***********//
//    Q_INVOKABLE void setCurrentDevNewIdAddress(QString newId, QString password, QString currentId);
//    Q_INVOKABLE void setCurrentDevLevelAsEmpty();
//    Q_INVOKABLE void setCurrentDevLevelAsFull();
//    Q_INVOKABLE void setCurrentDevSettings(QStringList key, QStringList values);
    Q_INVOKABLE void getCurrentDevTarTable();
    Q_INVOKABLE void setCurrentDevChangeId(QString password, QString uniqNameIdNew, QString uniqNameIdCurrent);
    //********************* TARING *********************//
    Q_INVOKABLE void setTableFromFrontEnd(QString uniqNameId, QStringList valuesLiters, QStringList valuesFuelLevel);
    Q_INVOKABLE void sendReqWriteTarrirAllDev();
    //
    Q_INVOKABLE int getTarMaxCountStep();

    Q_INVOKABLE void sendReqExportTarrirAllDevToCsv(QString pathFile);

    // какие устройства доступны для добавления в множественную таррировку
    // устройство с вкладки которого это начинают
    // уже должно быть туда добавленно, type, id, sn
    Q_INVOKABLE QStringList getAvailableDevTarrirAdd_DevType();
    Q_INVOKABLE QStringList getAvailableDevTarrirAdd_DevId();
    Q_INVOKABLE QStringList getAvailableDevTarrirAdd_DevSerialNumber();

    Q_INVOKABLE QStringList getTarCurrentDeviceData(int index);
    Q_INVOKABLE QList<int> getTarCurrentDeviceChartData(int index);

    // возвразщает кол-во уже добавленных уст-в
    Q_INVOKABLE int getStayedDevTarrirCount();

    // возвращает устройства добавленные в структуру тарировки (но без значений), type, id, sn
    Q_INVOKABLE QStringList getStayedDevTarrir_DevProperty(QString propertyName);

    // добавляем датчики в таблицу тарировки
    Q_INVOKABLE bool addTarrirDev(QString devTypeName, QString devId);
    Q_INVOKABLE void removeTarrirDev(QString devTypeName, QString devId);

    // добавляет текущее значение в таблицу
    Q_INVOKABLE void setLastRealTimeValuesToStep(int indexStep);

    //1) считать таблицу с добавленных устройств
            // отправляем в контроллер список dev с id
            // указываем что считать таблицу
            // ожидаем ответа по очереди
            // когда последний опрошен, отсылаем результат в qml
            // если ответа небыло, значение выделить красным и вывести message
    Q_INVOKABLE void sendReqGetTarrirAllDev();
    Q_INVOKABLE QStringList getTableAtDevice(int index);
    Q_INVOKABLE int getTableCountReady();

signals:

    void interfaceSetActiveProperty(QString ioType);
    void setActiveDeviceProperty(QString devType);
    void interfaceAndDeviceListIsEmpty();
    void interfaceReadyProperties(QString ioType, QStringList properties);

    void addConnectionFail(QString devName);
    void addDeviceFail(QString devName, QString errorMessage);

    void devConnected(QString typeDev);
    void devDisconnected(QString typeDev);
    void devReadyCheckCommand(QString devTypeName, QString devId, QString devSn, bool result);
    void devSetActiveDeviceProperty(QString devType);
    void devReadyProperties(QString typeDev, QStringList data);
    void devReadyPeriodicData(QString typeDev);
    void devErrorOperation(QString message);

    void devWrongTypeIncorrect(QString typeDev, QString devNameId);
    void devUpdateLogMessage(int codeMessage, QString message);
    void devUpdateLogDeviceMessage(QString typeDev, QString message);
    void devCustomCommandExecuted(QString typeDev, QStringList keys, QStringList args, bool ackMessageIsVisible);
    void devUpdateTree(QStringList devNames, QList<int>status);

public slots:
    void setChangedIndexDevice(int interfaceIndex,int deviceIndex);
    void setChangedIndexInteface(int index);

private slots:
    void deviceConnected(DevicesFactory::E_DeviceType, QString uniqNameId);
    void deviceDisconnected(DevicesFactory::E_DeviceType, QString uniqNameId);
    void deviceReadyCurrentData(DevicesFactory::E_DeviceType, QString uniqNameId);
    void deviceReadyProperties(DevicesFactory::E_DeviceType, QString uniqNameId);
    void deviceReadyInit(DevicesFactory::E_DeviceType, QString uniqNameId);
    void deviceCheckReady(DevicesFactory::E_DeviceType devType,QString devUniqNameId, bool result);

    void interfaceTreeChanged(ConnectionFactory::E_ConnectionUpdateType type);
    void deviceTreeChanged(DevicesFactory::E_DeviceUpdateType type, int index);
    void deviceReadyCustomCommand(int index, QString message,
                                  QStringList keyCustomData, QStringList valueCustomData,
                                  CommandController::sCommandData commmandData);
    void deviceLogMessage(int indexDev, QStringList message);

    bool isCurrentDevice(QString uniqNameId);

    void connectToDevSignals();
    void disconnectToDevSignals();

    DevicesFactory* getDeviceFactoryByIndex(int index);

    int getInterfaceCount();

private:
    ConnectionFactory *connFactory;
    Model *interfaceTree;

    QList<ServiceDevicesAbstract*> serviceList;
};

#endif // VIEWCONTROLLER_H
