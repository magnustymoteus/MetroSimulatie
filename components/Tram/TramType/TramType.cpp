//
// Created by gruzi on 25/04/2023.
//

#include "TramType.h"

TramType::TramType(const std::string &newNaam, const int &newSnelheid,
                   const std::vector<std::string> &newBediendeStationTypes) : fNaam(newNaam), fSnelheid(newSnelheid),
                   fBediendeStationTypes(newBediendeStationTypes) {
    _initCheck = this;
    ENSURE(properlyInitialized(), "Expected TramType to be properly initialized in constructor!");
}

bool TramType::properlyInitialized() const {
    return _initCheck == this;
}

std::string TramType::getNaam() const {
    REQUIRE(this->properlyInitialized(), "Expected Tram to be properly initialized getNaam!");
    return fNaam;
}

int TramType::getSnelheid() const {
    REQUIRE(this->properlyInitialized(), "Expected Tram to be properly initialized getSnelheid!");
    return fSnelheid;
}

std::vector<std::string> TramType::getBediendeStationTypes() {
    REQUIRE(this->properlyInitialized(), "Expected Tram to be properly initialized getBediendeStationTypes!");
    return fBediendeStationTypes;
}

void TramType::setNaam(const std::string &newNaam) {
    REQUIRE(this->properlyInitialized(), "Expected Tram to be properly initialized setNaam!");
    fNaam = newNaam;
}

void TramType::setSnelheid(const int &newSnelheid) {
    REQUIRE(this->properlyInitialized(), "Expected Tram to be properly initialized setSnelheid!");
    fSnelheid = newSnelheid;
}

void TramType::setBediendeStationTypes(const std::vector<std::string> &newBediendeStationTypes) {
    REQUIRE(this->properlyInitialized(), "Expected Tram to be properly initialized setBediendeStationTypes!");
    fBediendeStationTypes = newBediendeStationTypes;
}