//
// Created by gruzi on 06/03/2023.
//

#include "Tram.h"
#include "Station/Station.h"

Tram::Tram(const int &lijnNr, const int &voertuigNr, TramType type, const int &snelheid,
           const std::vector<std::string> &bediendeStationTypes, const int &aantalDefecten, const int &reparatieTijd) :
fLijnNr(lijnNr), fVoertuigNr(voertuigNr), fType(type), fSnelheid(snelheid), fBediendeStationTypes(bediendeStationTypes),
fAantalDefecten(aantalDefecten), fReparatieTijd(reparatieTijd)
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
int Tram::getSnelheid() const {
    REQUIRE(this->properlyInitialized(), "Expected Tram to be properly initialized in getSnelheid!");
    return fSnelheid;
}
Station* Tram::getBeginStation() const {
    REQUIRE(this->properlyInitialized(), "Expected Tram to be properly initialized in getBeginStation!");
    return fBeginStation;
}
std::vector<std::string> Tram::getBediendeStationTypes() const {
    REQUIRE(this->properlyInitialized(), "Expected TramType to be properly initialized getBediendeStationTypes!");
    return fBediendeStationTypes;
}
std::string tramTypeToString(TramType type) {
    switch(type) {
        case TramType_PCC:
            return "PCC";
        case TramType_Stadslijner:
            return "Stadslijner";
        case TramType_Albatros:
            return "Albatros";
        default:
            return "";
    }
}
TramType stringToTramType(const std::string &typeStr) {
    if(typeStr == "PCC") return TramType_PCC;
    else if(typeStr == "Stadslijner") return TramType_Stadslijner;
    else if(typeStr == "Albatros") return TramType_Albatros;
    return TramType_Null;
}

int Tram::getAantalDefecten() const {
    REQUIRE(this->properlyInitialized(), "Expected Tram to be properly initialized in getBeginStation!");
    return fAantalDefecten;
}
int Tram::getReparatieTijd() const {
    REQUIRE(this->properlyInitialized(), "Expected Tram to be properly initialized!");
    return fReparatieTijd;
}

Station *Tram::getHuidigeStation() const {
    REQUIRE(this->properlyInitialized(), "Expected Tram to be properly initialized in getHuidigeStation!");
    return fHuidigeStation;
}
void Tram::setHuidigeStation(Station* newHuidigeStation) {
    REQUIRE(this->properlyInitialized(), "Expected Tram to be properly initialized in setHuidigeStation!");
    fHuidigeStation = newHuidigeStation;
    ENSURE(getHuidigeStation() == newHuidigeStation, "Expected huidigeStation to equal to the new value!");
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
    REQUIRE(this->properlyInitialized(), "Expected Tram to be properly initialized in getType!");
    const std::string& stationType = station->getType();
    for(size_t i = 0; i<fBediendeStationTypes.size(); i++) {
        if(fBediendeStationTypes[i] == stationType) return true;
    }
    return false;
}


TramType Tram::getType() const {
    REQUIRE(this->properlyInitialized(), "Expected Tram to be properly initialized in getType!");
    return fType;
}

int Tram::getVoertuigNr() const {
    REQUIRE(this->properlyInitialized(), "Expected Tram to be properly initialized in getVoertuigNr!");
    return fVoertuigNr;
}
void Tram::setBeginStation(Station *const &newBeginStation) {
    REQUIRE(this->properlyInitialized(), "Expected Tram to be properly initialized in setBeginStation!");
    fBeginStation = newBeginStation;
    ENSURE(getBeginStation() == newBeginStation, "Expected beginStation to equal to the new value!");
}
double Tram::getReparatieKost() const {
    return fReparatieKost;
}

double Tram::getTotaleReparatieKost() const {
    return fTotaleReparatieKost;
}

void Tram::increaseTotaleReparatieKost(){
    fTotaleReparatieKost += fReparatieKost;
}

bool Tram::isDefect() const {
    return fDefect;
}

void Tram::setDefect(bool defect) {
    Tram::fDefect = defect;
}
