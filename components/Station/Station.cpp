//
// Created by gruzi on 06/03/2023.
//

#include "Station.h"

Station::Station(const std::string &naam, const std::string &type) : fNaam(naam), fType(type){
    _initCheck = this;

    ENSURE(properlyInitialized(), "Expected Station to be properly initialized in constructor!");
}
bool Station::properlyInitialized() const {
    return _initCheck == this;
}
// getters
std::string Station::getNaam() const {
    REQUIRE(this->properlyInitialized(), "Expected Station to be properly initialized in getNaam!");
    return fNaam;
}
Station* Station::getVolgende(const int &spoorNr) const {
    REQUIRE(this->properlyInitialized(), "Expected Station to be properly initialized in getVolgende!");
    return fSporen.at(spoorNr).second;
}
Station* Station::getVorige(const int &spoorNr) const {
    REQUIRE(this->properlyInitialized(), "Expected Station to be properly initialized in getVorige!");
    return fSporen.at(spoorNr).first;
}

std::pair<Station *, Station *> Station::getSpoor(const int &spoorNr) const {
    return fSporen.find(spoorNr)->second;
}
std::map<int, std::pair<Station *, Station *> > Station::getSporen() const {
    return fSporen;
}

// setters


void Station::setSpoor(const int &spoorNr, const std::pair<Station *, Station *> &newSpoor) {
    fSporen.at(spoorNr) = newSpoor;
}
void Station::setSporen(const std::map<int, std::pair<Station *, Station *> > &newSporen) {
    fSporen = newSporen;
}
void Station::setNaam(const std::string &newNaam) {
    REQUIRE(this->properlyInitialized(), "Expected Station to be properly initialized in setNaam!");
    fNaam = newNaam;
}
void Station::setVolgende(const int &spoorNr, Station *const &newVolgende) {
    REQUIRE(this->properlyInitialized(), "Expected Station to be properly initialized in setVolgende!");
    fSporen.at(spoorNr).second = newVolgende;
}
void Station::setVorige(const int &spoorNr, Station *const &newVorige) {
    REQUIRE(this->properlyInitialized(), "Expected Station to be properly initialized in setVorige!");
    fSporen.at(spoorNr).first = newVorige;
}

const std::string &Station::getType() const {
    REQUIRE(this->properlyInitialized(), "Expected Station to be properly initialized in getType!");
    return fType;
}

void Station::setType(const std::string &type) {
    REQUIRE(this->properlyInitialized(), "Expected Station to be properly initialized in setType!");
    fType = type;
}
