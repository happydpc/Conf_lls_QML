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
    virtual std::string getType() = 0;
    virtual std::string getInterfaceName() = 0;
    virtual std::pair<std::list<std::string>,std::list<std::string>> getInterfaceProperty() = 0;
    virtual std::list<std::string> getAvailableList() = 0;

signals:
    void errorInterface(std::string conTypeName, std::string errorMessage);
    void openIsNormam();
    void closeIsNormal();

};

#endif
