#ifndef VIEWCONTROLLER_H
#define VIEWCONTROLLER_H

#include <QObject>
#include "connection/connectionFactory.h"
#include "interfaceListControll/model.h"

class ViewController : public QObject
{
    Q_OBJECT
public:
    explicit ViewController(Model *pInterfaceModel, QObject *parent = nullptr);

    Q_INVOKABLE bool addConnectionSerialPort(QString name, QString baudrate);

    Q_INVOKABLE void removeActiveInterface();
    Q_INVOKABLE void removeActiveDevice();

    Q_INVOKABLE QStringList getAvailableNameToSerialPort();
    Q_INVOKABLE QStringList getAvailableDeviceNameToSerialPort();

    Q_INVOKABLE bool addDeviceToConnection(QString devTypeName, QString idNum, QString password);

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
    Q_INVOKABLE void getDevTarTableFromListId(QStringList devsId);

    Q_INVOKABLE void setCurrentDevTarTable(QStringList values, QStringList levels);
    Q_INVOKABLE void setCurrentDevExportTarTable(QString pathFile, QStringList values, QStringList levels);

    Q_INVOKABLE void setCurrentDevChangeId(QString passwordCheck, QString idNew);


    //********************* TARING *********************//
    //
    // какие устройства доступны для добавления в множественную таррировку
    // устройство с вкладки которого это начинают
    // уже должно быть туда добавленно, type, id, sn
    Q_INVOKABLE QStringList getAvailableDevTarrirAdd_DevType();
    Q_INVOKABLE QStringList getAvailableDevTarrirAdd_DevId();
    Q_INVOKABLE QStringList getAvailableDevTarrirAdd_DevSerialNumber();

    // возвразщает кол-во уже добавленных уст-в
    Q_INVOKABLE int getStayedDevTarrirCount();

    // возвращает устройства добавленные в структуру тарировки (но без значений), type, id, sn
    Q_INVOKABLE QStringList getStayedDevTarrir_DevType();
    Q_INVOKABLE QStringList getStayedDevTarrir_DevId();
    Q_INVOKABLE QStringList getStayedDevTarrir_DevSerialNumber();

    // добавляем датчики в таблицу тарировки
    Q_INVOKABLE bool addTarrirDev(QString devTypeName, QString devId);
    Q_INVOKABLE void removeTarrirDev(QString devTypeName, QString devId);

    //1) считать таблицу с добавленных устройств
            // отправляем в контроллер список dev с id
            // указываем что считать таблицу
            // ожидаем ответа по очереди
            // когда последний опрошен, отсылаем результат в qml
            // если ответа небыло, значение выделить красным и вывести message
    Q_INVOKABLE void getTarrirAllDev();
    Q_INVOKABLE QStringList getTableAtDevice(int index);
    Q_INVOKABLE int getTableCountReady();

    //2) записать таблицу в добавленные устройства
            // как 1
            // только в конце message с графическим результатом и текстом
            // кто ответил и записался - зеленный иначе красное и писать что не получилось

    //3) считать текущие значения с устройств
            // берем deviceFactory
            // находим нужные id
            // забираем текущие значения
            // если значения не валидные тогда -1
            // отправлять в qml

    //4) добавить считанные значения
            // qml присылает сигнал
            // что все текущие значения добавить в шаг таблицы
            // считаем текущие значения
            // добавляем в calibrate по id
            // в qml отсылаем результат
            // перерисовываем row в таблице
            // если значения -1 красное

    //5) добавить шаг таблицы
            // если каком-то из шагов есть -1
            // сообщаем и не даем делать следующий шаг

    //6) редактирование текущего row таблицы
            // когда срабатывает тригер
            // обновляем все значения из таблицы
            // в модель calibrate

    //7) удалить выделенный шаг таблицы со всеми значениями
            // приходит сигнал из qml
            // находим устройства
            // находим шаг
            // очищаем row
            // отсылаем в qml результат что готово
            // перерисовываем таблицу и график

signals:

    void setActivePropertySerialPort();
    void setActivePropertyProgressTmk24(bool status);

    void interfaceAndDeviceListIsEmpty();

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

    void devUpdatePasswordIncorrect(QString devType, QString devNameId);

    void devUpdateTypeDevIncorrect(QString devNameId);

    void devUpdateReadSettingExecuted(QString devNameId, QStringList key, QStringList settings);
    void devUpdateReadSettingWithoutRequest(QString devNameId, QStringList key, QStringList settings);
    void devUpdateReadErrorsExecuted(QString devNameId, QStringList errors);
    void devUpdateWriteSettingExecuted(QString devNameId);
    void devUpdateWriteTarTableExecuted(QString devNameId);
    void devUpdateWriteScaleMeasureExecuted(QString devNameId);

    void devUpdateReadTarTable(int devCount);

    void devUpdateLogMessage(int codeMessage, QString message);

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

    void interfaceTreeChanged(ConnectionFactory::E_ConnectionUpdateType type);
    void deviceTreeChanged(DevicesFactory::E_DeviceUpdateType type, int index);
    void deviceReadyCustomCommand(int index, QString message, QStringList customData, CommandController::sCommandData commmandData);

    bool isCurrentDevice(QString uniqNameId);

    void connectToDevSignals();
    void disconnectToDevSignals();

    DevicesFactory* getDeviceFactoryByIndex(int index);

    int getInterfaceCount();

private:
    ConnectionFactory *connFactory;
    Model *interfaceTree;

    Progress_tmk24Service *tmk24Service;
};

#endif // VIEWCONTROLLER_H
