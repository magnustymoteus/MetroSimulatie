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

#include "tinyxml.h"
#include <map>
#include <vector>
#include "../metronet/Metronet.h"

class Parser {
private:
     bool isTagSupported(const std::string &tagName) const;
     bool isPropertySupported(const std::string &tagName, const std::string &propertyName) const;
     void setSupportedTags();
     std::pair<std::string,std::pair<Station*, std::pair<std::string, std::string> > >
     parseStation(TiXmlElement* stationElem) const;
     std::pair<Tram*, std::string> parseTram(TiXmlElement* tramElem) const;
     std::map<std::string, std::vector<std::string> > fSupportedTags;
public:
     Parser();
     Metronet parseFile(const std::string &relativeFilePath);
};


#endif //PROJECT_SOFTWARE_PRACTICUM2_PARSER_H
