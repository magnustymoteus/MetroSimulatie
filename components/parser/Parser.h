//
// Created by gruzi on 06/03/2023.
//

#ifndef PROJECT_SOFTWARE_PRACTICUM2_PARSER_H
#define PROJECT_SOFTWARE_PRACTICUM2_PARSER_H

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

class Parser {
protected:
    Parser* _initCheck;
     std::string configPath;
    std::map<std::string, std::vector<std::string> > fSupportedTags;
public:
    Parser();
    Parser(const std::string &configFile);
    bool properlyInitialized() const;
     Metronet parseFile(const std::string &relativeFilePath);
    bool isTagSupported(const std::string &tagName) const;
    bool isPropertySupported(const std::string &tagName, const std::string &propertyName) const;
    std::map<std::string, std::vector<std::string> > getSupportedTags() const;
    void setSupportedTags();
    Station* parseStation(TiXmlElement* stationElem) const;
    Tram* parseTram(TiXmlElement* tramElem) const;
};


#endif //PROJECT_SOFTWARE_PRACTICUM2_PARSER_H
