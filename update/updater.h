#ifndef UPDATER_H
#define UPDATER_H

#include <QObject>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

class Updater : public QObject
{
    Q_OBJECT
public:
    explicit Updater(QObject *parent = nullptr);

    const double version = 7.0;
    const char* prefix_pg = "https://update.locuscom.tech/configure_v%1.msi";
    const char* prefix_gs = "https://update.locuscom.tech/configure_gs_v%1.msi";

    void checkNewUpdate();

signals:
    void needUpdate(QString path);

private slots:
    void downloaded(QNetworkReply*);
private:
    QNetworkAccessManager m_WebCtrl;
};

#endif // UPDATER_H
