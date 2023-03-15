//
// Created by gruzi on 15/03/2023.
//

#include "MetronetValidator.h"
#include "DesignByContract.h"
#include <iostream>

std::string kNotConsistent = "The metronet is not consistent!: ";

MetronetValidator::MetronetValidator() {
    _initCheck = this;
    ENSURE(properlyInitialized(), "Expected MetronetValidator to be properly initialized in constructor!");
}

bool MetronetValidator::properlyInitialized() const {
    return _initCheck == this;
}

void MetronetValidator::stationsLinkCheck(const Metronet &metronet) {
    for(std::map<int, Station*>::const_iterator iter = metronet.fSporen.begin();iter!=metronet.fSporen.end();iter++) {
        Station* beginStation = iter->second;
        Station* currentStation = iter->second;
        do {
            if(!currentStation || !currentStation->getVorige() || !currentStation->getVolgende())
                std::cerr << kNotConsistent << "station " << currentStation->getNaam() << " is not properly linked!\n";
            currentStation = currentStation->getVolgende();
        } while(currentStation != beginStation);
    }
}

void MetronetValidator::lijnNrExistsCheck(const Metronet &metronet) {
    for(std::map<int, Tram*>::const_iterator iter = metronet.fTrams.begin();iter!=metronet.fTrams.end();iter++) {
        if(metronet.fSporen.find(iter->second->getLijnNr()) == metronet.fSporen.end())
            std::cerr << kNotConsistent << "there is no spoor for lijnNr " << iter->second->getLijnNr() << "\n";
    }
}

void MetronetValidator::tramForSpoorCheck(const Metronet &metronet) {
    for(std::map<int, Station*>::const_iterator iter = metronet.fSporen.begin();iter!=metronet.fSporen.end();iter++) {
        if(metronet.fTrams.find(iter->second->getSpoorNr()) == metronet.fTrams.end())
            std::cerr << kNotConsistent << "there is no tram for spoor " << iter->second->getSpoorNr() << "\n";
    }
}
void MetronetValidator::duplicateTramsCheck(const Metronet &metronet) {
    for(std::map<int, Tram*>::const_iterator iter = metronet.fTrams.begin();iter!=metronet.fTrams.end();iter++) {
        for(std::map<int, Tram*>::const_iterator iter2 = metronet.fTrams.begin();iter2!=metronet.fTrams.end();iter2++) {
            if(iter->second->getLijnNr() == iter2->second->getLijnNr() && iter->second != iter2->second)
                std::cerr << kNotConsistent << "found duplicate tram for" << iter->second->getLijnNr() << "\n";
        }
    }
}
void MetronetValidator::consistencyCheck(const Metronet &metronet) {
    duplicateTramsCheck(metronet);
    tramForSpoorCheck(metronet);
    lijnNrExistsCheck(metronet);
    stationsLinkCheck(metronet);
}