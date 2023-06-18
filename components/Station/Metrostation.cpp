//
// Created by dasha on 18.06.2023.
//

#include "Metrostation.h"

Metrostation::Metrostation(const std::string &naam):
        Station(naam, "Halte") {
    _initCheck = this;
    ENSURE(properlyInitialized(), "Expected Halte to be properly initialized in constructor!");
}

bool Metrostation::properlyInitialized() const {
    return _initCheck == this;
}