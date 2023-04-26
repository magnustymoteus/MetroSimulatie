//
// Created by gruzi on 06/03/2023.
//

#ifndef PROJECT_SOFTWARE_PRACTICUM2_METRONETIMPORTER_H
#define PROJECT_SOFTWARE_PRACTICUM2_METRONETIMPORTER_H


#include <map>
#include <vector>

#include "tinyxml/tinyxml.h"

#include "MetroObject/VMetroObjectImporter.h"

#include "Metronet/Metronet.h"
#include "Metronet/MetronetValidator.h"

#include "Tram/TramImporter.h"
#include "Station/StationImporter.h"
#include "Tram/TramType/TramTypeImporter.h"

/**
 * This serves as a parser which processes XML files containing information about the metro and
 * returns Metronet instance back.
 * @author Patryk Pilichowski
 * @author Daria Matviichuk
 * @date 06/03/2023
 * @version 0.1
 */

class MetronetImporter {
private:
    MetronetImporter* _initCheck;
protected:
    TramImporter fTramImporter;
    StationImporter fStationImporter;
    TramTypeImporter fTramTypeImporter;
public:
    MetronetImporter();

    bool properlyInitialized() const;

    Metronet* parseFile(const std::string &relativeFilePath);

    void parseStations(TiXmlDocument &doc, Metronet &metronet) const;
    void parseTrams(TiXmlDocument &doc, Metronet &metronet) const;
};


#endif //PROJECT_SOFTWARE_PRACTICUM2_METRONETIMPORTER_H
