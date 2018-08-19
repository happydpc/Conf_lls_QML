#include "settings.h"

Settings::Settings() {
    this->baseSettings = getBaseSettings();
    getGamerList(this->gamersMap);
}

Settings::sBaseSettings Settings::getBaseSettings() {
    sBaseSettings tSettings;
    tSettings.ipAddApi = "localhost";
    tSettings.portApi = 45454;
    return tSettings;
}

void Settings::getGamerList(QVector<Gamer> &gamers) {
    gamers.push_back(std::move(*std::make_unique<Gamer>(QString("First Last %1").arg(gamers.size()), "1122434")));
    gamers.push_back(std::move(*std::make_unique<Gamer>(QString("First Last %1").arg(gamers.size()), "1122434")));
    gamers.push_back(std::move(*std::make_unique<Gamer>(QString("First Last %1").arg(gamers.size()), "1122434")));
    gamers.push_back(std::move(*std::make_unique<Gamer>(QString("First Last %1").arg(gamers.size()), "1122434")));
    gamers.push_back(std::move(*std::make_unique<Gamer>(QString("First Last %1").arg(gamers.size()), "1122434")));
    gamers.push_back(std::move(*std::make_unique<Gamer>(QString("First Last %1").arg(gamers.size()), "1122434")));
    gamers.push_back(std::move(*std::make_unique<Gamer>(QString("First Last %1").arg(gamers.size()), "1122434")));
    gamers.push_back(std::move(*std::make_unique<Gamer>(QString("First Last %1").arg(gamers.size()), "1122434")));
    gamers.push_back(std::move(*std::make_unique<Gamer>(QString("First Last %1").arg(gamers.size()), "1122434")));
    gamers.push_back(std::move(*std::make_unique<Gamer>(QString("First Last %1").arg(gamers.size()), "1122434")));

    emit updateGamerCount(gamers.size());
}

int Settings::getGamersCount() {
    return gamersMap.size();
}

QString Settings::getGamerToNumberName(int num) {
    Gamer tgamer = gamersMap.at(num);
    return tgamer.getName();
}

QString Settings::getGamerToNumberCard(int num) {
    Gamer tgamer = gamersMap.at(num);
    return tgamer.getCard();
}

Settings::~Settings() {

}
