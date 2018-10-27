#include "updater.h"
#include <QtDebug>
#include "QJsonDocument"
#include "QJsonObject"
#include "QJsonArray"

Updater::Updater(QObject *parent) : QObject(parent) {
    connect(&m_WebCtrl, SIGNAL (finished(QNetworkReply*)), this, SLOT (downloaded(QNetworkReply*)));
}

void Updater::checkNewUpdate() {
    QUrl imageUrl("https://update.locuscom.tech/index.json");
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
            qDebug() << "Updater: need update" << (QString(prefix).arg(res.toString()));
            emit needUpdate(QString(prefix).arg(res.toString()));
        }
    }
    pReply->deleteLater();
}
