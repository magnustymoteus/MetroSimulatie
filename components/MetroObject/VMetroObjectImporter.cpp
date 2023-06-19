//
// Created by gruzi on 24/04/2023.
//

#include "VMetroObjectImporter.h"

#include "DesignByContract.h"

VMetroObjectImporter::VMetroObjectImporter(const std::string &configFilePath) : fConfigPath(configFilePath) {
    _initCheck = this;
    loadSupportedTags();
    TiXmlDocument doc;
    ENSURE(properlyInitialized(), "Expected MetronetImporter to be properly initialized in constructor!");
    ENSURE(doc.LoadFile(fConfigPath.c_str()), "Expected configPath to load!");
}
VMetroObjectImporter::VMetroObjectImporter() {
    _initCheck = this;
    ENSURE(properlyInitialized(), "Expected MetronetImporter to be properly initialized in constructor!");
}

bool VMetroObjectImporter::properlyInitialized() const {
    return _initCheck == this;
}

std::map<std::string, std::vector<std::string> > VMetroObjectImporter::getSupportedTags() const {
    REQUIRE(this->properlyInitialized(), "Expected MetronetImporter to be properly initialized in getSupportedTags!");
    return fSupportedTags;
}
std::string VMetroObjectImporter::getConfigPath() const {
    REQUIRE(this->properlyInitialized(), "Expected MetronetImporter to be properly initialized in getConfigPath!");
    return fConfigPath;
}
void VMetroObjectImporter::setConfigPath(const std::string &configFilePath) {
    REQUIRE(this->properlyInitialized(), "Expected MetronetImporter to be properly initialized in setConfigPath!");
    fConfigPath = configFilePath;
    loadSupportedTags();
}
bool VMetroObjectImporter::isTagSupported(const std::string &tagName) const {
    REQUIRE(this->properlyInitialized(), "Expected MetronetImporter to be properly initialized in isTagSupported!");
    return fSupportedTags.find(tagName) != fSupportedTags.end();
}
/*
 * This function parses a config.xml file to get all supported tags
 * All supported tags are saved to fSupportedTags (protected variable of VMetroObjectImporter class)
 */
void VMetroObjectImporter::loadSupportedTags(const std::string &configFilePath) {
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
std::string VMetroObjectImporter::getValue(TiXmlElement *elem) const {
    REQUIRE(this->properlyInitialized(), "Expected MetronetImporter to be properly initialized!");
    REQUIRE(elem, "Expected element to not be null!");
    return elem->Value();
}
std::string VMetroObjectImporter::getText(TiXmlElement *elem) const {
    REQUIRE(this->properlyInitialized(), "Expected MetronetImporter to be properly initialized!");
    REQUIRE(elem, "Expected element to not be null!");
    return elem->GetText();
}
void VMetroObjectImporter::loadSupportedTags() {
    REQUIRE(this->properlyInitialized(), "Expected MetronetImporter to be properly initialized!");
    loadSupportedTags(fConfigPath);
}
TiXmlElement* VMetroObjectImporter::getNextSiblingProperty(TiXmlElement *elem, const std::string &propertyName) const {
    REQUIRE(this->properlyInitialized(), "Expected MetronetImporter to be properly initialized!");
    const std::string notSupportedPropertyStr1 = "Expected property '"+std::string(elem->Value())+"' to be supported!";
    REQUIRE(isPropertySupported(elem->Parent()->Value(), elem->Value()),
            notSupportedPropertyStr1.c_str());
    const std::string notSupportedPropertyStr2 =  "Expected property '"+propertyName+"' to be supported!";
    CERR_IF_FALSE(isPropertySupported(elem->Parent()->Value(), propertyName),
                  VHandleableMetroObjectException(notSupportedPropertyStr2.c_str()));
    return elem->NextSiblingElement(propertyName.c_str());
}
TiXmlElement* VMetroObjectImporter::getNextSiblingTag(TiXmlElement *elem, const std::string &tagName) const {
    REQUIRE(this->properlyInitialized(), "Expected MetronetImporter to be properly initialized!");
    const std::string notSupportedStr = "'"+tagName+"' tag is not supported!";
    CERR_IF_FALSE(isTagSupported(tagName), VHandleableMetroObjectException(notSupportedStr.c_str()));
    return elem->NextSiblingElement(tagName.c_str());
}
TiXmlElement *VMetroObjectImporter::getFirstChildProperty(TiXmlElement *elem, const std::string &propertyName) const {
    REQUIRE(this->properlyInitialized(), "Expected MetronetImporter to be properly initialized!");
    const std::string notSupportedTagStr = "Expected tag '"+std::string(elem->Value())+"' to be supported!";
    REQUIRE(isTagSupported(elem->Value()), notSupportedTagStr.c_str());
    const std::string notSupportedPropertyStr =  "Expected property '"+propertyName+"' to be supported!";
    CERR_IF_FALSE(isPropertySupported(elem->Value(), propertyName),
                  VHandleableMetroObjectException(notSupportedPropertyStr.c_str()));
    return elem->FirstChildElement(propertyName.c_str());
}
TiXmlElement *VMetroObjectImporter::getFirstChildTag(TiXmlElement* elem, const std::string &tagName) const {
    REQUIRE(this->properlyInitialized(), "Expected MetronetImporter to be properly initialized in loadSupportedTags!");
    const std::string notSupportedStr = "'"+tagName+"' tag is not supported!";
    CERR_IF_FALSE(isTagSupported(tagName), VHandleableMetroObjectException(notSupportedStr.c_str()));
    return elem->FirstChildElement(tagName.c_str());
}

bool VMetroObjectImporter::isPropertySupported(const std::string &tagName, const std::string &propertyName) const {
    REQUIRE(isTagSupported(tagName), "Tag name expected to be supported!");
    REQUIRE(this->properlyInitialized(), "Expected MetronetImporter to be properly initialized in isPropertySupported!");
    const std::vector<std::string> &properties = fSupportedTags.at(tagName);
    for(long unsigned int i=0;i<properties.size();i++) {
        if(properties[i] == propertyName) return true;
    }
    return false;
}
