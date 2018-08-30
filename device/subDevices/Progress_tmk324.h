#ifndef  Progress_tmk324_H
#define  Progress_tmk324_H

#include <QObject>
#include <QVector>
#include "Progress_tmk324Data.h"

class Progress_tmk324 : public Progress_tmk324Data
{
public:
    Progress_tmk324();
    ~Progress_tmk324();

    QStringList getSettings();
    bool setSettings(QStringList settigns);
    QStringList getCurrentData();

    QVector<int> getCommandListToIdlePoll();
};

#endif // Progress_tmk324_H
