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

void MetronetExporter::outputMetronet(const Metronet &metronet, const std::string &pathFile) {
    /*This function exports metronet information to output.txt file
     * @param metronet The metronetwork to save in txt-file
     * @param pathFile The relative path of the output file
     * @return nothing (void functcion) */
    std::ofstream outputFile;
    outputFile.open(pathFile.c_str());
    // Write all stations to file
    std::map<int, Station*> fSporen = metronet.getSporen();
    std::multimap<int, Tram*> fTrams = metronet.getTrams();
    for(std::multimap<int,Station*>::const_iterator iteratorIntStation = fSporen.begin(); iteratorIntStation != fSporen.end(); iteratorIntStation++){
        // Save begin station for further comparison
        Station* beginStation = iteratorIntStation->second;
        Station* currentStation = iteratorIntStation->second;
        outputFile << "--== STATIONS ==--" << "\n";
        // Iterate over all stations in the metronet
        do {
            outputFile << "Station " << currentStation->getNaam() << "\n";
            outputFile << "<- Station " << currentStation->getVorige()->getNaam() << "\n";
            outputFile << "-> Station " << currentStation->getVolgende()->getNaam() << "\n";
            outputFile << "Spoor " << currentStation->getSpoorNr() << "\n\n";
            currentStation = currentStation->getVolgende();
        } while(currentStation != beginStation);
    }
    outputFile << "--== TRAMS ==--" << "\n";
    // Iterate over all trams in the metronet
    for(std::multimap<int, Tram*>::const_iterator iteratorIntTrams = fTrams.begin(); iteratorIntTrams != fTrams.end(); iteratorIntTrams++){
        Tram* current = iteratorIntTrams->second;
        outputFile << "Tram " << current->getLijnNr() << " in Station " << current->getHuidigeStation()->getNaam() << "\n";
    }
    // Close file
    outputFile.close();
}