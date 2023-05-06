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
    REQUIRE(this->properlyInitialized(), "Expected Station to be properly initialized!");
    return fNaam;
}
Station* Station::getVolgende(const int &spoorNr) const {
    REQUIRE(this->properlyInitialized(), "Expected Station to be properly initialized!");
    return getSpoor(spoorNr).second;
}
Station* Station::getVorige(const int &spoorNr) const {
    REQUIRE(this->properlyInitialized(), "Expected Station to be properly initialized!");
    return getSpoor(spoorNr).first;
}

std::pair<Station *, Station *> Station::getSpoor(const int &spoorNr) const {
    REQUIRE(this->properlyInitialized(), "Expected Station to be properly initialized!");
    std::map<int, std::pair<Station*, Station*> >::const_iterator spoor = fSporen.find(spoorNr);
    REQUIRE(spoor != fSporen.end(), "Expected spoor to exist!");
    return spoor->second;
}
std::map<int, std::pair<Station *, Station *> > Station::getSporen() const {
    REQUIRE(this->properlyInitialized(), "Expected Station to be properly initialized!");
    return fSporen;
}
const std::string &Station::getType() const {
    REQUIRE(this->properlyInitialized(), "Expected Station to be properly initialized in getType!");
    return fType;
}
bool Station::spoorExists(const int &spoorNr) const {
    REQUIRE(this->properlyInitialized(), "Expected Station to be properly initialized!");
    return fSporen.find(spoorNr) != fSporen.end();
}
// setters


void Station::setSpoor(const int &spoorNr, const std::pair<Station *, Station *> &newSpoor) {
    REQUIRE(this->properlyInitialized(), "Expected Station to be properly initialized!");
    REQUIRE(fSporen.find(spoorNr) == fSporen.end(), "Spoor with given spoorNr already exists!");
    fSporen[spoorNr] = newSpoor;
    ENSURE(getSpoor(spoorNr) == newSpoor, "Expected spoor to equal to setter value!");
}
void Station::setSporen(const std::map<int, std::pair<Station *, Station *> > &newSporen) {
    REQUIRE(this->properlyInitialized(), "Expected Station to be properly initialized!");
    fSporen = newSporen;
    ENSURE(getSporen() == newSporen, "Expected getSporen() to equal to newSporen!");
}
void Station::setNaam(const std::string &newNaam) {
    REQUIRE(this->properlyInitialized(), "Expected Station to be properly initialized in setNaam!");
    fNaam = newNaam;
    ENSURE(getNaam() == newNaam, "Expected getNaam() to equal to newNaam");
}
void Station::setVolgende(const int &spoorNr, Station *const &newVolgende) {
    REQUIRE(this->properlyInitialized(), "Expected Station to be properly initialized in setVolgende!");
    REQUIRE(fSporen.find(spoorNr) != fSporen.end(), "Expected spoor to exist!");
    fSporen.at(spoorNr).second = newVolgende;
    ENSURE(getVolgende(spoorNr) == newVolgende, "Expected getVolgende to equal to newVolgende");
}
void Station::setVorige(const int &spoorNr, Station *const &newVorige) {
    REQUIRE(this->properlyInitialized(), "Expected Station to be properly initialized in setVorige!");
    REQUIRE(fSporen.find(spoorNr) != fSporen.end(), "Expected spoor to exist!");
    fSporen.at(spoorNr).first = newVorige;
    ENSURE(getVorige(spoorNr) == newVorige, "Expected getVorige to equal to newVorige");
}
void Station::setType(const std::string &newType) {
    REQUIRE(this->properlyInitialized(), "Expected Station to be properly initialized in setType!");
    fType = newType;
    ENSURE(getType() == newType, "Expected getType to equal to newType");
}
