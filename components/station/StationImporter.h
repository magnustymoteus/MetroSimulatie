//
// Created by gruzi on 24/04/2023.
//

#ifndef PROJECT_SOFTWARE_PRACTICUM2_STATIONIMPORTER_H
#define PROJECT_SOFTWARE_PRACTICUM2_STATIONIMPORTER_H

#include "utils/VMetroObjectImporter.h"

#include "Station.h"

class StationImporter :  protected VMetroObjectImporter {
    StationImporter* _initCheck;
public:
    StationImporter();

    bool properlyInitialized() const;

    Station* parse(TiXmlElement *stationElem) const;
};


#endif //PROJECT_SOFTWARE_PRACTICUM2_STATIONIMPORTER_H
