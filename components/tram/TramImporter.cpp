//
// Created by gruzi on 20/04/2023.
//

#include "TramImporter.h"

#include <iostream>
#include <sstream>

#include "DesignByContract.h"

const std::string configFilePath = "components/tram/config_tram.xml";

TramImporter::TramImporter() : VTagImporter(configFilePath) {
    _initCheck = this;
    ENSURE(properlyInitialized(), "Expected TramImporter to be properly initialized in constructor!");
}
bool TramImporter::properlyInitialized() const {
    return _initCheck == this;
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
Tram * TramImporter::parse(TiXmlElement *tramElem) const {
    REQUIRE(this->properlyInitialized(), "Expected MetronetImporter to be properly initialized in parseTram!");
    const std::string tramStr = "TRAM";
    REQUIRE(tramElem->Value() == tramStr, "Expected tramElem to be tram tag!");
    TiXmlElement* currentElem = tramElem->FirstChildElement();
    int lijnNr, voertuigNr;
    std::string type;
    while(currentElem) {
        std::string currentPropertyName = currentElem->Value();
        if(isPropertySupported(tramElem->Value(), currentPropertyName)) {
            int currentPropertyValue;
            std::istringstream(currentElem->GetText()) >> currentPropertyValue;
            if(currentPropertyName == "lijnNr") lijnNr = currentPropertyValue;
            else if(currentPropertyName == "type") type = currentElem->GetText();
            else if(currentPropertyName == "voertuigNr") voertuigNr = currentPropertyValue;
        }
        else std::cerr << "Property not supported for tag " << tramElem->Value() << ": " << currentElem->Value()
                       << "\n";
        currentElem = currentElem->NextSiblingElement();
    }
    Tram* tram = new Tram(lijnNr, voertuigNr, type);

    ENSURE(tram->getLijnNr(), "Tram expected to have lijnNr!");
    ENSURE(tram->getType().c_str(), "Tram expected to have type!");
    ENSURE(tram->getVoertuigNr(), "Tram expected to have voertuigNr!");
    return tram;
}