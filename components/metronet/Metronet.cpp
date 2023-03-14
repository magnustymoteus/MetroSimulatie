//
// Created by gruzi on 12/03/2023.
//

#include "Metronet.h"
#include <fstream>
#include <list>
#include <algorithm>
Metronet::Metronet(std::map<int, Station*> &newSporen, std::map<int, Tram*> &newTrams) : fSporen(newSporen),
fTrams(newTrams)
{}

void Metronet::outputFile() const {
    /*1. Maak uitvoerbestand
    2. WHILE Nog stations beschikbaar
    2.1. Schrijf station-gegevens uit naar bestand
    3. WHILE Nog trams beschikbaar
    3.1. Schrijf tram-gegevens uit naar bestand
    4. Sluit uitvoerbestand*/
    std::ofstream outputFile;
    outputFile.open("output.txt");
    // Write all stations to file
    for(std::map<int,Station*>::const_iterator iteratorIntStation = fSporen.begin(); iteratorIntStation != fSporen.end(); iteratorIntStation++){
        Station* beginStation = iteratorIntStation->second;
        std::list<Station*> visitedStations;
        for(Station* current = beginStation; std::find(visitedStations.begin(), visitedStations.end(), current) != visitedStations.end(); current = current->getVolgende()){
            outputFile << "Station " << current->getNaam() << "\n";
            outputFile << "<- Station " << current->getVorige()->getNaam() << "\n";
            outputFile << "-> Station " << current->getVolgende()->getNaam() << "\n";
            outputFile << "Spoor " << current->getSpoorNr() << "\n\n";
        }
    }

    for(std::map<int, Tram*>::const_iterator iteratorIntTrams = fTrams.begin(); iteratorIntTrams != fTrams.end(); iteratorIntTrams++){
        Tram* current = iteratorIntTrams->second;
        outputFile << "Tram " << current->getLijnNr() << "in Station " << current->getHuidigeStation()->getNaam() << "\n";
    }

    outputFile.close();
}