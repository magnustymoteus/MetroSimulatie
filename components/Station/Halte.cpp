//
// Created by dasha on 18.06.2023.
//

#include "Halte.h"

Halte::Halte(const std::string &naam) :
        Station(naam, "Halte") {
    _initCheck = this;
    ENSURE(properlyInitialized(), "Expected Halte to be properly initialized in constructor!");
}

bool Halte::properlyInitialized() const {
    return _initCheck == this;
}