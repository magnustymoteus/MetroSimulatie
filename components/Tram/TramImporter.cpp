//
// Created by gruzi on 20/04/2023.
//

#include "TramImporter.h"
#include "PCC.h"
#include "Stadslijner.h"
#include "Albatros.h"

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
    TramType type = stringToTramType(getText(getFirstChildProperty(tramElem, "type")));

    if(type == TramType_PCC) {
        std::istringstream(getText(getFirstChildProperty(tramElem, "aantalDefecten")))
        >> aantalDefecten;
        std::istringstream(getText(getFirstChildProperty(tramElem, "reparatieTijd")))
        >> reparatieTijd;
    }
    Tram* tram = 0;
    switch(type) {
        case TramType_PCC:
            tram = new PCC(lijnNr, voertuigNr, type, aantalDefecten, reparatieTijd);
            break;
        case TramType_Stadslijner:
            tram = new Stadslijner(lijnNr, voertuigNr, type);
            break;
        case TramType_Albatros:
            tram = new Albatros(lijnNr, voertuigNr, type);
            break;
        default:
            break;
    }
    ENSURE(tram, "Tram type unsupported!");
    ENSURE(tram->getLijnNr(), "Tram expected to have lijnNr!");
    ENSURE(tram->getVoertuigNr(), "Tram expected to have voertuigNr!");
    return tram;
}