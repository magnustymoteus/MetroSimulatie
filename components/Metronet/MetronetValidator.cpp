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
bool MetronetValidator::tramsHaveValidBeginStation() const {
    REQUIRE(properlyInitialized(), "Expected MetronetValidator to be properly initialized!");
    const std::multimap<int, Tram*> &trams = fMetronet->getTrams();
    for(std::multimap<int, Tram*>::const_iterator iter = trams.begin();iter!=trams.end();iter++) {
        const std::map<std::string, Station*> &stations = fMetronet->getStations();
        if(stations.find(iter->second->getBeginStation()->getNaam()) == stations.end()) return false;
    }
    return true;
}
bool MetronetValidator::noDuplicateTrams() const {
    REQUIRE(properlyInitialized(), "Expected MetronetValidator to be properly initialized!");
    const std::multimap<int, Tram*> &trams = fMetronet->getTrams();
    for(std::multimap<int, Tram*>::const_iterator iter = trams.begin();iter!=trams.end();iter++) {
        for(std::multimap<int, Tram*>::const_iterator iter2 = trams.begin();iter2!=trams.end();iter2++) {
            const Tram* const tram1 = iter->second;
            const Tram* const tram2 = iter2->second;
            if(tram1 != tram2 && tram1->getLijnNr() == tram2->getLijnNr()) {
                if(tram1->getVoertuigNr() == tram2->getVoertuigNr()) return false;
            }
        }
    }
    return true;
}
bool MetronetValidator::stationsLinked() const {
    REQUIRE(properlyInitialized(), "Expected MetronetValidator to be properly initialized!");
    const std::map<std::string, Station*> &stations = fMetronet->getStations();
    for(std::map<std::string, Station*>::const_iterator iter = stations.begin(); iter != stations.end(); iter++) {
        const std::map<int, std::pair<Station*, Station*> > &sporen = iter->second->getSporen();
        for(std::map<int, std::pair<Station*, Station*> >::const_iterator iter2 = sporen.begin();
        iter2 != sporen.end(); iter2++) {
            if(!iter->second->getVolgende(iter2->first)) return false;
            if(!iter->second->getVorige(iter2->first)) return false;
        }
    }
    return true;
}
bool MetronetValidator::sporenHaveTrams() const {
    REQUIRE(properlyInitialized(), "Expected MetronetValidator to be properly initialized!");
    const std::map<std::string, Station*> &stations = fMetronet->getStations();
    for(std::map<std::string, Station*>::const_iterator iter = stations.begin(); iter != stations.end(); iter++) {
        const std::map<int, std::pair<Station*, Station*> > &sporen = iter->second->getSporen();
        for(std::map<int, std::pair<Station*, Station*> >::const_iterator iter2 = sporen.begin();
            iter2 != sporen.end(); iter2++) {
            const std::multimap<int, Tram*> &trams = fMetronet->getTrams();
            const bool foundTramForSpoor = trams.find(iter2->first) != trams.end();
            if(!foundTramForSpoor) return false;
        }
    }
    return true;
}
bool MetronetValidator::tramsHaveSpoor() const {
    REQUIRE(properlyInitialized(), "Expected MetronetValidator to be properly initialized!");
    const std::multimap<int, Tram*> &trams = fMetronet->getTrams();
    for(std::multimap<int, Tram*>::const_iterator iter = trams.begin();iter!=trams.end();iter++) {
        const std::map<std::string, Station*> &stations = fMetronet->getStations();
        bool foundSpoor = false;
        for(std::map<std::string, Station*>::const_iterator iter2 = stations.begin();
        iter2 != stations.end(); iter2++) {
            const std::map<int, std::pair<Station*, Station*> > &sporen = iter2->second->getSporen();
            if(sporen.find(iter->second->getLijnNr()) != sporen.end()) foundSpoor = true;
        }
        if(!foundSpoor) return false;
    }
    return true;
}
void MetronetValidator::validateTrams() const {
    REQUIRE(properlyInitialized(), "Expected MetronetValidator to be properly initialized!");
    const std::multimap<int, Tram*> &trams = fMetronet->getTrams();
    for(std::multimap<int, Tram*>::const_iterator iter = trams.begin(); iter != trams.end(); iter++) {
        const Tram* const currentTram = iter->second;
        TramValidator tramValidator(currentTram);
        tramValidator.validate();
    }
}
bool MetronetValidator::validate() const {
    REQUIRE(properlyInitialized(), "Expected MetronetValidator to be properly initialized!");
    bool consistent = fMetronet->getIsConsistent();
    const bool noDupTrams = noDuplicateTrams();
    const bool stopsLinked = stationsLinked();
    const bool tramsHaveSpr = tramsHaveSpoor();
    const bool sprHaveTrams = sporenHaveTrams();
    const bool tramsHaveValidBeginSt = tramsHaveValidBeginStation();

    CERR_IF_FALSE(noDupTrams,
                   MetronetInconsistentException(getInvalidationMessage("Duplicate trams found!").c_str()));
    CERR_IF_FALSE(stopsLinked, MetronetInconsistentException(
            getInvalidationMessage("Stations are not properly linked!").c_str()));
    CERR_IF_FALSE(tramsHaveSpr, MetronetInconsistentException(
            getInvalidationMessage("A tram doesn't have a corresponding spoor!").c_str()));
    CERR_IF_FALSE(sprHaveTrams, MetronetInconsistentException(
            getInvalidationMessage("A spoor doesn't have a corresponding tram!").c_str()));
    CERR_IF_FALSE(tramsHaveValidBeginSt, MetronetInconsistentException(
            getInvalidationMessage("A tram doesn't have a valid beginStation!").c_str()));

    const bool bools[] = {noDupTrams, stopsLinked, tramsHaveSpr, sprHaveTrams,
                          tramsHaveValidBeginSt};
    const unsigned int numOfBools = sizeof(bools)/sizeof(bools[0]);
    for(unsigned int i=0;i<numOfBools;i++) consistent = consistent && bools[i];
    validateTrams();
    return consistent;
}
std::string MetronetValidator::getInvalidationMessage(const std::string &error) const {
    REQUIRE(properlyInitialized(), "Expected MetronetValidator to be properly initialized!");
    return "Metronet validation failed: "+error;
}
