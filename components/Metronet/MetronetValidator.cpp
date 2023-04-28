//
// Created by gruzi on 15/03/2023.
//

#include "MetronetValidator.h"

#include "Tram/TramValidator.h"

MetronetValidator::MetronetValidator(const Metronet* const &metronet) : fMetronet(metronet) {
    _initCheck = this;
    ENSURE(properlyInitialized(), "Expected MetronetValidator to be properly initialized in constructor!");
}

bool MetronetValidator::properlyInitialized() const {
    return _initCheck == this;
}

void MetronetValidator::noDuplicateTramsValidation() const {
    REQUIRE(properlyInitialized(), "Expected MetronetValidator to be properly initialized!");
    std::multimap<int, Tram*> trams = fMetronet->getTrams();
    for(std::multimap<int, Tram*>::const_iterator iter = trams.begin();iter!=trams.end();iter++) {
        for(std::multimap<int, Tram*>::const_iterator iter2 = trams.begin();iter2!=trams.end();iter2++) {
            const Tram* const tram1 = iter->second;
            const Tram* const tram2 = iter2->second;
            if(tram1 != tram2 && tram1->getLijnNr() == tram2->getLijnNr()) {
                EXPECT_NOTHROW(tram1->getVoertuigNr() != tram2->getVoertuigNr(),
                       MetronetInconsistentException("Duplicate trams found!"));
                return;
            }
        }
    }
}
void MetronetValidator::validate() const {
    REQUIRE(properlyInitialized(), "Expected MetronetValidator to be properly initialized!");
    noDuplicateTramsValidation();
    std::multimap<int, Tram*> trams = fMetronet->getTrams();
    for(std::multimap<int, Tram*>::const_iterator iter = trams.begin(); iter != trams.end(); iter++) {
        const Tram* const currentTram = iter->second;
        TramValidator tramValidator(currentTram);
        tramValidator.validate();
    }
}
std::string MetronetValidator::getInvalidationMessage(const std::string &error) const {
    REQUIRE(properlyInitialized(), "Expected MetronetValidator to be properly initialized!");
    return "Metronet validation failed: "+error+"\n";
}
