//
// Created by gruzi on 12/03/2023.
//

#include "Metronet.h"
#include "../../DesignByContract.h"
#include <fstream>
#include <iostream>

Metronet::Metronet(std::map<int, Station*> &newSporen, std::map<int, Tram*> &newTrams) : fSporen(newSporen),
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
    for(std::map<int, Tram*>::const_iterator iter = fTrams.begin(); iter != fTrams.end(); iter++) {
        delete iter->second;
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
void Metronet::insertAfterStation(const std::string &vorigeNaam, Station *station) {
    REQUIRE(this->properlyInitialized(), "Expected metronet to be properly initialized in insertAfterStation!");
    int spoorNr = station->getSpoorNr();
    Station* currentStation = retrieveStation(spoorNr, vorigeNaam);
    if(currentStation) {
        Station *rightStation = currentStation->getVolgende();

        station->setVorige(currentStation);
        station->setVolgende(rightStation);
        currentStation->setVolgende(station);
        rightStation->setVorige(station);
    }
    else std::cerr << "Cannot insert station " << station->getNaam() << " after station " << vorigeNaam << "!\n";
}

void Metronet::outputFile() const {
    /*1. Maak uitvoerbestand
    2. WHILE Nog stations beschikbaar
    2.1. Schrijf station-gegevens uit naar bestand
    3. WHILE Nog trams beschikbaar
    3.1. Schrijf tram-gegevens uit naar bestand
    4. Sluit uitvoerbestand*/
    REQUIRE(this->properlyInitialized(), "Expected metronet to be properly initialized in outputFile!");
    std::ofstream outputFile;
    outputFile.open("output/output.txt");
    // Write all stations to file
    for(std::map<int,Station*>::const_iterator iteratorIntStation = fSporen.begin(); iteratorIntStation != fSporen.end(); iteratorIntStation++){
        Station* beginStation = iteratorIntStation->second;
        Station* currentStation = iteratorIntStation->second;
        do {
            outputFile << "Station " << currentStation->getNaam() << "\n";
            outputFile << "<- Station " << currentStation->getVorige()->getNaam() << "\n";
            outputFile << "-> Station " << currentStation->getVolgende()->getNaam() << "\n";
            outputFile << "Spoor " << currentStation->getSpoorNr() << "\n\n";
            currentStation = currentStation->getVolgende();
        } while(currentStation != beginStation);
    }

    for(std::map<int, Tram*>::const_iterator iteratorIntTrams = fTrams.begin(); iteratorIntTrams != fTrams.end(); iteratorIntTrams++){
        Tram* current = iteratorIntTrams->second;
        outputFile << "Tram " << current->getLijnNr() << " in Station " << current->getHuidigeStation()->getNaam() << "\n";
    }

    outputFile.close();
}