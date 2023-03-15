//
// Created by gruzi on 06/03/2023.
//

#include "Tram.h"
#include "../../DesignByContract.h"

Tram::Tram() {
    _initCheck = this;
    ENSURE(properlyInitialized(), "Expected tram to be properly initialized in constructor!");
}
bool Tram::properlyInitialized() const {
    return _initCheck == this;
}
// getters
int Tram::getLijnNr() const {
    REQUIRE(this->properlyInitialized(), "Expected tram to be properly initialized in getLijnNr!");
    return fLijnNr;
}
int Tram::getSnelheid() const {
    REQUIRE(this->properlyInitialized(), "Expected tram to be properly initialized in getSnelheid!");
    return fSnelheid;
}
Station* Tram::getBeginStation() const {
    REQUIRE(this->properlyInitialized(), "Expected tram to be properly initialized in getBeginStation!");
    return fBeginStation;
}

// setters

void Tram::setLijnNr(const int &newLijnNr) {
    REQUIRE(this->properlyInitialized(), "Expected tram to be properly initialized in setLijnNr!");
    fLijnNr = newLijnNr;
}
void Tram::setSnelheid(const int &newSnelheid) {
    REQUIRE(this->properlyInitialized(), "Expected tram to be properly initialized in setSnelheid!");
    fSnelheid = newSnelheid;
}
void Tram::setBeginStation(Station *const &newBeginStation) {
    REQUIRE(this->properlyInitialized(), "Expected tram to be properly initialized in setBeginStation!");
    fBeginStation = newBeginStation;
}

Station *Tram::getHuidigeStation() const {
    REQUIRE(this->properlyInitialized(), "Expected tram to be properly initialized in getHuidigeStation!");
    return fHuidigeStation;
}

void Tram::setHuidigeStation(Station* newHuidigeStation) {
    REQUIRE(this->properlyInitialized(), "Expected tram to be properly initialized in setHuidigeStation!");
    Tram::fHuidigeStation = newHuidigeStation;
}

