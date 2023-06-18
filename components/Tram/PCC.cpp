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

PCC::PCC(const int &lijnNr, const int &voertuigNr, const int &aantalDefecten, const int &reparatieTijd, const double& reparatieKost)
: Tram(lijnNr, voertuigNr, TramType_PCC, 40, getPCCSupportedStations(), aantalDefecten, reparatieTijd)
{
    fReparatieKost = reparatieKost;
    fTotaleReparatieKost = 0;
    _initCheck = this;
    ENSURE(properlyInitialized(), "Expected PCC to be properly initialized in constructor!");
}
bool PCC::properlyInitialized() const {
    return _initCheck == this;
}
