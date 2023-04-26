//
// Created by gruzi on 24/04/2023.
//

#ifndef PROJECT_SOFTWARE_PRACTICUM2_STATIONIMPORTER_H
#define PROJECT_SOFTWARE_PRACTICUM2_STATIONIMPORTER_H

#include "MetroObject/VMetroObjectImporter.h"

#include "Station.h"


class StationImporter :  protected VMetroObjectImporter {
private:
    StationImporter* _initCheck;
public:
    StationImporter(const std::string &configPath=ConfigManager::StationConfig());

    bool properlyInitialized() const;

    Station* parse(TiXmlElement *stationElem) const;
};


#endif //PROJECT_SOFTWARE_PRACTICUM2_STATIONIMPORTER_H
