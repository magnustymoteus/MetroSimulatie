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
    std::map<int, Station*> sporen = metronet.getSporen();
    for(std::map<int, Station*>::const_iterator iter = sporen.begin();iter!=sporen.end();iter++) {
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
    std::map<int, Tram*> trams = metronet.getTrams();
    std::map<int, Station*> sporen = metronet.getSporen();
    for(std::map<int, Tram*>::const_iterator iter = trams.begin();iter!=trams.end();iter++) {
        if(sporen.find(iter->second->getLijnNr()) == sporen.end())
            std::cerr << kNotConsistent << "there is no spoor for lijnNr " << iter->second->getLijnNr() << "\n";
    }
}

void MetronetValidator::tramForSpoorCheck(const Metronet &metronet) {
    std::map<int, Station*> sporen = metronet.getSporen();
    std::map<int, Tram*> trams = metronet.getTrams();
    for(std::map<int, Station*>::const_iterator iter = sporen.begin();iter!=sporen.end();iter++) {
        if(trams.find(iter->second->getSpoorNr()) == trams.end())
            std::cerr << kNotConsistent << "there is no tram for spoor " << iter->second->getSpoorNr() << "\n";
    }
}
void MetronetValidator::duplicateTramsCheck(const Metronet &metronet) {
    std::map<int, Tram*> trams = metronet.getTrams();
    for(std::map<int, Tram*>::const_iterator iter = trams.begin();iter!=trams.end();iter++) {
        for(std::map<int, Tram*>::const_iterator iter2 = trams.begin();iter2!=trams.end();iter2++) {
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