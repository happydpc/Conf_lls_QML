#include "gamer.h"

Gamer::Gamer() {

}

Gamer::Gamer(const Gamer & object) {
    this->gamer = object.gamer;
}

Gamer::Gamer(QString name, QString card) {
    this->gamer.cardNumber = card;
    this->gamer.name = name;
}

void Gamer::setName(QString name) {

}

void Gamer::setCard(QString card) {

}

QString Gamer::getName() {

}

QString Gamer::getCard() {

}

Gamer::~Gamer() {

}
