//
// Created by gruzi on 16/06/2023.
//

#include "Albatros.h"

Albatros::Albatros(const int &lijnNr, const int &voertuigNr) : StandardTram(lijnNr, voertuigNr, TramType_Albatros) {
    _initCheck = this;

    ENSURE(properlyInitialized(), "Expected Albatros to be properly initialized in constructor!");
}
bool Albatros::properlyInitialized() const {
    return _initCheck == this;
}