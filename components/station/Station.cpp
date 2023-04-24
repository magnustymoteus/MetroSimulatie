//
// Created by gruzi on 06/03/2023.
//

#include "Station.h"

#include "DesignByContract.h"

Station::Station() {
    _initCheck = this;
    fSpoorNr=0;
    fVorige=0;
    fVolgende=0;
    ENSURE(properlyInitialized(), "Expected station to be properly initialized in constructor!");
}
bool Station::properlyInitialized() const {
    return _initCheck == this;
}
// getters
std::string Station::getNaam() const {
    REQUIRE(this->properlyInitialized(), "Expected station to be properly initialized in getNaam!");
    return fNaam;
}
int Station::getSpoorNr() const {
    REQUIRE(this->properlyInitialized(), "Expected station to be properly initialized in getSpoorNr!");
    return fSpoorNr;
}
Station* Station::getVolgende() const {
    REQUIRE(this->properlyInitialized(), "Expected station to be properly initialized in getVolgende!");
    return fVolgende;
}
Station* Station::getVorige() const {
    REQUIRE(this->properlyInitialized(), "Expected station to be properly initialized in getVorige!");
    return fVorige;
}

// setters

void Station::setNaam(const std::string &newNaam) {
    REQUIRE(this->properlyInitialized(), "Expected station to be properly initialized in setNaam!");
    fNaam = newNaam;
}
void Station::setSpoorNr(const int &newSpoorNr) {
    REQUIRE(this->properlyInitialized(), "Expected station to be properly initialized in setSpoorNr!");
    fSpoorNr = newSpoorNr;
}
void Station::setVolgende(Station *const &newVolgende) {
    REQUIRE(this->properlyInitialized(), "Expected station to be properly initialized in setVolgende!");
    fVolgende = newVolgende;
}
void Station::setVorige(Station *const &newVorige) {
    REQUIRE(this->properlyInitialized(), "Expected station to be properly initialized in setVorige!");
    fVorige = newVorige;
}

const std::string &Station::getType() const {
    REQUIRE(this->properlyInitialized(), "Expected station to be properly initialized in getType!");
    return fType;
}

void Station::setType(const std::string &type) {
    REQUIRE(this->properlyInitialized(), "Expected station to be properly initialized in setType!");
    fType = type;
}
