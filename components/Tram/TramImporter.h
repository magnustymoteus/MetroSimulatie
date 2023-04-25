//
// Created by gruzi on 20/04/2023.
//

#ifndef PROJECT_SOFTWARE_PRACTICUM2_TRAMIMPORTER_H
#define PROJECT_SOFTWARE_PRACTICUM2_TRAMIMPORTER_H

#include <vector>
#include <string>

#include <tinyxml/tinyxml.h>
#include "Utils/VMetroObjectImporter.h"

#include "Tram/Tram.h"

const std::string tram_defaultConfigPath = "components/Tram/config_tram.xml";

class TramImporter : protected VMetroObjectImporter {
protected:
    TramImporter* _initCheck;
public:
    TramImporter(const std::string &configPath=tram_defaultConfigPath);
    bool properlyInitialized() const;

    Tram * parse(TiXmlElement *tramElem) const;
};


#endif //PROJECT_SOFTWARE_PRACTICUM2_TRAMIMPORTER_H
