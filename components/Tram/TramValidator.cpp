//
// Created by gruzi on 25/04/2023.
//

#include "TramValidator.h"

TramValidator::TramValidator(const Tram* const &tramObject) : fTramObject(tramObject) {
    _initCheck = this;
    ENSURE(properlyInitialized(), "Expected TramValidator to be properly initialized in constructor!");
}

bool TramValidator::properlyInitialized() const {
    return _initCheck == this;
}

std::string TramValidator::getInvalidationMessage(const std::string &error) const {
    REQUIRE(properlyInitialized(), "Expected TramValidator to be properly initialized in getInvalidationMessage!");
    return "Tram validation failed: "+error+"\n";
}

void TramValidator::validate() const {
    REQUIRE(properlyInitialized(), "Expected TramValidator to be properly initialized in validate!");
    const Tram* const &tram = fTramObject;
    EXPECT(tram->getType(),
           VUnhandleableMetroObjectException(getInvalidationMessage("Tram type is null").c_str()));
    EXPECT(tram->getVoertuigNr(),
           VUnhandleableMetroObjectException(getInvalidationMessage("Tram voertuigNr is null").c_str()));
    EXPECT(tram->getLijnNr(),
           VUnhandleableMetroObjectException(getInvalidationMessage("Tram lijnNr is null").c_str()));
    EXPECT(tram->getHuidigeStation(),
           VUnhandleableMetroObjectException(getInvalidationMessage("Tram huidigeStation is null").c_str()));
    EXPECT(tram->getBeginStation(),
           VUnhandleableMetroObjectException(getInvalidationMessage("Tram beginStation is null").c_str()));
    EXPECT(tram->getVolgendeStation(),
           VUnhandleableMetroObjectException(getInvalidationMessage("Tram volgendeStation is null").c_str()));
    EXPECT(tram->getVorigeStation(),
           VUnhandleableMetroObjectException(getInvalidationMessage("Tram vorigeStation is null").c_str()));

    EXPECT(tram->supportsStation(tram->getBeginStation()), VUnhandleableMetroObjectException(
            getInvalidationMessage("Tram beginStation is not supported").c_str()));
    EXPECT(tram->supportsStation(tram->getHuidigeStation()), VUnhandleableMetroObjectException(
            getInvalidationMessage("Tram huidigeStation is not supported").c_str()));
}