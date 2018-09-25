#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QVector>
#include <iostream>
#include <memory>
#include <QVector>

//#include "./interfaces/interfacesAbstract.h"

class Settings : public QObject
{
    Q_OBJECT
//    Q_PROPERTY(int getGamersCount READ getGamersCount NOTIFY updateGamerCount)
public:
    Settings();
    Settings(QString pathSettings);
    ~Settings();

//signals:
//    void updateGamerCount(int size);

private:

//    QString pathSettings;


//    typedef struct {
//        bool isUsed;
//        //uint8_t *data; TODO:
//    }sDeviceSignatureStruct;

//    typedef struct {
//        QString name;
//        sDeviceSignatureStruct signature;
//    }sDeviceStruct;

//    typedef struct {
//        QString confName;
//    }sBaseSettings;

//public:
//    sBaseSettings getBaseSettings();

//    sBaseSettings baseSettings;
};

#endif // SETTINGS_H
