#ifndef BATTLESTACK_H
#define BATTLESTACK_H

#include <QObject>
#include <QTimer>

class BattleStack : public QObject
{
    Q_OBJECT
public:
    explicit BattleStack(QObject *parent = nullptr);

};

#endif // BATTLESTACK_H
