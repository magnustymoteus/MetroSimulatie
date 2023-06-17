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

/**
 * @brief This serves as a parser which processes XML files containing information about the metro and
 * returns Metronet instance back.
 * @author Patryk Pilichowski
 * @author Daria Matviichuk
 * @date 06/03/2023
 * @version 0.1
 */

class MetronetImporter : public VMetroObjectImporter {
private:
    MetronetImporter* _initCheck;
protected:
    /**
     * @brief Importer for trams
     */
    TramImporter fTramImporter;
    /**
     * @brief Importer for stations
     */
    StationImporter fStationImporter;
public:
    bool properlyInitialized() const;
    /**
     * @brief Constructor of MetronetImporter
     * @pre: MetronetImporter is properly initialised
     * @post: MetronetImporter with at least one supported tag is created
     */
    MetronetImporter();

    Metronet* parse(TiXmlElement* rootElem) const;

    /**
     * @brief Parses an xml file into a Metronet instance
     * @pre: MetronetImporter is properly initialised
     * @return An instance of Metronet
     * @param relativeFilePath The filepath of the xml file
     */
    Metronet* parseFile(const std::string &relativeFilePath) const;

    /**
     * @brief Parses xml tags representing stations into multiple instances of Station and adds them to metronet
     * @pre: MetronetImporter is properly initialised
     * @param rootElem The root element of the xml file
     * @param metronet An instance of Metronet
     */
    void parseStations(TiXmlElement* rootElem, Metronet* &metronet) const;
    /**
    * @brief Parses xml tags representing trams into multiple instances of Tram and adds them to metronet
    * @pre: MetronetImporter is properly initialised
    * @param rootElem The root element of the xml file
    * @param metronet An instance of Metronet
    */
    void parseTrams(TiXmlElement* rootElem, Metronet* &metronet) const;
    /**
     * @brief Gets the tags that are supported
     * @pre: MetronetImporter is properly initialised
     * @return A map of all the supported tags
     */
};


#endif //PROJECT_SOFTWARE_PRACTICUM2_METRONETIMPORTER_H
