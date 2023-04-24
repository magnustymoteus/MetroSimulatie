//
// Created by gruzi on 24/04/2023.
//

#include "StationImporter.h"

#include <iostream>
#include <sstream>

#include "DesignByContract.h"

const std::string configFilePath = "components/station/config_station.xml";

StationImporter::StationImporter() : VMetroObjectImporter(configFilePath) {
    _initCheck = this;
    ENSURE(properlyInitialized(), "Expected MetronetImporter to be properly initialized in constructor!");
}

bool StationImporter::properlyInitialized() const {
    return _initCheck == this;
}
Station* StationImporter::parse(TiXmlElement *stationElem) const {
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
            else if(currentPropertyName == "type"){
                station->setType(currentElem->GetText());
            }
        }
        else std::cerr << "Property not supported for tag " << stationElem->Value() << ": " << currentElem->Value()
                       << "\n";
        currentElem = currentElem->NextSiblingElement();
    }
    ENSURE(station->getNaam().c_str(), "Station expected to have a name!");
    ENSURE(station->getSpoorNr(), "Station expected to have spoorNr!");
    ENSURE(station->getType().c_str(), "Station expected to have type!");
    return station;
}