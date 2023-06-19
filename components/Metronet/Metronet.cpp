//
// Created by gruzi on 12/03/2023.
//

#include "Metronet.h"
#include "MetronetExporter.h"

#include <iostream>
#include <ctime>
#include "utils.h"

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
void Metronet::autoSimulate(const unsigned int &steps) {
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    REQUIRE(steps>0, "Expected steps > 0");
    REQUIRE(isConsistent, "Expected metronet to be consistent in a simulation!");
    std::multimap<int, Tram *>::iterator iter = fTrams.begin();

    //Tram : (stepsUntilDefect, stepsUntilFixed), only stores trams of PCC type
    std::map<Tram*, std::pair<unsigned int, unsigned int> > tramsDefectInfo;
    for (iter = fTrams.begin(); iter != fTrams.end(); iter++) {
        if(iter->second->getType() == TramType_PCC)
            tramsDefectInfo.insert(std::make_pair(iter->second, std::make_pair(
                iter->second->getAantalDefecten(),iter->second->getReparatieTijd())));
    }
    for (unsigned int i = 0; i < steps; i++) {
        // Fill alreadyMoved map
        std::map<Tram*, bool> alreadyMoved;
        for(iter = fTrams.begin(); iter != fTrams.end(); iter++){
            alreadyMoved.insert(std::make_pair(iter->second, false));
        }
        wait(1);
        print("Stap "); print(i + 1); print(":\n");
        for (iter = fTrams.begin(); iter != fTrams.end(); iter++) {
            print("\t");
            std::string stationName = iter->second->getVolgendeStation()->getNaam();
            int lijnNr = iter->second->getLijnNr();
            if(!isTramOnStation(stationName, lijnNr) || (getTramOnStation(stationName, lijnNr) != 0
                    && !alreadyMoved.at(getTramOnStation(stationName, lijnNr)))) {
                if (tramsDefectInfo.find(iter->second) != tramsDefectInfo.end()) {
                    const unsigned int stepsUntilDefect = tramsDefectInfo.at(iter->second).first;
                    const unsigned int stepsUntilFixed = tramsDefectInfo.at(iter->second).second;
                    if (stepsUntilDefect) tramsDefectInfo.at(iter->second).first--;
                    if (!tramsDefectInfo.at(iter->second).first && stepsUntilFixed)
                        tramsDefectInfo.at(iter->second).second--;
                    if (!stepsUntilDefect && !stepsUntilFixed) {
                        tramsDefectInfo.at(iter->second).first = iter->second->getAantalDefecten();
                        tramsDefectInfo.at(iter->second).second = iter->second->getReparatieTijd();
                    }
                    moveTram(iter->second, stepsUntilDefect > 0);
                } else moveTram(iter->second);
            }else{
                print("Tram "); print(iter->second->getLijnNr()); print(" (");
                print(iter->second->getVoertuigNr()); print(") (");
                print(tramTypeToString(iter->second->getType())); print(") wacht tot volgende station vrij is");
            }
            alreadyMoved[iter->second] = true;
        }
    }
}
bool Metronet::isTramOnStation(const std::string &stationName, const int &spoorNr) const {
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    REQUIRE(fStations.find(stationName) != fStations.end(), "Expected the station to exist in metronet!");
    REQUIRE(fStations.at(stationName)->spoorExists(spoorNr), "Expected the station to have the given spoorNr!");
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
void Metronet::pushSpoor(const std::string& stationName, const int &spoorNr, const std::pair<Station*, Station*> &newSpoor){
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    REQUIRE(!this->fStations.empty(), "There are no stations in Metronet!");
    std::map<std::basic_string<char>, Station *> extractedStations = getStations();
    Station* station = extractedStations.at(stationName);
    REQUIRE(station != NULL, "Station with given stationName is not found!");
    station->setSpoor(spoorNr, newSpoor);
}
bool Metronet::tramExists(const int &lijnNr) const {
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    return fTrams.find(lijnNr) != fTrams.end();
}
bool Metronet::spoorExists(const int &lijnNr) const {
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    std::map<std::string, Station*> allStations = getStations();
    for(std::map<std::string, Station*>::iterator stationIterator = allStations.begin();
                                                                            stationIterator != allStations.end(); stationIterator++){
        if(stationIterator->second->spoorExists(lijnNr)){
            return true;
        }
    }
    return false;
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
void Metronet::moveTram(Tram* &tram, const unsigned int &steps) const {
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    const int lijnNr = tram->getLijnNr();
    const int voertuigNr = tram->getVoertuigNr();
    if(steps) {
        tram->setDefect(false);
        Station *huidigeStation = tram->getHuidigeStation();
        unsigned int skippedStations = tram->move(steps);
        print("Tram "); print(lijnNr); print(" ("); print(voertuigNr); print(") ("); print(tramTypeToString(tram->getType()));
                  print(") reed van Station "); print(huidigeStation->getNaam()); print(" (");
                  print(huidigeStation->getType()); print(")"); print(" naar Station ");
                  print(tram->getHuidigeStation()->getNaam()); print(" (");
                  print(tram->getHuidigeStation()->getType()); print(")"); print(".\n");

        if (skippedStations) {
            print("\t\t"); print(skippedStations); print(" halte(s) genegeerd omdat een ");
            print(tramTypeToString(tram->getType())); print(" daar niet mag stoppen.\n");
        }
        }
    else {
        tram->setDefect(true);
        print("Tram "); print(lijnNr); print(" ("); print(voertuigNr); print(") (");
        print(tramTypeToString(tram->getType())); print(") is defect en wordt gerepareerd.\n");
        tram->increaseTotaleReparatieKost();
        print("\t\tTotale reparatiekosten voor de tram: "); print(tram->getTotaleReparatieKost()); print(" euro.\n");
    }
}
Station* Metronet::retrieveStation(const std::string &naam) const {
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    if(fStations.find(naam) == fStations.end()) return 0;
    return fStations.at(naam);
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
Tram* Metronet::getTramOnStation(const std::string &stationName, const int &spoorNr) const {
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    REQUIRE(fStations.find(stationName) != fStations.end(), "Expected the station to exist in metronet!");
    REQUIRE(fStations.at(stationName)->spoorExists(spoorNr), "Expected the station to have the given spoorNr!");
    for(std::multimap<int, Tram*>::const_iterator iter = fTrams.begin(); iter != fTrams.end(); iter++) {
        Station* huidigeStation = iter->second->getHuidigeStation();
        if(iter->second->getLijnNr() == spoorNr && huidigeStation->getNaam() == stationName) return iter->second;
    }
    return 0;
}

