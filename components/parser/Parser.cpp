//
// Created by gruzi on 06/03/2023.
//

#include "Parser.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "../../DesignByContract.h"

/*
 * Onherkenbaar element: unsupported tag
 * Ongeldige informatie: unsupported property
 */

std::string CONFIGPATH = "components/parser/config.xml";

Parser::Parser() {
    setSupportedTags();
}
void Parser::setSupportedTags() {
    TiXmlDocument doc;
    REQUIRE(doc.LoadFile(CONFIGPATH.c_str()), "Config file expected to be loaded!");
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

bool Parser::isTagSupported(const std::string &tagName) const {
    return fSupportedTags.find(tagName) != fSupportedTags.end();
}
bool Parser::isPropertySupported(const std::string &tagName, const std::string &propertyName) const {
    REQUIRE(isTagSupported(tagName), "Tag name expected to be supported!");
    const std::vector<std::string> &properties = fSupportedTags.at(tagName);
    for(long unsigned int i=0;i<properties.size();i++) {
        if(properties[i] == propertyName) return true;
    }
    return false;
}
std::pair<std::string,std::pair<Station*, std::pair<std::string, std::string> > >
        Parser::parseStation(TiXmlElement* stationElem) const {
    TiXmlElement* currentProperty = stationElem->FirstChildElement();
    Station* station = new Station();
    std::pair<std::string, std::string> vorige_volgende_station;
    while(currentProperty) {
        std::string currentPropertyName = currentProperty->Value();
        if(isPropertySupported(stationElem->Value(), currentPropertyName)) {
            std::string currentPropertyValue = currentProperty->GetText();
            if(currentPropertyName == "naam") station->setNaam(currentPropertyValue);
            else if(currentPropertyName == "spoorNr"){
                int spoorNr;
                std::istringstream(currentPropertyValue) >> spoorNr;
                station->setSpoorNr(spoorNr);
            }
            else if(currentPropertyName == "vorige") vorige_volgende_station.first = currentPropertyValue;
            else if(currentPropertyName == "volgende") vorige_volgende_station.second = currentPropertyValue;
        }
        else std::cerr << "Property of station not supported: " << currentPropertyName << "\n";
        currentProperty = currentProperty->NextSiblingElement();
    }
    return std::make_pair(station->getNaam(), std::make_pair(station, vorige_volgende_station));
}
std::pair<Tram*, std::string> Parser::parseTram(TiXmlElement *tramElem) const {
    TiXmlElement *currentProperty = tramElem->FirstChildElement();
    Tram *tram = new Tram();
    std::string beginStation;
    while (currentProperty) {
        std::string currentPropertyName = currentProperty->Value();
        if (isPropertySupported(tramElem->Value(), currentPropertyName)) {
            int currentPropertyValue;
            std::istringstream(currentProperty->GetText()) >> currentPropertyValue;
            if(currentPropertyName == "lijnNr") tram->setLijnNr(currentPropertyValue);
            else if(currentPropertyName == "snelheid") tram->setSnelheid(currentPropertyValue);
            else if(currentPropertyName == "beginStation") beginStation=currentProperty->GetText();
        } else std::cerr << "Property of tram not supported: " << currentPropertyName << "\n";
        currentProperty = currentProperty->NextSiblingElement();
    }
    return std::make_pair(tram, beginStation);
}

void linkTramsAndStations(
        std::map<std::string, std::pair<Station *, std::pair<std::string, std::string> > > &stations,
        std::map<Tram *, std::string> &trams) {
    for(std::map<std::string,std::pair<Station*, std::pair<std::string, std::string> > >::iterator
                iter=stations.begin();iter!=stations.end(); iter++) {

        std::map<std::string,std::pair<Station*, std::pair<std::string, std::string> > >::const_iterator  vorige =
                stations.find(iter->second.second.first);
        std::map<std::string,std::pair<Station*, std::pair<std::string, std::string> > >::const_iterator  volgende =
                stations.find(iter->second.second.second);

        if(vorige == stations.end())
            std::cerr << "Station " << iter->second.second.first <<" does not exist!\n";
        else
            iter->second.first->setVorige(vorige->second.first);

        if(volgende == stations.end())
            std::cerr << "Station " << iter->second.second.second <<" does not exist!\n";
        else
            iter->second.first->setVolgende(volgende->second.first);
    }
    for(std::map<Tram*,std::string>::iterator iter=trams.begin();iter!=trams.end();iter++) {
        std::map<std::string,std::pair<Station*, std::pair<std::string, std::string> > >::const_iterator beginStation
            = stations.find(iter->second);
        if(beginStation == stations.end())
            std::cerr << "Station " << iter->second <<" does not exist for tram " << iter->first->getLijnNr() << "!\n";
        else {
            iter->first->setBeginStation(beginStation->second.first);
            iter->first->setHuidigeStation(beginStation->second.first);
        }
    }
}
Metronet Parser::parseFile(const std::string &relativeFilePath_str) {
    const char *relativeFilePath = relativeFilePath_str.c_str();
    TiXmlDocument doc;
    REQUIRE(doc.LoadFile(relativeFilePath), "File expected to be loaded!");
    Metronet metronet;
    TiXmlElement *currentElem = doc.FirstChildElement();
    std::map<std::string,std::pair<Station*, std::pair<std::string, std::string> > > stations;
    std::map<Tram *, std::string> trams;
    while (currentElem) {
        std::string name = currentElem->Value();
        if (isTagSupported(name)) {
            if (name == "STATION") {
                stations.insert(parseStation(currentElem));
            } else if (name == "TRAM") {
                trams.insert(parseTram(currentElem));
            }
        } else std::cerr << "Tag not supported: " << name << "\n";
        currentElem = currentElem->NextSiblingElement();
    }
    linkTramsAndStations(stations, trams);
    return metronet;
}
