//
// Created by gruzi on 06/03/2023.
//

#include "Station.h"
/*
 * This serves as the implementation for a metro station.
 * @author Patryk Pilichowski
 * @date 06/03/2023
 * @version 0.1
 */

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