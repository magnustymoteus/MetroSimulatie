//
// Created by gruzi on 15/03/2023.
//

#include "MetronetValidator.h"

#include "Tram/TramValidator.h"

std::string kNotConsistent = "The Metronet is not consistent!: ";

MetronetValidator::MetronetValidator(const Metronet* const &metronet) : fMetronet(metronet) {
    _initCheck = this;
    ENSURE(properlyInitialized(), "Expected MetronetValidator to be properly initialized in constructor!");
}

bool MetronetValidator::properlyInitialized() const {
    return _initCheck == this;
}

void MetronetValidator::stationsLinkCheck() const {
    REQUIRE(properlyInitialized(), "Expected MetronetValidator to be properly initialized!");
    std::map<int, Station*> sporen = fMetronet->getSporen();
    for(std::map<int, Station*>::const_iterator iter = sporen.begin();iter!=sporen.end();iter++) {
        Station* beginStation = iter->second;
        Station* currentStation = iter->second;
        do {
            if(!currentStation || !currentStation->getVorige() || !currentStation->getVolgende())
                std::cerr << kNotConsistent << "Station " << currentStation->getNaam() << " is not properly linked!\n";
            currentStation = currentStation->getVolgende();
        } while(currentStation != beginStation);
    }
}

void MetronetValidator::lijnNrExistsCheck() const {
    REQUIRE(properlyInitialized(), "Expected MetronetValidator to be properly initialized!");
    std::multimap<int, Tram*> trams = fMetronet->getTrams();
    std::map<int, Station*> sporen = fMetronet->getSporen();
    for(std::multimap<int, Tram*>::const_iterator iter = trams.begin();iter!=trams.end();iter++) {
        if(sporen.find(iter->second->getLijnNr()) == sporen.end())
            std::cerr << kNotConsistent << "there is no spoor for lijnNr " << iter->second->getLijnNr() << "\n";
    }
}

void MetronetValidator::tramForSpoorCheck() const {
    REQUIRE(properlyInitialized(), "Expected MetronetValidator to be properly initialized!");
    std::map<int, Station*> sporen = fMetronet->getSporen();
    std::multimap<int, Tram*> trams = fMetronet->getTrams();
    for(std::map<int, Station*>::const_iterator iter = sporen.begin();iter!=sporen.end();iter++) {
        if(trams.find(iter->second->getSpoorNr()) == trams.end())
            std::cerr << kNotConsistent << "there is no Tram for spoor " << iter->second->getSpoorNr() << "\n";
    }
}
void MetronetValidator::duplicateTramsCheck() const {
    REQUIRE(properlyInitialized(), "Expected MetronetValidator to be properly initialized!");
    std::multimap<int, Tram*> trams = fMetronet->getTrams();
    for(std::multimap<int, Tram*>::const_iterator iter = trams.begin();iter!=trams.end();iter++) {
        for(std::multimap<int, Tram*>::const_iterator iter2 = trams.begin();iter2!=trams.end();iter2++) {
            if(iter->second->getLijnNr() == iter2->second->getLijnNr()
            && iter->second->getVoertuigNr() == iter2->second->getVoertuigNr() && iter->second != iter2->second)
                std::cerr << kNotConsistent << "found duplicate Tram for "
                << iter->second->getLijnNr() << "(" << iter->second->getVoertuigNr() << ")" << "\n";
        }
    }
}
void MetronetValidator::validate() const {
    REQUIRE(properlyInitialized(), "Expected MetronetValidator to be properly initialized!");
    duplicateTramsCheck();
    tramForSpoorCheck();
    lijnNrExistsCheck();
    stationsLinkCheck();

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
