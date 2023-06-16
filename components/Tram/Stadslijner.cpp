//
// Created by gruzi on 16/06/2023.
//

#include "Stadslijner.h"

Stadslijner::Stadslijner(const int &lijnNr, const int &voertuigNr, TramType type) :
StandardTram(lijnNr, voertuigNr, type) {
    _initCheck = this;

    ENSURE(properlyInitialized(), "Expected Stadslijner to be properly initialized in constructor!");
}

bool Stadslijner::properlyInitialized() const {
    return _initCheck == this;
}