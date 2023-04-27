//
// Created by gruzi on 27/04/2023.
//

#include "StationValidator.h"

StationValidator::StationValidator(const Station* const &stationObject) : fStationObject(stationObject) {
    _initCheck = this;
    ENSURE(properlyInitialized(), "Expected StationValidator to be properly initialized in constructor!");
}

bool StationValidator::properlyInitialized() const {
    return _initCheck == this;
}

std::string StationValidator::getInvalidationMessage(const std::string &error) const {
    REQUIRE(properlyInitialized(), "Expected StationValidator to be properly initialized in getInvalidationMessage!");
    return "Station validation failed: "+error+"\n";
}


