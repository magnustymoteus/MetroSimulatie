//
// Created by gruzi on 24/04/2023.
//

#ifndef PROJECT_SOFTWARE_PRACTICUM2_STATIONIMPORTER_H
#define PROJECT_SOFTWARE_PRACTICUM2_STATIONIMPORTER_H

#include "MetroObject/VMetroObjectImporter.h"

#include "Station.h"

/**
 * @brief An importer for Station
 * @author Patryk Pilichowski
 * @author Daria Matviichuk
 * @date 06/03/2023
 * @version 0.1
 */

class StationImporter :  protected VMetroObjectImporter {
private:
    StationImporter* _initCheck;
public:
    StationImporter(const std::string &configPath=ConfigManager::StationConfig());

    bool properlyInitialized() const;

    Station* parse(TiXmlElement *stationElem) const;
};


#endif //PROJECT_SOFTWARE_PRACTICUM2_STATIONIMPORTER_H
