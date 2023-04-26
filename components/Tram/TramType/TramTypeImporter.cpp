//
// Created by gruzi on 25/04/2023.
//

#include "TramTypeImporter.h"

#include "DesignByContract.h"
\
std::map<std::string, TramType *> TramTypeImporter::getSupportedTramTypes() const {
    REQUIRE(this->properlyInitialized(),
            "Expected MetronetImporter to be properly initialized!");
    return fSupportedTramTypes;
}
TramTypeImporter::TramTypeImporter(const std::string &configPath, const std::string &tramTypesPath) :
VMetroObjectImporter(configPath){
    _initCheck = this;
    fTramTypesPath = tramTypesPath;
    loadSupportedTramTypes();
    ENSURE(properlyInitialized(), "Expected TramImporter to be properly initialized in constructor!");
}
bool TramTypeImporter::properlyInitialized() const {
    return _initCheck == this;
}
void TramTypeImporter::loadSupportedTramTypes() {
    REQUIRE(this->properlyInitialized(),
            "Expected MetronetImporter to be properly initialized in loadSupportedTramTypes!");
    TiXmlDocument doc;
    REQUIRE(doc.LoadFile(fTramTypesPath.c_str()), "Expected tramTypes file to load!");
    TiXmlElement* currentElem = doc.FirstChildElement("TRAM_TYPE");
    while(currentElem) {
        TramType* tramType = parse(currentElem);
        fSupportedTramTypes.insert(std::make_pair(tramType->getNaam(), tramType));
        currentElem = currentElem->NextSiblingElement("TRAM_TYPE");
    }
}
TramType* TramTypeImporter::parse(TiXmlElement *tramTypeElem) const {
    REQUIRE(this->properlyInitialized(), "Expected MetronetImporter to be properly initialized in parse!");
    const std::string tramStr = "TRAM_TYPE";
    REQUIRE(tramTypeElem->Value() == tramStr, "Expected tramTypeElem to be TRAM_TYPE tag!");
    const std::string naam = tramTypeElem->FirstChildElement("naam")->GetText();
    int snelheid;
    std::vector<std::string> bediendeStationTypes;
    std::istringstream(tramTypeElem->FirstChildElement("snelheid")->GetText()) >> snelheid;
    TiXmlElement* bedienden = tramTypeElem->FirstChildElement("bedient")->FirstChildElement("bediende");
    while(bedienden) {
        const std::string bediende = bedienden->GetText();
        bediendeStationTypes.push_back(bediende);
        bedienden = bedienden->NextSiblingElement("bediende");
    }
    TramType* tramType = new TramType(naam, snelheid, bediendeStationTypes);
    return tramType;
}
