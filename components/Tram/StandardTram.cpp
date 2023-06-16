//
// Created by gruzi on 16/06/2023.
//

#include "StandardTram.h"

std::vector<std::string> getStandardTramSupportedStations() {
    std::vector<std::string> supportedStations;
    supportedStations.push_back("Metrostation");
    return supportedStations;
}

StandardTram::StandardTram(const int &lijnNr, const int &voertuigNr, TramType type) :
Tram(lijnNr, voertuigNr, type, 70, getStandardTramSupportedStations(), 0,0)
{
    _initCheck = this;
    ENSURE(properlyInitialized(), "Expected StandardTram to be properly initialized in constructor!");
}

bool StandardTram::properlyInitialized() const {
    return _initCheck == this;
}