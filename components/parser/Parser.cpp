//
// Created by gruzi on 06/03/2023.
//

#include "Parser.h"
#include "tinyxml.h"
#include "../../DesignByContract.h"


const char* configFilePath = "components/parser/config.xml";

Parser::Parser() {
    setSupportedTags();
}

void Parser::setSupportedTags() {
    TiXmlDocument doc;
    REQUIRE(doc.LoadFile(configFilePath), "Config file not found!");
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

Metronet Parser::parseFile(const std::string &relativeFilePath_str) {
    const char* relativeFilePath = relativeFilePath_str.c_str();
    TiXmlDocument doc;
    REQUIRE(doc.LoadFile(relativeFilePath), "File not found!");
    REQUIRE(isFileValid(relativeFilePath), "File not valid! (Some tag or property not supported)");
    Metronet metronet;
    TiXmlElement* currentElem = doc.FirstChildElement();
    while(currentElem) {
        std::string name = currentElem->Value();
        currentElem = currentElem->NextSiblingElement();
        // TO DO
    }
    return metronet;
}
bool Parser::isFileValid(const std::string &relativeFilePath_str) const {
    const char* relativeFilePath = relativeFilePath_str.c_str();
    TiXmlDocument doc;
    REQUIRE(doc.LoadFile(relativeFilePath), "File not found!");
    TiXmlElement* currentElem = doc.FirstChildElement();
    while(currentElem) {
        if(!isTagSupported(currentElem->Value())) return false;
        else {
            TiXmlElement* currentProperty = currentElem->FirstChildElement();
            while(currentProperty) {
                if(!isPropertySupported(currentElem->Value(), currentProperty->Value()))
                    return false;
                currentProperty = currentProperty->NextSiblingElement();
            }
        }
        currentElem = currentElem->NextSiblingElement();
    }
    return true;
}