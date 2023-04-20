//
// Created by gruzi on 06/03/2023.
//

#include <vector>
#include "Tram.h"
#include "Station.h"
#include "DesignByContract.h"
#include "TramImporter.h"

Tram::Tram() {
    _initCheck = this;
    fSnelheid=0;
    fLijnNr=0;
    fBeginStation=0;
    fHuidigeStation=0;
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
Station* Tram::getVolgendeStation() const{
    REQUIRE(this->properlyInitialized(), "Expected tram to be properly initialized in getVolgendeStation!");
    return fHuidigeStation->getVolgende();
}
Station* Tram::getVorigeStation() const{
    REQUIRE(this->properlyInitialized(), "Expected tram to be properly initialized in getVorigeStation!");
    return fHuidigeStation->getVorige();
}
void Tram::moveNaarVolgendeStation(){
    REQUIRE(this->properlyInitialized(), "Expected tram to be properly initialized in moveNaarVolgendeStation!");
    fHuidigeStation = getVolgendeStation();
}

const std::string &Tram::getType() const {
    REQUIRE(this->properlyInitialized(), "Expected tram to be properly initialized in getType!");
    return fType;
}

void Tram::setType(const std::string &type) {
    REQUIRE(this->properlyInitialized(), "Expected tram to be properly initialized in setType!");
    TramImporter tramImporter;
    REQUIRE(tramImporter.isTramTypeSupported(type), "Expected tram type to be supported!");
    fType = type;
}

int Tram::getVoertuigNr() const {
    REQUIRE(this->properlyInitialized(), "Expected tram to be properly initialized in getVoertuigNr!");
    return fVoertuigNr;
}

void Tram::setVoertuigNr(const int& voertuigNr) {
    REQUIRE(this->properlyInitialized(), "Expected tram to be properly initialized in setVoertuigNr!");
    Tram::fVoertuigNr = voertuigNr;
}

