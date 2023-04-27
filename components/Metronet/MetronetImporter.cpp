//
// Created by gruzi on 06/03/2023.
//

#include "MetronetImporter.h"

#include <iostream>

#include "DesignByContract.h"

MetronetImporter::MetronetImporter() {
    _initCheck = this;
    ENSURE(properlyInitialized(), "Expected MetronetImporter to be properly initialized in constructor!");
}

bool MetronetImporter::properlyInitialized() const {
    return _initCheck == this;
}
/*
 * This function retrieves information about trams from the given XML file to the metro system
 * @param doc The parsed file
 * @param Metronet The given metro network
 * @return nothing (void function)
 */
void MetronetImporter::parseTrams(TiXmlElement* rootElem, Metronet &metronet) const {
    REQUIRE(this->properlyInitialized(), "Expected MetronetImporter to be properly initialized in parseTrams!");
    TiXmlElement* currentElem = rootElem->FirstChildElement("TRAM");
    const std::map<std::string, TramType*> tramTypes = fTramTypeImporter.getSupportedTramTypes();
    while(currentElem) {
        Tram* tram = fTramImporter.parse(currentElem);
        TramType* tramType = tramTypes.at(currentElem->FirstChildElement("type")->GetText());
        tram->setType(tramType);
        metronet.pushTram(tram);
        Station* beginStation = metronet.retrieveStation(
                currentElem->FirstChildElement("beginStation")->GetText());
        if(beginStation) {
            tram->setBeginStation(beginStation);
            tram->setHuidigeStation(beginStation);
        }
        else std::cerr << "Could not find Station " << currentElem->FirstChildElement("beginStation")->GetText()
        << " for Tram " << tram->getLijnNr() << "!\n";
        currentElem = currentElem->NextSiblingElement("TRAM");
    }
}
/*
 * This function retrieves information about stations from the given XML file to the metro system
 * @param doc The parsed file
 * @param Metronet The given metro network
 * @return nothing (void function)
 */
void MetronetImporter::parseStations(TiXmlElement* rootElem, Metronet &metronet) const {
    REQUIRE(this->properlyInitialized(), "Expected MetronetImporter to be properly initialized in parseStations!");
    TiXmlElement* currentElem = rootElem->FirstChildElement("STATION");
    std::map<std::string, Station*> stations;
    while(currentElem) {
        std::string naam = currentElem->FirstChildElement("naam")->GetText();
        std::string type = currentElem->FirstChildElement("type")->GetText();
        Station* station = new Station(naam, type);
        stations.insert(std::make_pair(naam, station));
        currentElem = currentElem->NextSiblingElement("STATION");
    }
    metronet.setStations(stations);
    currentElem = rootElem->FirstChildElement("STATION");
    while(currentElem) {
        TiXmlElement* currentSpoorElem = currentElem->FirstChildElement("SPOOR");
        std::map<int, std::pair<Station*, Station*> > sporen;
        while(currentSpoorElem) {
            int spoorNr;
            std::istringstream(currentSpoorElem->FirstChildElement("spoorNr")->GetText()) >> spoorNr;
            Station* vorige =
                    metronet.retrieveStation(currentSpoorElem->FirstChildElement("vorige")->GetText());
            Station* volgende =
                    metronet.retrieveStation(currentSpoorElem->FirstChildElement("volgende")->GetText());
            sporen.insert(std::make_pair(spoorNr, std::make_pair(vorige, volgende)));
            currentSpoorElem = currentSpoorElem->NextSiblingElement("SPOOR");
        }
        metronet.retrieveStation(currentElem->FirstChildElement("naam")->GetText())->setSporen(
                sporen);
        currentElem = currentElem->NextSiblingElement("STATION");
    }
}
/*
 * This function retrieves information from the given XML file to the metro system
 * @param relativeFilePath_str The relative path to the parsed file
 * @return The resulted metro network
 */
Metronet* MetronetImporter::parseFile(const std::string &relativeFilePath_str) {
    REQUIRE(this->properlyInitialized(), "Expected MetronetImporter to be properly initialized in parseFile!");
    const char *relativeFilePath = relativeFilePath_str.c_str();
    TiXmlDocument doc;
    REQUIRE(doc.LoadFile(relativeFilePath), "File expected to be loaded!");
    TiXmlElement* root = doc.RootElement();
    Metronet *metronet = new Metronet();
    metronet->setTramTypes(fTramTypeImporter.getSupportedTramTypes());
    parseStations(root, *metronet);
    parseTrams(root, *metronet);
    MetronetValidator metronetValidator(metronet);
    metronetValidator.validate();
    return metronet;
}