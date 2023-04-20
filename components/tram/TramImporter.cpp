//
// Created by gruzi on 20/04/2023.
//

#include "TramImporter.h"
#include "DesignByContract.h"

const std::string defaultConfigPath = "components/tram/supportedTramTypes.xml";

TramImporter::TramImporter() {
    _initCheck = this;
    configPath = defaultConfigPath;
    loadSupportedTramTypes();
    TiXmlDocument doc;
    ENSURE(properlyInitialized(), "Expected TramImporter to be properly initialized in constructor!");
    ENSURE(doc.LoadFile(configPath.c_str()), "Expected default configPath to load!");
}
bool TramImporter::properlyInitialized() const {
    return _initCheck == this;
}
void TramImporter::setConfigPath(const std::string &configFilePath) {
    REQUIRE(this->properlyInitialized(), "Expected MetronetImporter to be properly initialized in setConfigPath!");
    configPath = configFilePath;
}
std::string TramImporter::getConfigPath() const {
    REQUIRE(this->properlyInitialized(), "Expected MetronetImporter to be properly initialized in getConfigPath!");
    return configPath;
}
void TramImporter::loadSupportedTramTypes() {
    REQUIRE(this->properlyInitialized(),
            "Expected MetronetImporter to be properly initialized in loadSupportedTramTypes!");
    TiXmlDocument doc;
    REQUIRE(doc.LoadFile(configPath.c_str()), "Config file expected to be loaded!");
    fSupportedTramTypes.clear();
    TiXmlElement* currentElem = doc.FirstChildElement()->FirstChildElement();
    while(currentElem) {
        TiXmlElement* currentSupportedTag = currentElem->FirstChildElement();
        std::string currentSupportedTramType = currentSupportedTag->GetText();
        fSupportedTramTypes.push_back(currentSupportedTramType);
        currentElem = currentElem->NextSiblingElement();
    }
}
std::vector<std::string> TramImporter::getSupportedTramTypes() const {
    REQUIRE(this->properlyInitialized(),
            "Expected MetronetImporter to be properly initialized in getSupportedTramTypes!");
    return fSupportedTramTypes;
}
bool TramImporter::isTramTypeSupported(const std::string &tramType) const {
    REQUIRE(this->properlyInitialized(),
            "Expected MetronetImporter to be properly initialized in isTramTypeSupported!");
    for(size_t i = 0; i<fSupportedTramTypes.size();i++){
        if(fSupportedTramTypes[i] == tramType) return true;
    }
    return false;
}