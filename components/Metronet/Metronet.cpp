//
// Created by gruzi on 12/03/2023.
//

#include "Metronet.h"

#include <iostream>
#include <ctime>

Metronet::Metronet(std::map<std::string, Station*> &newStations, std::multimap<int, Tram*> &newTrams) :
fStations(newStations), fTrams(newTrams)
{
    _initCheck = this;
    ENSURE(properlyInitialized(), "Expected Metronet to be properly initialized!");
}
Metronet::Metronet() {
    _initCheck = this;
    ENSURE(properlyInitialized(), "Expected Metronet to be properly initialized!");
}
bool Metronet::properlyInitialized() const {
    return _initCheck == this;
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
void sleep(const long &durationInSeconds) {
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
    std::multimap<int, Tram*>::iterator iter = fTrams.begin();
    for(int i =0;i<durationInSeconds;i++) {
        sleep(1);
        for(iter = fTrams.begin(); iter != fTrams.end(); iter++){
            moveTram(iter->second->getLijnNr(), iter->second->getVoertuigNr());
        }
    }
}
void Metronet::pushStation(Station* station) {
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    // TODO
}
void Metronet::pushTram(Tram* tram) {
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    fTrams.insert(std::make_pair(tram->getLijnNr(), tram));
}
bool Metronet::tramExists(const int &lijnNr) const {
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    return fTrams.find(lijnNr) != fTrams.end();
}
std::map<std::string, TramType*> Metronet::getTramTypes() const {
    return fTramTypes;
}
void Metronet::setTramTypes(std::map<std::string, TramType *> newTramTypes) {
    fTramTypes = newTramTypes;
}
void Metronet::moveTram(const int &lijnNr, const int &voertuigNr, const int &steps) {
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    REQUIRE(tramExists(lijnNr), "Expected to-be-moved Tram to exist!");
    Tram* tram = getTram(lijnNr, voertuigNr);
    for(int i=0;i<steps;i++) {
        Station *huidigeStation = tram->getHuidigeStation();
        tram->moveNaarVolgendeStation();
        std::cout << "Tram " << lijnNr << " (" << voertuigNr << ") (" << tram->getType()->getNaam() <<
        ") reed van Station " << huidigeStation->getNaam() << " (" << huidigeStation->getType() << ")" <<
        " naar Station " << tram->getHuidigeStation()->getNaam() << " (" <<
        tram->getHuidigeStation()->getType() << ")" << ".\n";
    }
}
Station* Metronet::retrieveStation(const std::string &naam) const {
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    return fStations.find(naam)->second;
}
std::multimap<int, Tram*> Metronet::getTrams() const {
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    return fTrams;
}
void Metronet::setTrams(std::multimap<int, Tram*> &newTrams) {
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    fTrams = newTrams;
}

std::map<std::string, Station *> Metronet::getStations() const {
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    return fStations;
}
void Metronet::setStations(std::map<std::string, Station *> &newStations) {
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    fStations=newStations;
}

Tram* Metronet::getTram(const int &lijnNr, const int &voertuigNr) const{
    if(__isnan(voertuigNr)){
        return fTrams.find(lijnNr)->second;
    } else{
        std::pair <std::multimap<int, Tram*>::const_iterator, std::multimap<int,Tram*>::const_iterator> range = fTrams.equal_range(lijnNr);
        for(std::_Rb_tree_const_iterator<std::pair<const int, Tram *> > i = range.first; i != range.second; i++){
            if(i->second->getVoertuigNr() == voertuigNr){
                return i->second;
            }
        }
        return 0;
    }
}
