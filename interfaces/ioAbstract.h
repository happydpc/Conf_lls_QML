#ifndef IO_ABSTRACT_H
#define IO_ABSTRACT_H

#include <QObject>
#include <memory>

class IoAbstract : public QObject
{
    Q_OBJECT
public:
    explicit IoAbstract(QObject *parent = nullptr);

public slots:
    virtual void initInterface() = 0;
    virtual bool openInterface() = 0;
    virtual bool isOpen() = 0;
    virtual void closeInterface() = 0;
    virtual bool sendData(QByteArray pData) = 0;
    virtual bool readData(QByteArray &pData) = 0;
    virtual QString getType() = 0;
    virtual QString getInterfaceName() = 0;
    virtual QPair<QStringList,QStringList> getInterfaceProperty() = 0;
    virtual QStringList getAvailableList() = 0;

signals:
    void errorInterface(QString conTypeName, QString errorMessage);
    void openIsNormam();
    void closeIsNormal();

};

#endif
