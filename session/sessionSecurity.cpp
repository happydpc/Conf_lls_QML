#include "sessionSecurity.h"
#include "QJsonDocument"
#include "QJsonObject"
#include "QJsonArray"
#include "QDateTime"
#include <QDebug>

SessionSecurity::SessionSecurity(QObject *parent) : QObject(parent) {
//    this->database = std::make_unique<Database>();
}

SessionSecurity::~SessionSecurity() {
//    delete database.release();
}

std::list<std::string> SessionSecurity::getAvailableSessions() const {
//    std::list<std::string> res;
//    res = database->getSessionsCountAvailable();
//    return res;
}

SessionProperty SessionSecurity::getSessionByName(const std::string name) {
//    auto res = getSessionAll();
//    for(auto it:res) {
//        if(it.getSessionName() == name) {
//            return it;
//        }
//    }
//    return SessionProperty();
}

bool SessionSecurity::removeSession(std::string sessionName) {
//    return database->sendRemoveSession(sessionName);
}

QList<SessionProperty> SessionSecurity::getSessionAll() const {
//    QList<SessionProperty> res;
//    std::list<std::string> jsonRes = database->getSessionsAll();
//    if(!jsonRes.empty()) {
//        for(auto rootIt:jsonRes) {
//            if(!rootIt.isEmpty()) {
//                // document
//                QJsonDocument document = QJsonDocument::fromJson(rootIt.toUtf8());
//                QJsonObject rootObject = document.object();
//                // create session class and structures
//                // session name
//                SessionProperty *p_session = new SessionProperty(rootObject.value("name").toString());
//                // array insterfaces [interface_0 ... _1 _2 _3]
//                QJsonArray attributesArray = rootObject.value("attributes").toArray();
//                QJsonObject interfaceObj = attributesArray.at(0).toObject();
//                // while interfaces is exist
//                auto itBegin = interfaceObj.begin();
//                while(itBegin != interfaceObj.end()) {
//                    SessionProperty::sInterface t_interface;
//                    SessionProperty::sDevices t_device;
//                    QJsonObject tObj = itBegin->toObject();
//                    // interface property
//                    QJsonObject propertyObj = tObj.value("property").toObject();
//                    auto propIt = propertyObj.begin();
//                    while(propIt != propertyObj.end()) {
//                        t_interface.propKey.push_back(propIt.key());
//                        t_interface.propValue.push_back(propIt.value().toString());
//                        propIt++;
//                    }
//                    t_interface.typeName = tObj.value("type").toString();
//                    t_interface.name = tObj.value("name").toString();
//                    // add interface structure to class
//                    p_session->addInterface(t_interface);

//                    // create device structures
//                    QJsonArray devicesArray = tObj.value("devices").toArray();
//                    auto devIt = devicesArray.begin();
//                    while(devIt != devicesArray.end()) {
//                        QJsonObject deviceList = devIt->toObject();
//                        auto devItContrete = deviceList.begin();
//                        while(devItContrete != deviceList.end()) {
//                            QJsonObject dev = devItContrete->toObject();
//                            QJsonObject devProperty = dev.value("property").toObject();
//                            t_device.propKey.clear();
//                            t_device.propValue.clear();
//                            //
//                            t_device.typeName = dev.value("typeName").toString();
//                            // devId
//                            t_device.propKey.push_back("id");
//                            t_device.propValue.push_back(devProperty.value("id").toString());
//                            // devHeader
//                            t_device.propKey.push_back("header");
//                            t_device.propValue.push_back(devProperty.value("header").toString());
//                            p_session->addDevice(t_device);
//                            devItContrete++;
//                        }
//                        devIt++;
//                    }
//                    itBegin++;
//                }
//                p_session->setIsValid(true);
//                res.push_back(*p_session);
//            }
//        }
//    }
//    return res;
}

std::string SessionSecurity::saveSession(SessionProperty & session) {
//    std::string jsonResult;
//    QJsonArray attributesArray;
//    session.setIsValid(true);
//    if(session.getIsValid()) {
//        QJsonObject rootObject;
//        QJsonObject interfaceObj;
//        rootObject["name"] = session.getSessionName();
//        rootObject["type"] = "session";
//        int interfaceCount = 0;
//        for(auto itInerfaces: session.getInterfaces()) {
//            int devCounter = 0;
//            QJsonArray devArray;
//            QJsonObject ioSubProperty;
//            QJsonObject ioSubPropertyItem;
//            for(int ioPropCoun=0;ioPropCoun<itInerfaces.propKey.size();ioPropCoun++) {
//                ioSubPropertyItem[itInerfaces.propKey.at(ioPropCoun)] = itInerfaces.propValue.at(ioPropCoun);
//            }
//            ioSubProperty["name"] = itInerfaces.name;
//            ioSubProperty["type"] = itInerfaces.typeName;
//            ioSubProperty["property"] = ioSubPropertyItem;
//            for(auto itDevices: itInerfaces.devices) {
//                QJsonObject devObj;
//                QJsonObject devPropertyObj;
//                QJsonValue devPropertyValue;
//                QJsonObject jsonValueObj;
//                jsonValueObj["header"] = "lls_1";
//                jsonValueObj["id"] = "11111";
//                devPropertyObj["typeName"] = itDevices.typeName;
//                for(int devPropCoun=0; devPropCoun<itDevices.propKey.size(); devPropCoun++) {
//                    jsonValueObj[itDevices.propKey.at(devPropCoun)] = itDevices.propValue.at(devPropCoun);
//                }
//                devPropertyValue = jsonValueObj;
//                devPropertyObj["property"] = devPropertyValue;
//                devObj[std::string("dev_%1").arg(devCounter)] = devPropertyObj;
//                devArray.push_back(devObj);
//                ioSubProperty["devices"] = devArray;
//                devCounter++;
//            }
//            interfaceObj[std::string("interface_%1").arg(interfaceCount)] = ioSubProperty;
//            interfaceCount++;
//        }
//        attributesArray.append(interfaceObj);
//        rootObject["attributes"] = attributesArray;
//        QJsonDocument jsonDoc(rootObject);
//        qDebug() << "resultJson = " << jsonDoc.toJson();
//        jsonResult = jsonDoc.toJson();
//        database->sendSaveSession(session.getSessionName(), jsonResult);
//    }
//    return session.getSessionName();
}
