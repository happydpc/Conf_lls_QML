#ifndef VIEWCONTROLLER_H
#define VIEWCONTROLLER_H

#include <QObject>
#include "connection/connectionFactory.h"
#include "interfaceListControll/model.h"

class ViewController : public QObject
{
    Q_OBJECT
public:
    explicit ViewController(QObject *parent = nullptr);

//    Model interfaceListModel;

    Q_INVOKABLE bool addConnectionSerialPort(QString name, QString baudrate);
    Q_INVOKABLE bool removeActiveConnectionSerialPort();

    Q_INVOKABLE QStringList getAvailableNameToSerialPort();
    Q_INVOKABLE QStringList getAvailableDeviceNameToSerialPort();

    Q_INVOKABLE bool addDeviceToConnection(QString devTypeName, QString idNum, QString password);
    Q_INVOKABLE void removeActiveDevice();

    Q_INVOKABLE void setChangedIndexDevice(int index);
    Q_INVOKABLE void setChangedIndexInteface(int index);

    Q_INVOKABLE QList<int> getCurrentDevChart();
    Q_INVOKABLE QList<QString> getCurrentDevOtherData();

    Q_INVOKABLE QString getCurrentInterfaceNameToSerial();

    Q_INVOKABLE int getDeviceCount();
    Q_INVOKABLE QStringList getDeviceHeaderByIndex(int index);

    Q_INVOKABLE QStringList getCurrentDevPropertyByIndex();

    Q_INVOKABLE void setCurrentDevLevelAsEmpty();
    Q_INVOKABLE void setCurrentDevLevelAsFull();

    Q_INVOKABLE void getCurrentDevSettingsWithoutRequest();
    Q_INVOKABLE void getCurrentDevSettings();
    Q_INVOKABLE void setCurrentDevSettings(QStringList key, QStringList settings);
    Q_INVOKABLE void getCurrentDevErrors();

    Q_INVOKABLE void getCurrentDevTarTable();
    Q_INVOKABLE void setCurrentDevTarTable(QStringList values, QStringList levels);
    Q_INVOKABLE void setCurrentDevExportTarTable(QString pathFile, QStringList values, QStringList levels);

    Q_INVOKABLE void setCurrentDevChangeId(QString passwordCheck, QString idNew);

signals:
    void remakeInterfaceTree(QStringList list, QList<int>status);
    void changeInterfaceTreeStatus(int index, int status);

    void remakeDeviceTree(QStringList list, QList<int>status);
    void changeDeviceTreeStatus(int index, int status);

    void updatePropertiesSerialPort(QStringList properties);

    void addConnectionFail(QString devName);
    void addDeviceFail(QString devName);

    void devConnectedTmk24();
    void devConnectedTmk4ux();
    void devDisconnectedTmk24();
    void devDisconnectedTmk4ux();

    void devReadyPropertiesTmk24(QStringList data);
    void devReadyPropertiesTmk4ux(QStringList data);

    void devReadyOtherDataTmk24(QStringList data);
    void devReadyOtherDataTmk4ux(QStringList data);

    void devFullReadyTmk24(QStringList data);
    void devFullReadyTmk4ux(QStringList data);

    void devErrorOperation(QString message);

    void devUpdatePasswordIncorrect(QString devNameId);

    void devUpdateTypeDevIncorrect(QString devNameId);

    void devUpdateReadSettingExecuted(QString devNameId, QStringList key, QStringList settings);
    void devUpdateReadSettingWithoutRequest(QString devNameId, QStringList key, QStringList settings);
    void devUpdateReadErrorsExecuted(QString devNameId, QStringList errors);
    void devUpdateWriteSettingExecuted(QString devNameId);
    void devUpdateWriteTarTableExecuted(QString devNameId);
    void devUpdateWriteScaleMeasureExecuted(QString devNameId);
    void devUpdateReadTarTable(QString devNameId, QStringList table);

    void devUpdateLogMessage(int codeMessage, QString message);

    void devUpdateTree(QStringList devNames, QList<int>status);

private slots:
    void deviceConnected(DevicesFactory::E_DeviceType, QString uniqNameId);
    void deviceDisconnected(DevicesFactory::E_DeviceType, QString uniqNameId);
    void deviceReadyCurrentData(DevicesFactory::E_DeviceType, QString uniqNameId);
    void deviceReadyProperties(DevicesFactory::E_DeviceType, QString uniqNameId);
    void deviceReadyInit(DevicesFactory::E_DeviceType, QString uniqNameId);

    void interfaceTreeChanged(ConnectionFactory::E_ConnectionUpdateType type);
    void deviceTreeChanged(DevicesFactory::E_DeviceUpdateType type, int index);
    void deviceReadyCustomCommand(int index, QString message, QStringList customData);

    bool isCurrentDevice(QString uniqNameId);

    void connectToDevSignals();
    void disconnectToDevSignals();

    DevicesFactory* getDeviceFactoryByIndex(int index);

    int getInterfaceCount();

private:
    ConnectionFactory *connFactory;

    typedef struct {
        int interfaceIndex;
        int deviceIndex;
    }sCurrentIndex;
    sCurrentIndex index = {0, 0};
};

#endif // VIEWCONTROLLER_H
