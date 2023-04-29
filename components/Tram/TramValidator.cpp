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
    return "Tram validation failed: "+error;
}

bool TramValidator::validate() const {
    REQUIRE(properlyInitialized(), "Expected TramValidator to be properly initialized in validate!");
    const Tram* const &tram = fTramObject;
    bool validated = true;
    const bool tramHasType = tram->getType();
    const bool tramHasVoertuigNr = tram->getVoertuigNr();
    const bool tramHasLijnNr = tram->getLijnNr();
    const bool tramHasHuidigeStation = tram->getHuidigeStation();
    const bool tramHasBeginStation = tram->getBeginStation();

    const bool tramHasVolgendeStation = tram->getVolgendeStation();
    const bool tramHasVorigeStation  = tram->getVorigeStation();

    const bool tramSupportsBeginStation = tram->supportsStation(tram->getBeginStation());
    const bool tramSupportsHuidigeStation = tram->supportsStation(tram->getHuidigeStation());

    EXPECT(tramHasType,
           VUnhandleableMetroObjectException(getInvalidationMessage("Tram type is null").c_str()));
    EXPECT(tramHasVoertuigNr,
           VUnhandleableMetroObjectException(getInvalidationMessage("Tram voertuigNr is null").c_str()));
    EXPECT(tramHasLijnNr,
           VUnhandleableMetroObjectException(getInvalidationMessage("Tram lijnNr is null").c_str()));
    EXPECT(tramHasHuidigeStation,
           VUnhandleableMetroObjectException(getInvalidationMessage("Tram huidigeStation is null").c_str()));
    EXPECT(tramHasBeginStation,
           VUnhandleableMetroObjectException(getInvalidationMessage("Tram beginStation is null").c_str()));
    EXPECT(tramSupportsBeginStation, VUnhandleableMetroObjectException(
            getInvalidationMessage("Tram beginStation is not supported").c_str()));
    EXPECT(tramSupportsHuidigeStation, VUnhandleableMetroObjectException(
            getInvalidationMessage("Tram huidigeStation is not supported").c_str()));
    EXPECT_NOTHROW(tramHasVolgendeStation,
           VUnhandleableMetroObjectException(getInvalidationMessage("Tram volgendeStation is null").c_str()));
    EXPECT_NOTHROW(tramHasVorigeStation,
           VUnhandleableMetroObjectException(getInvalidationMessage("Tram vorigeStation is null").c_str()));

    const bool bools[] = {tramHasType, tramHasVoertuigNr, tramHasLijnNr, tramHasHuidigeStation,
                           tramHasBeginStation, tramHasVolgendeStation, tramHasVorigeStation,
                           tramSupportsBeginStation, tramSupportsHuidigeStation};
    const unsigned int numOfBools = sizeof(bools)/sizeof(bools[0]);
    for(unsigned int i =0;i<numOfBools;i++) validated = validated && bools[i];

    return validated;
}