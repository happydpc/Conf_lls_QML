#include "sessionsecurity.h"
#include "QJsonDocument"
#include "QJsonObject"
#include "QJsonArray"

SessionSecurity::SessionSecurity(QObject *parent) : QObject(parent) {
    this->database = new Database();
}

QStringList SessionSecurity::getAvailableSessions() {
    QStringList res;
    res = database->getSessionsCountAvailable();
    return res;
}

QList<Session> SessionSecurity::getSessionAll() {
    QList<Session> res;
    QStringList jsonRes;
    if(database->getSessionsAll(jsonRes)) {
        for(auto rootIt:jsonRes) {
            if(!rootIt.isEmpty()) {
                // document
                Session *pSession = new Session();

                QJsonDocument document = QJsonDocument::fromJson(rootIt.toUtf8());
                QJsonObject rootObject = document.object();
                // array insterfaces [interface_0 ... _1 _2 _3]
                QJsonArray attributesArray = rootObject.value("attributes").toArray();
                QJsonObject interfaceObj = attributesArray.at(0).toObject();
                int countInterfaces = interfaceObj.size();
                if(countInterfaces != 0) {
                    auto itBegin = interfaceObj.begin();
                    while(itBegin != interfaceObj.end()) {
                        QJsonObject tObj = itBegin->toObject();
                        QJsonArray devicesArray = tObj.value("devices").toArray();
                        QString interfaceName = tObj.value("name").toString();
                        QJsonObject propertyObj = tObj.value("property").toObject();
                        QPair<QStringList,QStringList> propertyList;
                        // interface property
                        auto propIt = propertyObj.begin();
                        while(propIt != propertyObj.end()) {
                            propertyList.first.push_back(propIt.key());
                            propertyList.second.push_back(propIt.value().toString());
                            propIt++;
                        }
                        auto devIt = devicesArray.begin();
                        while(devIt != devicesArray.end()) {
                            QJsonObject deviceList = devIt->toObject();
                            auto devItContrete = deviceList.begin();
                            while(devItContrete != deviceList.end()) {
                                QJsonObject dev = devItContrete->toObject();
                                QJsonObject devProperty = dev.value("property").toObject();
                                QString devTypeName = dev.value("typeName").toString();
                                QString devHeader = devProperty.value("header").toString();
                                QString devId = devProperty.value("id").toString();
                                devItContrete++;
                            }
                            devIt++;
                        }
                        itBegin++;
                    }
                }
            }
        }
    }
    return res;
}

Session* SessionSecurity::getByName(QString sessionName) {

}

bool SessionSecurity::saveByName(QString sessionName) {

}

bool SessionSecurity::saveAuto() {

}
