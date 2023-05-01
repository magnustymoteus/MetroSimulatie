//
// Created by gruzi on 20/04/2023.
//

#include "TramImporter.h"

TramImporter::TramImporter(const std::string &configPath) : VMetroObjectImporter(configPath) {
    _initCheck = this;
    ENSURE(properlyInitialized(), "Expected TramImporter to be properly initialized in constructor!");
}
bool TramImporter::properlyInitialized() const {
    return _initCheck == this;
}
Tram * TramImporter::parse(TiXmlElement *tramElem) const {
    REQUIRE(this->properlyInitialized(), "Expected MetronetImporter to be properly initialized in parse!");
    const std::string tramStr = "TRAM";
    REQUIRE(getValue(tramElem) == tramStr, "Expected tramElem to be Tram tag!");

    int lijnNr, voertuigNr, aantalDefecten=0, reparatieTijd=0;
    std::istringstream(getText(getFirstChildProperty(tramElem, "lijnNr"))) >> lijnNr;
    std::istringstream(getText(getFirstChildProperty(tramElem, "voertuigNr"))) >> voertuigNr;

    const std::string typeWithDefects = "PCC";
    if(getText(getFirstChildProperty(tramElem, "type")) == typeWithDefects) {
        std::istringstream(getText(getFirstChildProperty(tramElem, "aantalDefecten")))
        >> aantalDefecten;
        std::istringstream(getText(getFirstChildProperty(tramElem, "reparatieTijd")))
        >> reparatieTijd;
    }
    Tram* tram = new Tram(lijnNr, voertuigNr, aantalDefecten, reparatieTijd);

    ENSURE(tram->getLijnNr(), "Tram expected to have lijnNr!");
    ENSURE(tram->getVoertuigNr(), "Tram expected to have voertuigNr!");
    return tram;
}