#ifndef GAMER_H
#define GAMER_H

#include <QObject>

class Gamer : public QObject
{
    Q_OBJECT
public:
    Gamer();
    Gamer(QString name, QString card);
    Gamer(const Gamer & object);
    ~Gamer();
signals:

public slots:

public:
    void setName(QString name);
    void setCard(QString card);
    QString getName();
    QString getCard();

private:

    typedef struct {
        QString name;
        QString cardNumber;
    }sGamer;

    sGamer gamer;
};

#endif // GAMER_H
