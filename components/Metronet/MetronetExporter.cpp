//
// Created by gruzi on 17/03/2023.
//

#include "MetronetExporter.h"

#include <fstream>
#include <iostream>

#include "DesignByContract.h"

MetronetExporter::MetronetExporter() {
    _initCheck = this;
    ENSURE(properlyInitialized(), "Expected MetronetExporter to be properly initialized in constructor!");
}

bool MetronetExporter::properlyInitialized() const {
    return _initCheck == this;
}

void MetronetExporter::output(const Metronet* const &metronet, const std::string &pathFile) {
    REQUIRE(metronet->getIsConsistent(), "Expected metronet to be consistent before exporting!");
    std::ofstream outputFile;
    outputFile.open(pathFile.c_str());
    std::map<std::string, Station*> stations = metronet->getStations();
    std::multimap<int, Tram*> fTrams = metronet->getTrams();
    outputFile << "--== STATIONS ==--" << "\n";
    for(std::map<std::string,Station*>::const_iterator iteratorIntStation = stations.begin(); iteratorIntStation != stations.end();
    iteratorIntStation++){
        // Save begin Station for further comparison
        Station* currentStation = iteratorIntStation->second;
        // Iterate over all stations in the Metronet
        outputFile << "= Station " << currentStation->getNaam() << " =\n";
        std::map<int, std::pair<Station*, Station*> > sporen = currentStation->getSporen();
        for(std::map<int, std::pair<Station*, Station*> >::const_iterator iterSpoor = sporen.begin();
        iterSpoor != sporen.end(); iterSpoor++) {
            outputFile << "* Spoor " << iterSpoor->first << ":\n";
            outputFile << "\t-> Station " << iterSpoor->second.second->getNaam() << "\n";
            outputFile << "\t<- Station " << iterSpoor->second.first->getNaam() << "\n";
            outputFile << "\n";
        }
    };
    outputFile << "--== TRAMS ==--" << "\n";
    // Iterate over all trams in the Metronet
    for(std::multimap<int, Tram*>::const_iterator iteratorIntTrams = fTrams.begin(); iteratorIntTrams != fTrams.end(); iteratorIntTrams++){
        Tram* current = iteratorIntTrams->second;
        outputFile << "Tram " << current->getLijnNr() << " nr " << current->getVoertuigNr() << "\n";
        outputFile << "\ttype: " << tramTypeToString(current->getType()) << "\n";
        outputFile << "\tsnelheid: " << current->getSnelheid() << "\n";
        outputFile << "\thuidig station: " << current->getHuidigeStation()->getNaam() << "\n";
        if(current->getAantalDefecten() && current->getReparatieTijd()) {
            outputFile << "\taantal defecten: " << current->getAantalDefecten() << "\n";
            outputFile << "\treparatie tijd: " << current->getReparatieTijd() << "\n";
            outputFile << "\treparatiekosten: " << current->getReparatieKost() << " euro\n";
            outputFile << "\ttotale reparatiekosten: " << current->getTotaleReparatieKost() << " euro\n";
        }
    }
    // Close file
    outputFile.close();
}
void MetronetExporter::outputAdvanced(const Metronet *const &metronet, const std::string &pathFile) {
    REQUIRE(metronet->getIsConsistent(), "Expected metronet to be consistent before exporting!");
    std::ofstream outputFile;
    outputFile.open(pathFile.c_str());
    std::multimap<int, Tram*> trams = metronet->getTrams();
    std::map<int, bool> visitedSpoor;
    for(std::multimap<int, Tram*>::const_iterator tramIter = trams.begin(); tramIter != trams.end(); tramIter++){
        if(visitedSpoor.find(tramIter->second->getLijnNr()) == visitedSpoor.end()) {
            visitedSpoor.insert(std::make_pair(tramIter->second->getLijnNr(), true));
        }
        else if(visitedSpoor.at(tramIter->second->getLijnNr())) continue;
        Station* currentStation = tramIter->second->getBeginStation();
        Station* beginStation = currentStation;
        std::string stationsStr, tramsStr;
        do {
            stationsStr+="="+currentStation->getNaam()+"=";
            if(metronet->isTramOnStation(currentStation->getNaam(), tramIter->second->getLijnNr()))
                tramsStr += " T ";
            else tramsStr += "   ";
            currentStation = currentStation->getVolgende(tramIter->first);
        } while(currentStation != beginStation);
        outputFile << stationsStr << "\n" << tramsStr << "\n";
    }
}
