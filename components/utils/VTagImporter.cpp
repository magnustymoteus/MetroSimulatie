//
// Created by gruzi on 24/04/2023.
//

#include "VTagImporter.h"

#include "DesignByContract.h"

VTagImporter::VTagImporter(const std::string &configFilePath) {
    _initCheck = this;
    configPath = configFilePath;
    loadSupportedTags();
    TiXmlDocument doc;
    ENSURE(properlyInitialized(), "Expected MetronetImporter to be properly initialized in constructor!");
    ENSURE(doc.LoadFile(configPath.c_str()), "Expected configPath to load!");
}

bool VTagImporter::properlyInitialized() const {
    return _initCheck == this;
}

std::map<std::string, std::vector<std::string> > VTagImporter::getSupportedTags() const {
    REQUIRE(this->properlyInitialized(), "Expected MetronetImporter to be properly initialized in getSupportedTags!");
    return fSupportedTags;
}
std::string VTagImporter::getConfigPath() const {
    REQUIRE(this->properlyInitialized(), "Expected MetronetImporter to be properly initialized in getConfigPath!");
    return configPath;
}
void VTagImporter::setConfigPath(const std::string &configFilePath) {
    REQUIRE(this->properlyInitialized(), "Expected MetronetImporter to be properly initialized in setConfigPath!");
    configPath = configFilePath;
    loadSupportedTags();
}
bool VTagImporter::isTagSupported(const std::string &tagName) const {
    REQUIRE(this->properlyInitialized(), "Expected MetronetImporter to be properly initialized in isTagSupported!");
    return fSupportedTags.find(tagName) != fSupportedTags.end();
}
/*
 * This function parses a config.xml file to get all supported tags
 * All supported tags are saved to fSupportedTags (protected variable of VTagImporter class)
 */
void VTagImporter::loadSupportedTags(const std::string &configFilePath) {
    REQUIRE(this->properlyInitialized(), "Expected MetronetImporter to be properly initialized in loadSupportedTags!");
    TiXmlDocument doc;
    REQUIRE(doc.LoadFile(configFilePath.c_str()), "Config file expected to be loaded!");
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
void VTagImporter::loadSupportedTags() {
    loadSupportedTags(configPath);
}

bool VTagImporter::isPropertySupported(const std::string &tagName, const std::string &propertyName) const {
    REQUIRE(isTagSupported(tagName), "Tag name expected to be supported!");
    REQUIRE(this->properlyInitialized(), "Expected MetronetImporter to be properly initialized in isPropertySupported!");
    const std::vector<std::string> &properties = fSupportedTags.at(tagName);
    for(long unsigned int i=0;i<properties.size();i++) {
        if(properties[i] == propertyName) return true;
    }
    return false;
}
