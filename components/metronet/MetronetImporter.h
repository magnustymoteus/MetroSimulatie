//
// Created by gruzi on 06/03/2023.
//

#ifndef PROJECT_SOFTWARE_PRACTICUM2_METRONETIMPORTER_H
#define PROJECT_SOFTWARE_PRACTICUM2_METRONETIMPORTER_H

/**
 * This serves as a parser which processes XML files containing information about the metro.
 * @author Patryk Pilichowski
 * @author Daria Matviichuk
 * @date 06/03/2023
 * @version 0.1
 */

#include "tinyxml/tinyxml.h"
#include <map>
#include <vector>
#include "metronet/Metronet.h"
#include "metronet/MetronetValidator.h"

class MetronetImporter {
protected:
    MetronetImporter* _initCheck;
     std::string configPath;
    std::map<std::string, std::vector<std::string> > fSupportedTags;
public:
    MetronetImporter();
    void setConfigPath(const std::string &configFilePath);
    std::string getConfigPath() const;

    bool properlyInitialized() const;
     Metronet parseFile(const std::string &relativeFilePath);
    bool isTagSupported(const std::string &tagName) const;
    bool isPropertySupported(const std::string &tagName, const std::string &propertyName) const;
    std::map<std::string, std::vector<std::string> > getSupportedTags() const;
    void loadSupportedTags();
    Station* parseStation(TiXmlElement* stationElem) const;
    Tram* parseTram(TiXmlElement* tramElem) const;
};


#endif //PROJECT_SOFTWARE_PRACTICUM2_METRONETIMPORTER_H
