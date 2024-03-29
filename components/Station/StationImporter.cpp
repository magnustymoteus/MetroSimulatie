//
// Created by gruzi on 24/04/2023.
//

#include "StationImporter.h"

#include "DesignByContract.h"

StationImporter::StationImporter(const std::string &configPath) : VMetroObjectImporter(configPath) {
    _initCheck = this;
    ENSURE(properlyInitialized(), "Expected MetronetImporter to be properly initialized in constructor!");
}

bool StationImporter::properlyInitialized() const {
    return _initCheck == this;
}
Station* StationImporter::parse(TiXmlElement *stationElem) const {
    REQUIRE(this->properlyInitialized(), "Expected MetronetImporter to be properly initialized in parseStation!");
    const std::string stationStr = "STATION";
    REQUIRE(getValue(stationElem) == stationStr, "Expected stationElem to be Station tag!");

    std::string naam = getText(stationElem->FirstChildElement("naam"));
    std::string type = getText(stationElem->FirstChildElement("type"));
    Station* station = new Station(naam, type);

    ENSURE(station->getNaam().c_str(), "Station expected to have a name!");
    ENSURE(!station->getSporen().empty(), "Station expected to have non-empty sporen!");
    ENSURE(station->getType().c_str(), "Station expected to have type!");
    return station;
}