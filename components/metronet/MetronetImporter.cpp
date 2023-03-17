//
// Created by gruzi on 06/03/2023.
//

#include "MetronetImporter.h"
#include <iostream>
#include <sstream>
#include "DesignByContract.h"

/*
 * Onherkenbaar element: unsupported tag
 * Ongeldige informatie: unsupported property
 */

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
        }
        else std::cerr << "Property not supported for tag " << stationElem->Value() << ": " << currentElem->Value()
                       << "\n";
        currentElem = currentElem->NextSiblingElement();
    }
    ENSURE(station->getNaam().c_str(), "Station expected to have a name!");
    ENSURE(station->getSpoorNr(), "Station expected to have spoorNr!");
    return station;
}
Tram* MetronetImporter::parseTram(TiXmlElement *tramElem) const {
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
            else if(currentPropertyName == "snelheid") tram->setSnelheid(currentPropertyValue);
        }
        else std::cerr << "Property not supported for tag " << tramElem->Value() << ": " << currentElem->Value()
                       << "\n";
        currentElem = currentElem->NextSiblingElement();
    }
    ENSURE(tram->getLijnNr(), "Tram expected to have lijnNr!");
    ENSURE(tram->getSnelheid(), "Tram expected to have snelheid!");
    return tram;
}


Metronet MetronetImporter::parseFile(const std::string &relativeFilePath_str) {
    REQUIRE(this->properlyInitialized(), "Expected MetronetImporter to be properly initialized in parseFile!");
    const char *relativeFilePath = relativeFilePath_str.c_str();
    TiXmlDocument doc;
    REQUIRE(doc.LoadFile(relativeFilePath), "File expected to be loaded!");
    Metronet metronet;
    TiXmlElement *currentElem = doc.FirstChildElement();
    while (currentElem) {
        std::string name = currentElem->Value();
        if (isTagSupported(name)) {
            if (name == "STATION") {
                Station* station = parseStation(currentElem);
                if(metronet.spoorExists(station->getSpoorNr())) {
                    std::string vorigeStationNaam = currentElem->FirstChildElement("vorige")->GetText();
                    metronet.insertAfterStation(vorigeStationNaam,station);
                }
                else metronet.pushStation(station);
            } else if (name == "TRAM") {
                Tram* tram = parseTram(currentElem);
                std::string beginStationNaam = currentElem->FirstChildElement("beginStation")->GetText();
                Station* beginStation = metronet.retrieveStation(tram->getLijnNr(), beginStationNaam);
                if(beginStation) {
                    tram->setBeginStation(beginStation);
                    tram->setHuidigeStation(beginStation);
                    metronet.pushTram(tram);
                }
                else std::cerr << "Could not find begin station " << beginStationNaam << " for tram "
                << tram->getLijnNr();
            }
        } else std::cerr << "Tag not supported: " << name << "\n";
        currentElem = currentElem->NextSiblingElement();
    }
    MetronetValidator::consistencyCheck(metronet);
    return metronet;
}
