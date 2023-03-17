//
// Created by gruzi on 17/03/2023.
//

#include "MetronetExporter.h"
#include "DesignByContract.h"
#include <fstream>

MetronetExporter::MetronetExporter() {
    _initCheck = this;
    ENSURE(properlyInitialized(), "Expected MetronetExporter to be properly initialized in constructor!");
}

bool MetronetExporter::properlyInitialized() const {
    return _initCheck == this;
}

void MetronetExporter::outputMetronet(const Metronet &metronet) {
    /*1. Maak uitvoerbestand
   2. WHILE Nog stations beschikbaar
   2.1. Schrijf station-gegevens uit naar bestand
   3. WHILE Nog trams beschikbaar
   3.1. Schrijf tram-gegevens uit naar bestand
   4. Sluit uitvoerbestand*/
    std::ofstream outputFile;
    outputFile.open("output/output.txt");
    // Write all stations to file
    std::map<int, Station*> fSporen = metronet.getSporen();
    std::map<int, Tram*> fTrams = metronet.getTrams();
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