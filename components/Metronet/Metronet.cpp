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
    const std::map<std::string, Station*> & stations = getStations();
    for(std::map<std::string, Station*>::const_iterator iter = stations.begin(); iter!=stations.end();iter++) {
        delete iter->second;
    }
    const std::multimap<int, Tram*> & trams = getTrams();
    for(std::multimap<int, Tram*>::const_iterator iter = trams.begin(); iter != trams.end(); iter++) {
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
    std::multimap<int, Tram *> trams = getTrams();
    std::multimap<int, Tram *>::iterator iter = trams.begin();

    //Tram : (stepsUntilDefect, stepsUntilFixed), only stores trams of PCC type
    std::map<Tram*, std::pair<unsigned int, unsigned int> > tramsDefectInfo;
    for (iter = trams.begin(); iter != trams.end(); iter++) {
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
        for (iter = trams.begin(); iter != trams.end(); iter++) {
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
    // Print the rapport
    printRapport();
}
bool Metronet::isTramOnStation(const std::string &stationName, const int &spoorNr) const {
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    const std::map<std::string, Station*> & stations = getStations();
    REQUIRE(stations.find(stationName) != stations.end(), "Expected the station to exist in metronet!");
    REQUIRE(stations.at(stationName)->spoorExists(spoorNr), "Expected the station to have the given spoorNr!");
    const std::multimap<int, Tram*> & trams = getTrams();
    for(std::multimap<int, Tram*>::const_iterator iter = trams.begin(); iter != trams.end(); iter++) {
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
    const std::map<std::string, Station*> &stations = getStations();
    REQUIRE(!stations.empty(), "There are no stations in Metronet!");
    std::map<std::basic_string<char>, Station *> extractedStations = getStations();
    Station* station = extractedStations.at(stationName);
    REQUIRE(station != NULL, "Station with given stationName is not found!");
    station->setSpoor(spoorNr, newSpoor);
}
bool Metronet::tramExists(const int &lijnNr) const {
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    const std::multimap<int, Tram*> & trams = getTrams();
    return trams.find(lijnNr) != trams.end();
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
    const std::map<std::string, Station*> & stations = getStations();
    if(stations.find(naam) == stations.end()) return 0;
    return stations.at(naam);
}
Tram* Metronet::retrieveTram(const int &lijnNr, const int &voertuigNr) const{
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    const std::multimap<int, Tram*> & trams = getTrams();
    std::pair <std::multimap<int, Tram*>::const_iterator, std::multimap<int,Tram*>::const_iterator> range =
            trams.equal_range(lijnNr);
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

void Metronet::printRapport() const{
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    std::set<std::string> stationTypes = getStationTypes();
    std::set<std::string> tramTypes = getTramTypes();
    print("\n######################## Rapport ########################\n\n");
    print("Aantal stations in het metronet: "); print(fStations.size()); print("\n");
    print("Daarvan:\n");
    std::set<std::string>::iterator iter;
    // Iterate through all station types
    for(iter = stationTypes.begin(); iter != stationTypes.end(); ++iter){
        print("\t- " + *iter + ": "); print(getNumberOfStationsWithGivenType(*iter)); print("\n");
        std::set<Station*> stationsWithType = getStationsWithGivenType(*iter);
        for(std::set<Station*>::const_iterator stationIt = stationsWithType.begin();
                                stationIt != stationsWithType.end(); ++stationIt){
            print("\t\t Station " + (*stationIt)->getNaam() + ". ");
            // TODO: some station info
            print("\n");
        }
    }
    print("\nAantal trams in het metronet: "); print(fTrams.size()); print("\n");
    print("Daarvan:\n");
    double totaleKosten = 0;
    // Iterate through all tram types
    for(iter = tramTypes.begin(); iter != tramTypes.end(); ++iter){
        print("\t- " + *iter + ": "); print(getNumberOfTramsWithGivenType(*iter)); print("\n");
        std::set<Tram*> tramsWithType = getTramsWithGivenType(*iter);
        for(std::set<Tram*>::const_iterator tramIt = tramsWithType.begin();
            tramIt != tramsWithType.end(); ++tramIt){
            print("\t\t Totale reparatiekosten voor tram "); print((*tramIt)->getLijnNr()); print(" ("); print((*tramIt)->getVoertuigNr());
            print("): "); print((*tramIt)->getTotaleReparatieKost()); print(" euro.\n");
            totaleKosten += (*tramIt)->getTotaleReparatieKost();
        }
    }
    print("\nTotale reparatiekosten voor alle trams: "); print(totaleKosten); print("\n");
    print("\n#########################################################\n");
}
std::set<std::string> Metronet::getStationTypes() const{
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    std::set<std::string> to_return;
    for(std::map<std::string,Station*>::const_iterator iter = fStations.begin(); iter != fStations.end(); ++iter){
        to_return.insert(iter->second->getType());
    }
    return to_return;
}
std::set<std::string> Metronet::getTramTypes() const{
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    std::set<std::string> to_return;
    for(std::map<int,Tram*>::const_iterator iter = fTrams.begin(); iter != fTrams.end(); ++iter){
        to_return.insert(tramTypeToString(iter->second->getType()));
    }
    return to_return;
}

int Metronet::getNumberOfStationsWithGivenType(const std::string& stationType) const{
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    int numberOfStations = 0;
    for(std::map<std::string, Station*>::const_iterator iter = fStations.begin();
                        iter != fStations.end(); ++iter){
        if(iter->second->getType() == stationType) numberOfStations++;
    }
    return numberOfStations;
}

int Metronet::getNumberOfTramsWithGivenType(const std::string& tramType) const{
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    int numberOfTrams = 0;
    for(std::map<int, Tram*>::const_iterator iter = fTrams.begin();
        iter != fTrams.end(); ++iter){
        if(tramTypeToString(iter->second->getType()) == tramType) numberOfTrams++;
    }
    return numberOfTrams;
}

std::set<Station*> Metronet::getStationsWithGivenType(const std::string& stationType) const{
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    std::set<Station*> stations;
    for(std::map<std::string,Station*>::const_iterator iter = fStations.begin();
                iter != fStations.end(); ++iter){
        if(iter->second->getType() == stationType){
            stations.insert(iter->second);
        }
    }
    return stations;
}

std::set<Tram*> Metronet::getTramsWithGivenType(const std::string& tramType) const{
    REQUIRE(this->properlyInitialized(), "Expected Metronet to be properly initialized!");
    std::set<Tram*> trams;
    for(std::map<int,Tram*>::const_iterator iter = fTrams.begin();
        iter != fTrams.end(); ++iter){
        if(tramTypeToString(iter->second->getType()) == tramType){
            trams.insert(iter->second);
        }
    }
    return trams;
}
