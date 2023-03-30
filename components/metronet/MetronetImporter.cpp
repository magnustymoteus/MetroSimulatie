//
// Created by gruzi on 06/03/2023.
//

#include "MetronetImporter.h"
#include <iostream>
#include <sstream>
#include "DesignByContract.h"

const std::string defaultConfigPath = "components/metronet/config.xml";

MetronetImporter::MetronetImporter() {
    _initCheck = this;
    configPath = defaultConfigPath;
    loadSupportedTags();
    TiXmlDocument doc;
    ENSURE(properlyInitialized(), "Expected MetronetImporter to be properly initialized in constructor!");
    ENSURE(doc.LoadFile(configPath.c_str()), "Expected default configPath to load!");
}

bool MetronetImporter::properlyInitialized() const {
    return _initCheck == this;
}

std::string MetronetImporter::getConfigPath() const {
    REQUIRE(this->properlyInitialized(), "Expected MetronetImporter to be properly initialized in getConfigPath!");
    return configPath;
}
void MetronetImporter::setConfigPath(const std::string &configFilePath) {
    REQUIRE(this->properlyInitialized(), "Expected MetronetImporter to be properly initialized in setConfigPath!");
    configPath = configFilePath;
    loadSupportedTags();
}

std::map<std::string, std::vector<std::string> > MetronetImporter::getSupportedTags() const {
    REQUIRE(this->properlyInitialized(), "Expected MetronetImporter to be properly initialized in getSupportedTags!");
    return fSupportedTags;
}
/*
 * This function parses config.xml file to get all supported tags
 * All supported tags are saved to fSupportedTags (protected variable of MetronetImporter class)
 */
void MetronetImporter::loadSupportedTags() {
    REQUIRE(this->properlyInitialized(), "Expected MetronetImporter to be properly initialized in loadSupportedTags!");
    TiXmlDocument doc;
    REQUIRE(doc.LoadFile(configPath.c_str()), "Config file expected to be loaded!");
    fSupportedTags.clear();
    TiXmlElement* currentElem = doc.FirstChildElement()->FirstChildElement();
    while(currentElem) {
        TiXmlElement* currentSupportedTag = currentElem->FirstChildElement();
        std::string currentSupportedTagName = currentSupportedTag->GetText();
        std::vector<std::string> supportedProperties;
        TiXmlElement* currentProperty =
                currentSupportedTag->NextSiblingElement("properties")->FirstChildElement("property");
            while(currentProperty) {
                supportedProperties.push_back(currentProperty->GetText());
                currentProperty = currentProperty->NextSiblingElement();
            }
            fSupportedTags.insert(std::make_pair(currentSupportedTagName, supportedProperties));
        currentElem = currentElem->NextSiblingElement();
    }
}

bool MetronetImporter::isTagSupported(const std::string &tagName) const {
    REQUIRE(this->properlyInitialized(), "Expected MetronetImporter to be properly initialized in isTagSupported!");
    return fSupportedTags.find(tagName) != fSupportedTags.end();
}
bool MetronetImporter::isPropertySupported(const std::string &tagName, const std::string &propertyName) const {
    REQUIRE(isTagSupported(tagName), "Tag name expected to be supported!");
    REQUIRE(this->properlyInitialized(), "Expected MetronetImporter to be properly initialized in isPropertySupported!");
    const std::vector<std::string> &properties = fSupportedTags.at(tagName);
    for(long unsigned int i=0;i<properties.size();i++) {
        if(properties[i] == propertyName) return true;
    }
    return false;
}
Station* MetronetImporter::parseStation(TiXmlElement* stationElem) const {
    const std::string stationStr = "STATION";
    REQUIRE(this->properlyInitialized(), "Expected MetronetImporter to be properly initialized in parseStation!");
    REQUIRE(stationElem->Value() == stationStr, "Expected stationElem to be station tag!");
    TiXmlElement* currentElem = stationElem->FirstChildElement();
    Station* station = new Station();
    while(currentElem) {
        std::string currentPropertyName = currentElem->Value();
        if(isPropertySupported(stationElem->Value(), currentPropertyName)) {
            if(currentPropertyName == "naam") station->setNaam(currentElem->GetText());
            else if(currentPropertyName == "spoorNr"){
                int spoorNr;
                std::istringstream(currentElem->GetText()) >> spoorNr;
                station->setSpoorNr(spoorNr);
            }
            else if(currentPropertyName == "type"){
                station->setType(currentElem->GetText());
            }
        }
        else std::cerr << "Property not supported for tag " << stationElem->Value() << ": " << currentElem->Value()
                       << "\n";
        currentElem = currentElem->NextSiblingElement();
    }
    ENSURE(station->getNaam().c_str(), "Station expected to have a name!");
    ENSURE(station->getSpoorNr(), "Station expected to have spoorNr!");
    ENSURE(station->getType().c_str(), "Station expected to have type!");
    return station;
}
Tram* MetronetImporter::parseTram(TiXmlElement *tramElem) const {
    //TODO: ensure tram to have voertuigNr?
    const std::string tramStr = "TRAM";
    REQUIRE(this->properlyInitialized(), "Expected MetronetImporter to be properly initialized in parseTram!");
    REQUIRE(tramElem->Value() == tramStr, "Expected tramElem to be tram tag!");
    TiXmlElement* currentElem = tramElem->FirstChildElement();
    Tram* tram = new Tram();
    while(currentElem) {
        std::string currentPropertyName = currentElem->Value();
        if(isPropertySupported(tramElem->Value(), currentPropertyName)) {
            int currentPropertyValue;
            std::istringstream(currentElem->GetText()) >> currentPropertyValue;
            if(currentPropertyName == "lijnNr") tram->setLijnNr(currentPropertyValue);
            else if(currentPropertyName == "type") tram->setType(currentElem->GetText());
            else if(currentPropertyName == "voertuigNr") tram->setVoertuigNr(currentPropertyValue);
        }
        else std::cerr << "Property not supported for tag " << tramElem->Value() << ": " << currentElem->Value()
                       << "\n";
        currentElem = currentElem->NextSiblingElement();
    }
    ENSURE(tram->getLijnNr(), "Tram expected to have lijnNr!");
    ENSURE(tram->getType().c_str(), "Tram expected to have type!");
    return tram;
}


TiXmlElement* findStationTag(TiXmlDocument &doc, const std::string &stationName, const std::string &spoorNr) {
    TiXmlElement* currentElem = doc.FirstChildElement("STATION");
    const std::string stationTag = "STATION";
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
 * @param metronet The given metro network
 * @return nothing (void function)
 */
void MetronetImporter::parseTrams(TiXmlDocument &doc, Metronet &metronet) const {
    REQUIRE(this->properlyInitialized(), "Expected MetronetImporter to be properly initialized in parseTrams!");
    TiXmlElement* currentElem = doc.FirstChildElement("TRAM");
    while(currentElem) {
        Tram* tram = parseTram(currentElem);
        metronet.pushTram(tram);
        Station* beginStation = metronet.retrieveStation(tram->getLijnNr(),
                                         currentElem->FirstChildElement("beginStation")->GetText());
        if(beginStation) {
            tram->setBeginStation(beginStation);
            tram->setHuidigeStation(beginStation);
        }
        else std::cerr << "Could not find station " << currentElem->FirstChildElement("beginStation")->GetText()
        << " for tram " << tram->getLijnNr() << "!\n";
        currentElem = currentElem->NextSiblingElement("TRAM");
    }
}
/*
 * This function retrieves information about stations from the given XML file to the metro system
 * @param doc The parsed file
 * @param metronet The given metro network
 * @return nothing (void function)
 */
void MetronetImporter::parseStations(TiXmlDocument &doc, Metronet &metronet) const {
    REQUIRE(this->properlyInitialized(), "Expected MetronetImporter to be properly initialized in parseStations!");
    TiXmlElement* currentElem = doc.FirstChildElement("STATION");
    while(currentElem) {
        TiXmlElement* nextStationElem = currentElem;
        const std::string firstElemName = currentElem->FirstChildElement("naam")->GetText();
        while(nextStationElem) {
            Station* nextStation = parseStation(nextStationElem);
            metronet.pushStation(nextStation);
            std::string volgende = nextStationElem->FirstChildElement("volgende")->GetText();
            std::string spoorNr = nextStationElem->FirstChildElement("spoorNr")->GetText();
            doc.RemoveChild(nextStationElem);
            nextStationElem = findStationTag(doc, volgende, spoorNr);
            if(!nextStationElem && volgende != firstElemName)
                std::cerr << "Could not find station " << volgende << "!\n";
        }
        currentElem = doc.FirstChildElement("STATION");
    }
}
/*
 * This function retrieves information from the given XML file to the metro system
 * @param relativeFilePath_str The relative path to the parsed file
 * @return The resulted metro network
 */
Metronet MetronetImporter::parseFile(const std::string &relativeFilePath_str) {
    REQUIRE(this->properlyInitialized(), "Expected MetronetImporter to be properly initialized in parseFile!");
    const char *relativeFilePath = relativeFilePath_str.c_str();
    TiXmlDocument doc;
    REQUIRE(doc.LoadFile(relativeFilePath), "File expected to be loaded!");
    Metronet metronet;
    parseStations(doc, metronet);
    parseTrams(doc, metronet);
    MetronetValidator::consistencyCheck(metronet);
    return metronet;
}
