//
// Created by gruzi on 06/03/2023.
//

#include "Tram.h"

// getters
int Tram::getLijnNr() const {
    return fLijnNr;
}
int Tram::getSnelheid() const {
    return fSnelheid;
}
Station* Tram::getBeginStation() const {
    return fBeginStation;
}

// setters

void Tram::setLijnNr(const int &newLijnNr) {
    fLijnNr = newLijnNr;
}
void Tram::setSnelheid(const int &newSnelheid) {
    fSnelheid = newSnelheid;
}
void Tram::setBeginStation(Station *const &newBeginStation) {
    fBeginStation = newBeginStation;
}

Station *Tram::getHuidigeStation() const {
    return fHuidigeStation;
}

void Tram::setHuidigeStation(Station *fHuidigeStation) {
    Tram::fHuidigeStation = fHuidigeStation;
}

