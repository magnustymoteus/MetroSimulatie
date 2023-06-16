//
// Created by gruzi on 16/06/2023.
//

#include "Stadslijner.h"

Stadslijner::Stadslijner(const int &lijnNr, const int &voertuigNr) :
StandardTram(lijnNr, voertuigNr, TramType_Stadslijner) {
    _initCheck = this;

    ENSURE(properlyInitialized(), "Expected Stadslijner to be properly initialized in constructor!");
}

bool Stadslijner::properlyInitialized() const {
    return _initCheck == this;
}