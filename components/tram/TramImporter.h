//
// Created by gruzi on 20/04/2023.
//

#ifndef PROJECT_SOFTWARE_PRACTICUM2_TRAMIMPORTER_H
#define PROJECT_SOFTWARE_PRACTICUM2_TRAMIMPORTER_H

#include <vector>
#include <string>

#include <tinyxml/tinyxml.h>
#include "utils/VMetroObjectImporter.h"

#include "tram/Tram.h"

class TramImporter : protected VMetroObjectImporter {
protected:
    std::vector<std::string> fSupportedTramTypes;
    TramImporter* _initCheck;
    std::string configPath;
public:
    TramImporter();
    bool properlyInitialized() const;

    std::vector<std::string> getSupportedTramTypes() const;

    bool isTramTypeSupported(const std::string &tramType) const;

    Tram * parse(TiXmlElement *tramElem) const;
};


#endif //PROJECT_SOFTWARE_PRACTICUM2_TRAMIMPORTER_H
