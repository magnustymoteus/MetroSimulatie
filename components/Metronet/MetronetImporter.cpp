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

TiXmlElement* findStationTag(TiXmlDocument &doc, const std::string &stationName, const std::string &spoorNr) {
    TiXmlElement* currentElem = doc.FirstChildElement("STATION");
    bool found = false;
    while(currentElem)
    {
        bool nameEquality = currentElem->FirstChildElement("naam")->GetText() == stationName;
        bool spoorNrEquality = currentElem->FirstChildElement("spoorNr")->GetText() == spoorNr;
        if(nameEquality && spoorNrEquality) {
            found = true;
            break;
        }
        currentElem = currentElem->NextSiblingElement("STATION");
    }
    if(found) return currentElem;
    return 0;

}
/*
 * This function retrieves information about trams from the given XML file to the metro system
 * @param doc The parsed file
 * @param Metronet The given metro network
 * @return nothing (void function)
 */
void MetronetImporter::parseTrams(TiXmlDocument &doc, Metronet &metronet) const {
    REQUIRE(this->properlyInitialized(), "Expected MetronetImporter to be properly initialized in parseTrams!");
    TiXmlElement* currentElem = doc.FirstChildElement("TRAM");
    const std::map<std::string, TramType*> tramTypes = fTramTypeImporter.getSupportedTramTypes();
    while(currentElem) {
        Tram* tram = fTramImporter.parse(currentElem);
        TramType* tramType = tramTypes.at(currentElem->FirstChildElement("type")->GetText());
        tram->setType(tramType);
        metronet.pushTram(tram);
        Station* beginStation = metronet.retrieveStation(tram->getLijnNr(),
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
void MetronetImporter::parseStations(TiXmlDocument &doc, Metronet &metronet) const {
    REQUIRE(this->properlyInitialized(), "Expected MetronetImporter to be properly initialized in parseStations!");
    TiXmlElement* currentElem = doc.FirstChildElement("STATION");
    while(currentElem) {
        TiXmlElement* nextStationElem = currentElem;
        const std::string firstElemName = currentElem->FirstChildElement("naam")->GetText();
        while(nextStationElem) {
            Station* nextStation = fStationImporter.parse(nextStationElem);
            metronet.pushStation(nextStation);
            std::string volgende = nextStationElem->FirstChildElement("volgende")->GetText();
            std::string spoorNr = nextStationElem->FirstChildElement("spoorNr")->GetText();
            doc.RemoveChild(nextStationElem);
            nextStationElem = findStationTag(doc, volgende, spoorNr);
            if(!nextStationElem && volgende != firstElemName)
                std::cerr << "Could not find Station " << volgende << "!\n";
        }
        currentElem = doc.FirstChildElement("STATION");
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
    Metronet *metronet = new Metronet();
    metronet->setTramTypes(fTramTypeImporter.getSupportedTramTypes());
    parseStations(doc, *metronet);
    parseTrams(doc, *metronet);
    MetronetValidator metronetValidator(metronet);
    metronetValidator.validate();
    return metronet;
}