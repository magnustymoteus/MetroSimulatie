//
// Created by gruzi on 12/03/2023.
//

#include "Metronet.h"

#include <iostream>
#include <ctime>

#include "Exceptions/MetronetInconsistentException.h"

Metronet::Metronet(std::map<std::string, Station*> &newStations, std::multimap<int, Tram*> &newTrams) :
fStations(newStations), fTrams(newTrams), isConsistent(true)
{
    _initCheck = this;
    ENSURE(properlyInitialized(), "Expected Metronet to be properly initialized!");
}
Metronet::Metronet() : isConsistent(true) {
    _initCheck = this;
    ENSURE(properlyInitialized(), "Expected Metronet to be properly initialized!");
}
bool Metronet::properlyInitialized() const {
    return _initCheck == this;
}

void Metronet::setIsConsistent(const bool &newIsConsistent) {
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    isConsistent = newIsConsistent;
    ENSURE(getIsConsistent() == isConsistent, "Expected isConsistent to equal to the setter value!");
}

bool Metronet::getIsConsistent() const {
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    return isConsistent;
}

Metronet::~Metronet() {
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    for(std::map<std::string, Station*>::const_iterator iter = fStations.begin(); iter!=fStations.end();iter++) {
        delete iter->second;
    }
    for(std::multimap<int, Tram*>::const_iterator iter = fTrams.begin(); iter != fTrams.end(); iter++) {
        delete iter->second;
    }
    for(std::map<std::string, TramType*>::const_iterator iter = fTramTypes.begin(); iter != fTramTypes.end();iter++) {
        delete iter->second;
    }
}
void wait(const long &durationInSeconds) {
    clock_t now = clock();
    while(clock()-now < durationInSeconds*CLOCKS_PER_SEC);
}
void Metronet::autoSimulate(const int &durationInSeconds) {
    /*
     * This function simulates circulating of trams on the metro network
     * @param durationInSeconds number of steps (1 step/sec) made by all trams
     * @return nothing (void function)
     * */

    // too simple, needs more parallelism in the future
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    if(isConsistent) {
        std::multimap<int, Tram *>::iterator iter = fTrams.begin();
        for (int i = 0; i < durationInSeconds; i++) {
            wait(1);
            std::cout << "Stap " << i + 1 << ":\n";
            for (iter = fTrams.begin(); iter != fTrams.end(); iter++) {
                std::cout << "\t";
                moveTram(iter->second);
            }
        }
    }
    else std::cerr << "Cannot simulate an inconsistent metronet!" << std::endl;
}
bool Metronet::isTramOnStation(const std::string &stationName, const int &spoorNr) const {
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    for(std::multimap<int, Tram*>::const_iterator iter = fTrams.begin(); iter != fTrams.end(); iter++) {
        Station* huidigeStation = iter->second->getHuidigeStation();
        if(iter->second->getLijnNr() == spoorNr && huidigeStation->getNaam() == stationName) return true;
    }
    return false;
}
void Metronet::pushStation(Station* station) {
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    fStations.insert(std::make_pair(station->getNaam(), station));
    ENSURE(fStations.find(station->getNaam()) != fStations.end(), "Expected station to be pushed to fStations!");
}
void Metronet::pushTram(Tram* tram) {
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    fTrams.insert(std::make_pair(tram->getLijnNr(), tram));
    ENSURE(fTrams.find(tram->getLijnNr()) != fTrams.end(), "Expected tram to be pushed to fTrams!");
}
bool Metronet::tramExists(const int &lijnNr) const {
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    return fTrams.find(lijnNr) != fTrams.end();
}
std::map<std::string, TramType*> Metronet::getTramTypes() const {
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    return fTramTypes;
}
void Metronet::setTramTypes(const std::map<std::string, TramType *> &newTramTypes) {
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    fTramTypes = newTramTypes;
    ENSURE(getTramTypes() == newTramTypes, "Expected fTramTypes to equal to the setter value!");
}
void Metronet::moveTram(Tram* &tram, const int &steps) const {
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    const int lijnNr = tram->getLijnNr();
    const int voertuigNr = tram->getVoertuigNr();
    Station *huidigeStation = tram->getHuidigeStation();
    unsigned int skippedStations = tram->move(steps);
    std::cout << "Tram " << lijnNr << " (" << voertuigNr << ") (" << tram->getType()->getNaam() <<
    ") reed van Station " << huidigeStation->getNaam() << " (" << huidigeStation->getType() << ")" <<
    " naar Station " << tram->getHuidigeStation()->getNaam() << " (" <<
    tram->getHuidigeStation()->getType() << ")" << ".\n";

    if(skippedStations) std::cout << "\t\t" << skippedStations <<
    " halte(s) genegeerd omdat tram daar niet mag stoppen.\n";
}
Station* Metronet::retrieveStation(const std::string &naam) const {
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    return fStations.find(naam)->second;
}
Tram* Metronet::retrieveTram(const int &lijnNr, const int &voertuigNr) const{
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    std::pair <std::multimap<int, Tram*>::const_iterator, std::multimap<int,Tram*>::const_iterator> range =
            fTrams.equal_range(lijnNr);
    for(std::_Rb_tree_const_iterator<std::pair<const int, Tram *> > i = range.first; i != range.second; i++){
        if(i->second->getVoertuigNr() == voertuigNr){
            return i->second;
        }
    }
    return 0;
}

std::multimap<int, Tram*> Metronet::getTrams() const {
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    return fTrams;
}
void Metronet::setTrams(std::multimap<int, Tram*> &newTrams) {
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    fTrams = newTrams;
    ENSURE(getTrams() == newTrams, "Expected fTrams to equal to setter value!");
}

std::map<std::string, Station *> Metronet::getStations() const {
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    return fStations;
}
void Metronet::setStations(std::map<std::string, Station *> &newStations) {
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    fStations=newStations;
    ENSURE(getStations() == newStations, "Expected fStations to equal to the setter value!");
}
