#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QDebug>

#include "./settings/settings.h"

Settings::Settings() {
//    this->baseSettings = getBaseSettings();
}

Settings::Settings(QString pathSettings) {
//    this->pathSettings = pathSettings;
//    Settings(pathSettings);
}

Settings::~Settings(){}

//Settings::sBaseSettings Settings::getBaseSettings() {
//    sBaseSettings tSettings;
//    tSettings.ipAddApi = "localhost";
//    tSettings.portApi = 45454;
//    return tSettings;
//}

//void Settings::getGamerList(QVector<Gamer> &gamers) {
//    gamers.push_back(std::move(*std::make_unique<Gamer>(QString("First Last %1").arg(gamers.size()), "1122434")));
//    gamers.push_back(std::move(*std::make_unique<Gamer>(QString("First Last %1").arg(gamers.size()), "1122434")));
//    gamers.push_back(std::move(*std::make_unique<Gamer>(QString("First Last %1").arg(gamers.size()), "1122434")));
//    gamers.push_back(std::move(*std::make_unique<Gamer>(QString("First Last %1").arg(gamers.size()), "1122434")));
//    gamers.push_back(std::move(*std::make_unique<Gamer>(QString("First Last %1").arg(gamers.size()), "1122434")));
//    gamers.push_back(std::move(*std::make_unique<Gamer>(QString("First Last %1").arg(gamers.size()), "1122434")));
//    gamers.push_back(std::move(*std::make_unique<Gamer>(QString("First Last %1").arg(gamers.size()), "1122434")));
//    gamers.push_back(std::move(*std::make_unique<Gamer>(QString("First Last %1").arg(gamers.size()), "1122434")));
//    gamers.push_back(std::move(*std::make_unique<Gamer>(QString("First Last %1").arg(gamers.size()), "1122434")));
//    gamers.push_back(std::move(*std::make_unique<Gamer>(QString("First Last %1").arg(gamers.size()), "1122434")));
//    emit updateGamerCount(gamers.size());
//}

//sBaseSettings Settings::getBaseSettings() {
//    sBaseSettings baseSettings
//}

//int Settings::getGamersCount() {
//    return gamersMap.size();
//}

//QString Settings::getGamerToNumberName(int num) {
//    Gamer tgamer = gamersMap.at(num);
//    return tgamer.getName();
//}

//QString Settings::getGamerToNumberCard(int num) {
//    Gamer tgamer = gamersMap.at(num);
//    return tgamer.getCard();
//}


//bool Settings::loadJson() {
//    return loadJson(path);
//}

//bool Settings::loadJson(QString path) {
//    QFile file;
//    QString val;
//    file.setFileName(path);
//    file.open(QIODevice::ReadWrite | QIODevice::Text);
//    val = file.readAll();
//    file.close();
//    if(!val.isEmpty()) {
//        QJsonDocument document = QJsonDocument::fromJson(val.toUtf8());
//        QJsonObject objects = document.object();

//        QJsonObject objDatabase = objects.value("database").toObject();
//        dbName = objDatabase.value("db").toString();
//        dbHost = objDatabase.value("host").toString();
//        dbuser = objDatabase.value("user").toString();
//        dbpass = objDatabase.value("pass").toString();
//        dbPort = objDatabase.value("port").toInt();


//        QJsonObject objTty = objects.value("tty").toObject();
//        ttyName = objTty.value("port_name").toString();
//        ttyBaudrate = objTty.value("baudrate").toInt();

//        QJsonObject objOther = objects.value("other_stend_param").toObject();
//        stendRole = objOther.value("stend_role").toString();
//        QJsonArray objArrayNetw = objOther.value("stend_array_network").toArray();

//        for(auto it = objArrayNetw.begin(); it != objArrayNetw.end(); it++) {
//            StendsParam t_stend_param;
//            QJsonObject stenObjNet = (*it).toObject();
//            t_stend_param.is_enabled = stenObjNet.value("isEnabled").toBool();
//            t_stend_param.name = stenObjNet.value("name").toString();
//            t_stend_param.ip  = stenObjNet.value("ip").toString();
//            t_stend_param.port_main = stenObjNet.value("port_main").toInt();
//            t_stend_param.port_485 = stenObjNet.value("port_485").toInt();
//            t_stend_param.port_232 = stenObjNet.value("port_232").toInt();

//            stends[t_stend_param.name] = t_stend_param;
//        }
//    }
//    return (stends.empty()) ? false : true;
//}

//QString Settings::getDbName() {
//    return dbName;
//}

//QString Settings::getdbHost() {
//    return dbHost;
//}

//QString Settings::getDbUser() {
//    return dbuser;
//}

//QString Settings::getDbPass() {
//    return dbpass;
//}

//int Settings::getDbPort() {
//    return dbPort;
//}

//QString Settings::getTtyName() {
//    return ttyName;
//}

//int Settings::getTtyBaudType() {
//    return ttyBaudrate;
//}

//QString Settings::getstendRole() {
//    return stendRole;
//}

//int Settings::getStendCount() {
//    return stends.size();
//}

//StendsParam *Settings::getStendParameter(int index) {
//    auto it = stends.begin();
//    it+= index;
//    return &(*it);
//}
