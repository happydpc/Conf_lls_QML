#ifndef VIEWCONTROLLER_H
#define VIEWCONTROLLER_H

#include <QObject>

#include "connection/connectionFactory.h"

class ViewController : public QObject
{
    Q_OBJECT
public:
    explicit ViewController(QObject *parent = nullptr);

    Q_INVOKABLE void addConnectionEvent();
    Q_INVOKABLE void closeConnectionEvent();
    Q_INVOKABLE void closeAppEvent();

    // говорим что нужен новый коннект
//    Q_INVOKABLE void addConnectionRequest();
//    Q_INVOKABLE void addConnection(QString nameInterface, QString subName, QString param);
//    Q_INVOKABLE QStringList getAvailableListInterfaceOfType(int indexType); // первый - это имя интерфейса (SerialPort,Ble,Ethernet)

signals:
    // otsilaet cakie connecti dostypni
    void addConnReplyList(QStringList);

    // отсылает сколько каких коннектов можно создать
//    void readyCreateNewConnections(int connecionsCountTypes);
//    // горит что что-то там открылось
//    void connectionOpened(QString nameInterface, QString subName);
//    // закрылось штатно
//    void connectionClosed(QString name);
//    // закрылось изза ошибки
//    void connectionClosedWithError(QString name);

//    // говорит какой из коннектов сейчас активен на форме
//    void activeCurrentInterface(QString nameInterface, int indexInterface,
//                                int activeDeviceIndex);

private slots:
    void connectionIsLost(interfacesAbstract::eInterfaceTypes, QString nameInterface);

//    void currentActiveConnectionIsChanged(interfacesAbstract::eInterfaceTypes, QString name, int index);



signals:

public slots:


private:
    ConnectionFactory *connFactory;


    int currentInterfaceType;
    QString currentIntefaceName;

    int currentDeviceIndex;
    QString currentDeviceName;

};

#endif // VIEWCONTROLLER_H
