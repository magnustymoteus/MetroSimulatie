//
// Created by gruzi on 06/03/2023.
//

#include "MetronetImporter.h"

#include <iostream>

#include "DesignByContract.h"

MetronetImporter::MetronetImporter() {
    _initCheck = this;
    ENSURE(properlyInitialized(), "Expected MetronetImporter to be properly initialized in constructor!");
    REQUIRE(this->properlyInitialized(), "Expected MetronetImporter to be properly initialized in getSupportedTags!");
    // Collect all tags from importers
    std::map<std::string, std::vector<std::string> > tagsOfTramImporter = fTramImporter.getSupportedTags();
    std::map<std::string, std::vector<std::string> > tagsOfStationImporter = fStationImporter.getSupportedTags();
    std::map<std::string, std::vector<std::string> > tagsOfTramTypeImporter = fTramTypeImporter.getSupportedTags();
    REQUIRE(!tagsOfStationImporter.empty(), "Expected StationImporter to have at least one supported tag");
    REQUIRE(!tagsOfTramImporter.empty(), "Expected TramImporter to have at least one supported tag");
    REQUIRE(!tagsOfTramTypeImporter.empty(), "Expected TramTypeImporter to have at least one supported tag");
    fSupportedTags.insert(tagsOfTramTypeImporter.begin(), tagsOfTramTypeImporter.end());
    fSupportedTags.insert(tagsOfTramImporter.begin(), tagsOfTramImporter.end());
    fSupportedTags.insert(tagsOfStationImporter.begin(), tagsOfStationImporter.end());
    ENSURE(!fSupportedTags.empty(), "Expected MetronetImporter to have at least one supported tag");
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
void MetronetImporter::parseTrams(TiXmlElement* rootElem, Metronet* &metronet) const {
    REQUIRE(this->properlyInitialized(), "Expected MetronetImporter to be properly initialized in parseTrams!");
    TiXmlElement* currentElem = fTramImporter.getFirstChildTag(rootElem, "TRAM");
    const std::map<std::string, TramType*> tramTypes = fTramTypeImporter.getSupportedTramTypes();
    while(currentElem) {
        Tram* tram = fTramImporter.parse(currentElem);
        TramType* tramType = tramTypes.at(
                getText(fTramImporter.getFirstChildProperty(currentElem, "type")));
        tram->setType(tramType);
        metronet->pushTram(tram);
        Station* beginStation = metronet->retrieveStation(
                getText(fTramImporter.getFirstChildProperty(currentElem, "beginStation")));
        if(beginStation) {
            tram->setBeginStation(beginStation);
            tram->setHuidigeStation(beginStation);
        }
        else std::cerr << "Could not find Station " <<
        getText(fTramImporter.getFirstChildProperty(currentElem, "beginStation"))
        << " for Tram " << tram->getLijnNr() << "!\n";
        currentElem = fTramImporter.getNextSiblingTag(currentElem, "TRAM");
    }
}
/*
 * This function retrieves information about stations from the given XML file to the metro system
 * @param doc The parsed file
 * @param Metronet The given metro network
 * @return nothing (void function)
 */
void MetronetImporter::parseStations(TiXmlElement* rootElem, Metronet* &metronet) const {
    REQUIRE(this->properlyInitialized(), "Expected MetronetImporter to be properly initialized in parseStations!");
    TiXmlElement* currentElem = fStationImporter.getFirstChildTag(rootElem, "STATION");
    std::map<std::string, Station*> stations;
    while(currentElem) {
        std::string naam = getText(fStationImporter.getFirstChildProperty(currentElem, "naam"));
        std::string type = getText(fStationImporter.getFirstChildProperty(currentElem, "type"));
        Station* station = new Station(naam, type);
        stations.insert(std::make_pair(naam, station));
        currentElem = fStationImporter.getNextSiblingTag(currentElem, "STATION");
    }
    metronet->setStations(stations);
    currentElem = fStationImporter.getFirstChildTag(rootElem, "STATION");
    while(currentElem) {
        TiXmlElement* currentSpoorElem = fStationImporter.getFirstChildProperty(currentElem, "SPOOR");
        std::map<int, std::pair<Station*, Station*> > sporen;
        while(currentSpoorElem) {
            int spoorNr;
            std::istringstream(
                    getText(fStationImporter.getFirstChildProperty(
                            currentSpoorElem, "spoorNr"))) >> spoorNr;
            const bool spoorNotFound = sporen.find(spoorNr) == sporen.end();
            if(!spoorNotFound) metronet->setIsConsistent(false);
            CERR_IF_FALSE(spoorNotFound,
                           MetronetInconsistentException("A station has one spoor more than once!"));
                Station *vorige =
                        metronet->retrieveStation(getText(fStationImporter.getFirstChildProperty(
                                currentSpoorElem, "vorige")));
                Station *volgende =
                        metronet->retrieveStation(getText(fStationImporter.getFirstChildProperty(
                                currentSpoorElem, "volgende")));
                sporen.insert(std::make_pair(spoorNr, std::make_pair(vorige, volgende)));
            currentSpoorElem = fStationImporter.getNextSiblingTag(currentSpoorElem, "SPOOR");
        }
        metronet->retrieveStation(getText(fStationImporter.getFirstChildProperty(
                currentElem, "naam")))->setSporen(sporen);
        currentElem = fStationImporter.getNextSiblingTag(currentElem, "STATION");
    }
}
Metronet* MetronetImporter::parse(TiXmlElement* rootElem) const {
    REQUIRE(this->properlyInitialized(), "Expected MetronetImporter to be properly initialized in parseFile!");
    Metronet *metronet = new Metronet();
    metronet->setTramTypes(fTramTypeImporter.getSupportedTramTypes());
    parseStations(rootElem, metronet);
    parseTrams(rootElem, metronet);
    MetronetValidator metronetValidator(metronet);
    metronet->setIsConsistent(metronetValidator.validate());
    return metronet;
}
Metronet* MetronetImporter::parseFile(const std::string &relativeFilePath_str) const {
    REQUIRE(this->properlyInitialized(), "Expected MetronetImporter to be properly initialized in parseFile!");
    const char *relativeFilePath = relativeFilePath_str.c_str();
    TiXmlDocument doc;
    REQUIRE(doc.LoadFile(relativeFilePath), "File expected to be loaded!");
    TiXmlElement* root = doc.RootElement();
    Metronet* metronet = parse(root);
    return metronet;
}