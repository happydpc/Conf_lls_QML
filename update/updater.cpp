#include "updater.h"
#include <QtDebug>
#include "QJsonDocument"
#include "QJsonObject"
#include "QJsonArray"

Updater::Updater(QObject *parent) : QObject(parent) {
    connect(&m_WebCtrl, SIGNAL (finished(QNetworkReply*)), this, SLOT (downloaded(QNetworkReply*)));
}

void Updater::checkNewUpdate() {
#ifdef PROGRESS
    QUrl imageUrl("https://update.locuscom.tech/index.json");
#endif
#ifdef GLOSSAV
    QUrl imageUrl("https://update.locuscom.tech/index_gs.json");
#endif
    QNetworkRequest request(imageUrl);
    m_WebCtrl.get(request);
}

void Updater::downloaded(QNetworkReply* pReply) {
    QByteArray data = pReply->readAll();
    qDebug() << "size=" << data.size();
    if(!data.isEmpty()) {
        // document
        QJsonDocument document = QJsonDocument::fromJson(data);
        QJsonObject rootObject = document.object();
        QJsonArray installerArray = rootObject.value("installer").toArray();
        QJsonObject obj = installerArray.at(0).toObject();
        QJsonArray infoObjArray = obj.value("info").toArray();
        QJsonObject infoObj = infoObjArray.at(0).toObject();
        QJsonValue res = infoObj.value("lastVersion");
        qDebug() << "Updater: lastVersion=" << res.toString();
        if(res.toString().toDouble() > version) {
#ifdef PROGRESS
            std::string updatePathUrl(prefix_pg);
            auto beginVersion = updatePathUrl.find("%1");
            updatePathUrl.replace(beginVersion, (beginVersion + sizeof("%1")), res.toString().toStdString());
            emit needUpdate(updatePathUrl);
#endif
#ifdef GLOSSAV
            std::string updatePathUrl(prefix_gs);
            auto beginVersion = updatePathUrl.find("%1");
            updatePathUrl.replace(beginVersion, (beginVersion + sizeof("%1")), res.toString().toStdString());
            emit needUpdate(updatePathUrl);
#endif
        }
    }
    pReply->deleteLater();
}
