//
// Created by gruzi on 12/03/2023.
//

#include "Metronet.h"
#include "DesignByContract.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Metronet::Metronet(std::map<int, Station*> &newSporen, std::multimap<int, Tram*> &newTrams) : fSporen(newSporen),
fTrams(newTrams)
{
    _initCheck = this;
    ENSURE(properlyInitialized(), "Expected metronet to be properly initialized in constructor!");
}
Metronet::Metronet() {
    _initCheck = this;
    ENSURE(properlyInitialized(), "Expected metronet to be properly initialized in constructor!");
}
bool Metronet::properlyInitialized() const {
    return _initCheck == this;
}

Metronet::~Metronet() {
    REQUIRE(this->properlyInitialized(), "Expected metronet to be properly initialized in destructor!");
    for(std::map<int, Station*>::const_iterator iter = fSporen.begin(); iter!=fSporen.end();iter++) {
        Station* endStation = iter->second->getVorige();
        Station* currentStation = iter->second;
        while(currentStation != endStation) {
            currentStation = currentStation->getVolgende();
            delete currentStation->getVorige();
        }
        delete currentStation;
    }
    for(std::multimap<int, Tram*>::const_iterator iter = fTrams.begin(); iter != fTrams.end(); iter++) {
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
    REQUIRE(this->properlyInitialized(), "Expected metronet to be properly initialized in autoSimulate!");
    std::multimap<int, Tram*>::iterator iter = fTrams.begin();
    for(int i =0;i<durationInSeconds;i++) {
        sleep(1);
        //std::advance(iter, rand() % fTrams.size());
        for(iter = fTrams.begin(); iter != fTrams.end(); iter++){
            moveTram(iter->second->getLijnNr(), iter->second->getVoertuigNr());
        }
    }
}
void Metronet::pushStation(Station* station) {
    REQUIRE(this->properlyInitialized(), "Expected metronet to be properly initialized in pushStation!");
    int spoorNr = station->getSpoorNr();
    std::map<int, Station*>::const_iterator stationFind = fSporen.find(spoorNr);
    if(stationFind == fSporen.end()) {
        fSporen.insert(std::make_pair(spoorNr, station));
        station->setVorige(station);
        station->setVolgende(station);
    }
    else {
        Station* firstStation = stationFind->second;
        Station* lastStation = firstStation->getVorige();

        station->setVolgende(firstStation);
        station->setVorige(lastStation);
        lastStation->setVolgende(station);
        firstStation->setVorige(station);
    }
}
void Metronet::pushTram(Tram* tram) {
    REQUIRE(this->properlyInitialized(), "Expected metronet to be properly initialized in pushTram!");
    fTrams.insert(std::make_pair(tram->getLijnNr(), tram));
}
bool Metronet::spoorExists(const int &spoorNr) const {
    REQUIRE(this->properlyInitialized(), "Expected metronet to be properly initialized in spoorExists!");
    return fSporen.find(spoorNr) != fSporen.end();
}
bool Metronet::tramExists(const int &lijnNr) const {
    REQUIRE(this->properlyInitialized(), "Expected metronet to be properly initialized in tramExists!");
    return fTrams.find(lijnNr) != fTrams.end();
}
void Metronet::moveTram(const int &lijnNr, const int &voertuigNr, const int &steps) {
    REQUIRE(this->properlyInitialized(), "Expected metronet to be properly initialized in moveTram!");
    REQUIRE(tramExists(lijnNr), "Expected to-be-moved tram to exist!");
    REQUIRE(spoorExists(lijnNr), "Expected the spoor of the corresponding to-be-moved tram to exist!");
    Tram* tram = getTram(lijnNr, voertuigNr);
    for(int i=0;i<steps;i++) {
        Station *huidigeStation = tram->getHuidigeStation();
        tram->moveNaarVolgendeStation();
        std::cout << "Tram " << lijnNr << "(" << voertuigNr << ")" << " reed van station " << huidigeStation->getNaam() << " naar station " <<
                  tram->getHuidigeStation()->getNaam() << ".\n";
    }
}
Station* Metronet::retrieveStation(const int &spoorNr, const std::string &naam) const {
    REQUIRE(this->properlyInitialized(), "Expected metronet to be properly initialized in retrieveStation!");
    std::map<int, Station*>::const_iterator stationFind = fSporen.find(spoorNr);
    if(stationFind != fSporen.end()) {
        Station* endStation = stationFind->second->getVorige();
        Station* currentStation = stationFind->second;
        while(currentStation->getNaam() != naam && currentStation != endStation) {
            currentStation = currentStation->getVolgende();
        }
        if(currentStation->getNaam() == naam) return currentStation;
        else std::cerr << "Could not find station " << naam << " in spoorNr " << spoorNr << "!\n";

    }
    else std::cerr << "Cannot find spoorNr " << spoorNr << "!\n";
    return 0;
}
std::multimap<int, Tram*> Metronet::getTrams() const {
    REQUIRE(this->properlyInitialized(), "Expected metronet to be properly initialized in getTrams!");
    return fTrams;
}
void Metronet::setTrams(std::multimap<int, Tram*> &newTrams) {
    REQUIRE(this->properlyInitialized(), "Expected metronet to be properly initialized in setTrams!");
    fTrams = newTrams;
}

std::map<int, Station *> Metronet::getSporen() const {
    REQUIRE(this->properlyInitialized(), "Expected metronet to be properly initialized in getSporen!");
    return fSporen;
}
void Metronet::setSporen(std::map<int, Station *> &newSporen) {
    REQUIRE(this->properlyInitialized(), "Expected metronet to be properly initialized in setSporen!");
    fSporen=newSporen;
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
