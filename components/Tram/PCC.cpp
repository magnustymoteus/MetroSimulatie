//
// Created by gruzi on 16/06/2023.
//

#include "PCC.h"

std::vector<std::string> getPCCSupportedStations() {
    std::vector<std::string> supportedStations;
    supportedStations.push_back("Metrostation");
    supportedStations.push_back("Halte");
    return supportedStations;
}

PCC::PCC(const int &lijnNr, const int &voertuigNr, TramType type, const int &aantalDefecten, const int &reparatieTijd)
: Tram(lijnNr, voertuigNr, type, 40, getPCCSupportedStations(), aantalDefecten, reparatieTijd)
{
    _initCheck = this;

    ENSURE(properlyInitialized(), "Expected PCC to be properly initialized in constructor!");
}
bool PCC::properlyInitialized() const {
    return _initCheck == this;
}