//
// Created by gruzi on 16/06/2023.
//

#include "Albatros.h"

Albatros::Albatros(const int &lijnNr, const int &voertuigNr, TramType type) : StandardTram(lijnNr, voertuigNr, type) {
    _initCheck = this;

    ENSURE(properlyInitialized(), "Expected Albatros to be properly initialized in constructor!");
}
bool Albatros::properlyInitialized() const {
    return _initCheck == this;
}