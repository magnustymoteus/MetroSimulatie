//
// Created by gruzi on 24/04/2023.
//

#ifndef PROJECT_SOFTWARE_PRACTICUM2_STATIONIMPORTER_H
#define PROJECT_SOFTWARE_PRACTICUM2_STATIONIMPORTER_H

#include "Utils/VMetroObjectImporter.h"

#include "Station.h"

const std::string station_defaultConfigPath = "components/Station/config_station.xml";

class StationImporter :  protected VMetroObjectImporter {
    StationImporter* _initCheck;
public:
    StationImporter(const std::string &configPath=station_defaultConfigPath);

    bool properlyInitialized() const;

    Station* parse(TiXmlElement *stationElem) const;
};


#endif //PROJECT_SOFTWARE_PRACTICUM2_STATIONIMPORTER_H
