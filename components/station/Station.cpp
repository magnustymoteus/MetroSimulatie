//
// Created by gruzi on 06/03/2023.
//

#include "Station.h"

// getters
std::string Station::getNaam() const {
    return fNaam;
}
int Station::getSpoorNr() const {
    return fSpoorNr;
}
Station* Station::getVolgende() const {
    return fVolgende;
}
Station* Station::getVorige() const {
    return fVorige;
}

// setters

void Station::setNaam(const std::string &newNaam) {
    fNaam = newNaam;
}
void Station::setSpoorNr(const int &newSpoorNr) {
    fSpoorNr = newSpoorNr;
}
void Station::setVolgende(Station *const &newVolgende) {
    fVolgende = newVolgende;
}
void Station::setVorige(Station *const &newVorige) {
    fVorige = newVorige;
}