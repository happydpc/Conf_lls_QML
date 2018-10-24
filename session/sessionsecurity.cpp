#include "sessionsecurity.h"
#include "QJsonDocument"
#include "QJsonObject"
#include "QJsonArray"

SessionSecurity::SessionSecurity(QObject *parent) : QObject(parent) {
    this->database = new Database();
}

QStringList SessionSecurity::getAvailableSessions() {
    QStringList res;
    QStringList queryJson;
    if(database->getSessionsAll(queryJson)) {
        for(auto it:queryJson) {
            if(!it.isEmpty()) {
                QJsonDocument document = QJsonDocument::fromJson(it.toUtf8());
                QJsonObject objects = document.object();
                QJsonArray jsonArray = objects.value("attributes").toArray();
                QJsonObject interface = jsonArray.at(0).toObject();
                auto begin = interface.begin();
                while(begin != interface.end()) {
                    QJsonArray j1 = (QJsonArray*)begin;
                    begin++;
                }

                QJsonArray deviceArray =

//                for(int i=0; i<interfaceArray.size(); i++) {
//                    QJsonArray interface = interfaceArray.at(i).toArray();
////                    interface.
//                }

//                QJsonObject objDatabase = objects.value("database").toObject();
//                dbName = objDatabase.value("db").toString();
//                dbHost = objDatabase.value("host").toString();
//                dbuser = objDatabase.value("user").toString();
//                dbpass = objDatabase.value("pass").toString();
//                dbPort = objDatabase.value("port").toInt();

//                QJsonObject objTty = objects.value("tty").toObject();
//                ttyName = objTty.value("port_name").toString();
//                ttyBaudrate = objTty.value("baudrate").toInt();

//                QJsonObject objOther = objects.value("other_stend_param").toObject();
//                stendRole = objOther.value("stend_role").toString();
//                QJsonArray objArrayNetw = objOther.value("stend_array_network").toArray();

//                for(auto it = objArrayNetw.begin(); it != objArrayNetw.end(); it++) {
//                    StendsParam t_stend_param;
//                    QJsonObject stenObjNet = (*it).toObject();
//                    t_stend_param.is_enabled = stenObjNet.value("isEnabled").toBool();
//                    t_stend_param.name = stenObjNet.value("name").toString();
//                    t_stend_param.ip  = stenObjNet.value("ip").toString();
//                    t_stend_param.port_main = stenObjNet.value("port_main").toInt();
//                    t_stend_param.port_485 = stenObjNet.value("port_485").toInt();
//                    t_stend_param.port_232 = stenObjNet.value("port_232").toInt();

//                    stends[t_stend_param.name] = t_stend_param;
//                }
            }
//            QByteArray dataArray(it.toUtf8());
//            QJsonParseError jsonParserError;
//            QJsonDocument jsonDoc(QJsonDocument::fromJson(dataArray, &jsonParserError));
//            QJsonDocument.
//            QJsonArray jsonArray = jsonDoc.array();
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
