#ifndef VIEWCONTROLLER_H
#define VIEWCONTROLLER_H

#include <QObject>
#include "connection/connectionFactory.h"
#include "interfaceListControll/model.h"
#include "device/devicesFactory.h"
#include "session/sessionsecurity.h"

class ViewController : public QObject
{
    Q_OBJECT
public:
    explicit ViewController(Model *pInterfaceModel, QObject *parent = nullptr);


    Q_INVOKABLE void resetSession();
    Q_INVOKABLE bool removeSessionByName(QString sessionName);

    Q_INVOKABLE QStringList getListSession();
    Q_INVOKABLE QString saveCurrentSession();
    Q_INVOKABLE QString saveCurrentSessionAs(QString sessionName);

    Q_INVOKABLE bool loadSession(QString sessionName);

    Q_INVOKABLE void closeApplication();

    Q_INVOKABLE bool addConnection(QString typeName, QString name, QStringList keyParam, QStringList valueParam);
    Q_INVOKABLE void removeActiveInterface();
    Q_INVOKABLE QStringList getInterfaceAvailableToAdd(QString typeName);

    Q_INVOKABLE bool addDeviceToConnection(QString ioName, QString devTypeName, QStringList keyParam, QStringList valueParam);
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

    void addInterfaceSuccesfull(QString ioType, QStringList keyProperty, QStringList valueProperty);
    void deleteInterfaceSuccesfull(int ioIndex);
    void interfaceSetActiveProperty(int ioIndex, QString ioType);
    void interfaceAndDeviceListIsEmpty();
    void interfaceReadyProperties(QString ioType, int ioIndex, QStringList keyProperty, QStringList valueProperty);

    void addConnectionFail(QString devName);
    void addDeviceFail(QString devName, QString errorMessage);

    void addDeviceSuccesfull(int ioIndex, QString devType, QStringList devKeyProperty, QStringList devValueProperty);
    void deleteDeviceSuccesfull(int ioIndex, int devIndex);
    void devSetActiveDeviceProperty(int ioIndex, int devIndex, QString devType);
    void devConnected(int ioIndex, int devIndex, QString typeDev);
    void devDisconnected(int ioIndex, int devIndex, QString typeDev);
    void devReady(int ioIndex, int devIndex, QString typeDev);
    void devReadyCheckCommand(int ioIndex, QString devTypeName, QString devId, QString devSn, bool result);
    void devReadyProperties(QString typeDev, int ioIndex, int devIndex, QStringList keys, QStringList values);
    void devReadyPeriodicData(QString typeDev, int ioIndex, int devIndex, QStringList keys, QStringList values);
    void devErrorOperation(QString message);

    void devWrongTypeIncorrect(QString typeDev, QString devNameId);
    void devUpdateLogMessage(int ioIndex, int devIndex, int codeMessage, QString message);
    void devCustomCommandExecuted(QString typeDev, int ioIndex, int devIndex,
                                  QStringList keys, QStringList args, bool ackMessageIsVisible);
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

    void interfaceTreeChanged(int ioIndex, ConnectionFactory::E_ConnectionUpdateType type);
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
    QTimer *updateIoStatusTimer;
    ConnectionFactory *connFactory;
    Model *interfaceTree;
    SessionSecurity *sessionSecurity;
    QList<ServiceDevicesAbstract*> serviceList;
};

#endif // VIEWCONTROLLER_H
