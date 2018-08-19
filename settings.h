#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QVector>
#include <iostream>
#include <memory>

#include "gamer.h"

class Settings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int getGamersCount READ getGamersCount NOTIFY updateGamerCount)
public:
    Settings();
    ~Settings();

    int getGamersCount();
    QString getGamerToNumberName(int num);
    QString getGamerToNumberCard(int num);

signals:
    void updateGamerCount(int size);

private:

    typedef struct {
        QString ipAddApi;
        int portApi;
    }sBaseSettings;

    void getGamerList(QVector<Gamer> &gamers);
    sBaseSettings getBaseSettings();

    sBaseSettings baseSettings;
    QVector<Gamer>gamersMap;

};

#endif // SETTINGS_H
