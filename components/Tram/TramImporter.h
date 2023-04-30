//
// Created by gruzi on 20/04/2023.
//

#ifndef PROJECT_SOFTWARE_PRACTICUM2_TRAMIMPORTER_H
#define PROJECT_SOFTWARE_PRACTICUM2_TRAMIMPORTER_H

#include <vector>
#include <string>

#include <tinyxml/tinyxml.h>
#include "MetroObject/VMetroObjectImporter.h"

#include "Tram/Tram.h"

/**
 * @brief Importer for Tram
 * @author Patryk Pilichowski
 * @author Daria Matviichuk
 * @date 06/03/2023
 * @version 0.1
 */

class TramImporter : protected VMetroObjectImporter {
private:
    TramImporter* _initCheck;
public:
    TramImporter(const std::string &configPath=ConfigManager::TramConfig());
    bool properlyInitialized() const;

    Tram * parse(TiXmlElement *tramElem) const;
};


#endif //PROJECT_SOFTWARE_PRACTICUM2_TRAMIMPORTER_H
