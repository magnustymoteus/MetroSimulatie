//
// Created by gruzi on 15/03/2023.
//

#include "MetronetValidator.h"

#include <iostream>

#include "DesignByContract.h"

std::string kNotConsistent = "The Metronet is not consistent!: ";

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
                std::cerr << kNotConsistent << "Station " << currentStation->getNaam() << " is not properly linked!\n";
            currentStation = currentStation->getVolgende();
        } while(currentStation != beginStation);
    }
}

void MetronetValidator::lijnNrExistsCheck(const Metronet &metronet) {
    std::multimap<int, Tram*> trams = metronet.getTrams();
    std::map<int, Station*> sporen = metronet.getSporen();
    for(std::multimap<int, Tram*>::const_iterator iter = trams.begin();iter!=trams.end();iter++) {
        if(sporen.find(iter->second->getLijnNr()) == sporen.end())
            std::cerr << kNotConsistent << "there is no spoor for lijnNr " << iter->second->getLijnNr() << "\n";
    }
}

void MetronetValidator::tramForSpoorCheck(const Metronet &metronet) {
    std::map<int, Station*> sporen = metronet.getSporen();
    std::multimap<int, Tram*> trams = metronet.getTrams();
    for(std::map<int, Station*>::const_iterator iter = sporen.begin();iter!=sporen.end();iter++) {
        if(trams.find(iter->second->getSpoorNr()) == trams.end())
            std::cerr << kNotConsistent << "there is no Tram for spoor " << iter->second->getSpoorNr() << "\n";
    }
}
void MetronetValidator::duplicateTramsCheck(const Metronet &metronet) {
    // TODO: correct linebreaks of code
    std::multimap<int, Tram*> trams = metronet.getTrams();
    for(std::multimap<int, Tram*>::const_iterator iter = trams.begin();iter!=trams.end();iter++) {
        for(std::multimap<int, Tram*>::const_iterator iter2 = trams.begin();iter2!=trams.end();iter2++) {
            if(iter->second->getLijnNr() == iter2->second->getLijnNr()
            && iter->second->getVoertuigNr() == iter2->second->getVoertuigNr() && iter->second != iter2->second)
                std::cerr << kNotConsistent << "found duplicate Tram for "
                << iter->second->getLijnNr() << "(" << iter->second->getVoertuigNr() << ")" << "\n";
        }
    }
}
void MetronetValidator::consistencyCheck(const Metronet &metronet) {
    duplicateTramsCheck(metronet);
    tramForSpoorCheck(metronet);
    lijnNrExistsCheck(metronet);
    stationsLinkCheck(metronet);
}