//
// Created by gruzi on 06/03/2023.
//

#include "Tram.h"
#include "Station/Station.h"

Tram::Tram(const int &lijnNr, const int &voertuigNr, const int &aantalDefecten, const int &reparatieTijd) :
fLijnNr(lijnNr), fVoertuigNr(voertuigNr), fAantalDefecten(aantalDefecten), fReparatieTijd(reparatieTijd)
{
    _initCheck = this;
    fBeginStation = 0;
    fHuidigeStation = 0;

    ENSURE(properlyInitialized(), "Expected Tram to be properly initialized in constructor!");
}
bool Tram::properlyInitialized() const {
    return _initCheck == this;
}
int Tram::getLijnNr() const {
    REQUIRE(this->properlyInitialized(), "Expected Tram to be properly initialized in getLijnNr!");
    return fLijnNr;
}
Station* Tram::getBeginStation() const {
    REQUIRE(this->properlyInitialized(), "Expected Tram to be properly initialized in getBeginStation!");
    return fBeginStation;
}
int Tram::getAantalDefecten() const {
    REQUIRE(this->properlyInitialized(), "Expected Tram to be properly initialized in getBeginStation!");
    return fAantalDefecten;
}
int Tram::getReparatieTijd() const {
    REQUIRE(this->properlyInitialized(), "Expected Tram to be properly initialized!");
    return fReparatieTijd;
}

void Tram::setAantalDefecten(const int &newAantalDefecten) {
    REQUIRE(this->properlyInitialized(), "Expected Tram to be properly initialized!");
    fAantalDefecten = newAantalDefecten;
}
void Tram::setReparatieTijd(const int &newReparatieTijd) {
    REQUIRE(this->properlyInitialized(), "Expected Tram to be properly initialized!");
    fReparatieTijd = newReparatieTijd;
}
void Tram::setLijnNr(const int &newLijnNr) {
    REQUIRE(this->properlyInitialized(), "Expected Tram to be properly initialized in setLijnNr!");
    fLijnNr = newLijnNr;
}
void Tram::setBeginStation(Station *const &newBeginStation) {
    REQUIRE(this->properlyInitialized(), "Expected Tram to be properly initialized in setBeginStation!");
    fBeginStation = newBeginStation;
}

Station *Tram::getHuidigeStation() const {
    REQUIRE(this->properlyInitialized(), "Expected Tram to be properly initialized in getHuidigeStation!");
    return fHuidigeStation;
}
void Tram::setHuidigeStation(Station* newHuidigeStation) {
    REQUIRE(this->properlyInitialized(), "Expected Tram to be properly initialized in setHuidigeStation!");
    Tram::fHuidigeStation = newHuidigeStation;
}
Station* Tram::getVolgendeStation() const{
    REQUIRE(this->properlyInitialized(), "Expected Tram to be properly initialized in getVolgendeStation!");
    return fHuidigeStation->getSpoor(fLijnNr).second;
}
Station* Tram::getVorigeStation() const{
    REQUIRE(this->properlyInitialized(), "Expected Tram to be properly initialized in getVorigeStation!");
    return fHuidigeStation->getSpoor(fLijnNr).first;
}
unsigned int Tram::move() {
    REQUIRE(this->properlyInitialized(), "Expected Tram to be properly initialized in moveNaarVolgendeStation!");
    Station* nextStation = getVolgendeStation();
    unsigned int skippedStations = 0;
    while(!supportsStation(nextStation)) {
        skippedStations++;
        nextStation = nextStation->getVolgende(fLijnNr);
    }
    fHuidigeStation = nextStation;
    return skippedStations;
}
unsigned int Tram::move(const unsigned int &steps) {
    REQUIRE(this->properlyInitialized(), "Expected Tram to be properly initialized in moveNaarVolgendeStation!");
    REQUIRE(steps >= 0, "Expected steps >= 0 in move!");
    unsigned int skippedStations = 0;
    for(unsigned int i=0;i<steps;i++) skippedStations += move();
    return skippedStations;
}
bool Tram::supportsStation(const Station *const &station) const {
    return fType->supportsStationType(station->getType());
}

TramType* Tram::getType() const {
    REQUIRE(this->properlyInitialized(), "Expected Tram to be properly initialized in getType!");
    return fType;
}

void Tram::setType(TramType* &type) {
    REQUIRE(this->properlyInitialized(), "Expected Tram to be properly initialized in setType!");
    fType = type;
}

int Tram::getVoertuigNr() const {
    REQUIRE(this->properlyInitialized(), "Expected Tram to be properly initialized in getVoertuigNr!");
    return fVoertuigNr;
}

void Tram::setVoertuigNr(const int& voertuigNr) {
    REQUIRE(this->properlyInitialized(), "Expected Tram to be properly initialized in setVoertuigNr!");
    Tram::fVoertuigNr = voertuigNr;
}
