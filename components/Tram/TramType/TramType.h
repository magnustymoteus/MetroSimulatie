//
// Created by gruzi on 25/04/2023.
//

#ifndef PROJECT_SOFTWARE_PRACTICUM2_TRAMTYPE_H
#define PROJECT_SOFTWARE_PRACTICUM2_TRAMTYPE_H

#include "MetroObject/IMetroObject.h"


/**
 * @brief Adds more information to Tram such as supported station types and the speed
 * @author Patryk Pilichowski
 * @author Daria Matviichuk
 * @date 06/03/2023
 * @version 0.1
 */

class TramType : public IMetroObject {
private:
    TramType* _initCheck;
protected:
    /**
     * @brief The name of the tram type
     */
    std::string fNaam;
    /**
     * @brief The speed of the tram type
     */
    int fSnelheid;
    /**
     * @brief The stations that the tram type supports (can stop at)
     */
    std::vector<std::string> fBediendeStationTypes;
public:
    bool properlyInitialized() const;
    /**
     * @brief The constructor which sets the name, speed and supported station types
     * @param newNaam the name
     * @param newSnelheid the speed
     * @param newBediendeStationTypes the supported station types
     */
    TramType(const std::string &newNaam, const int &newSnelheid,
             const std::vector<std::string> &newBediendeStationTypes);


    /**
     * @brief Checks whether the tram type supports a specific station type
     * @param stationType the station type
     * @return a boolean denoting if the station type is supported
     */
    bool supportsStationType(const std::string &stationType) const;

    /**
     * @brief Returns the name of the tram type
     * @return the name of the tram type
     */
    std::string getNaam() const;
    /**
     * @brief Returns the speec of the tram type
     * @return The speed
     */
    int getSnelheid() const;
    /**
     * @brief Returns all supported station types
     * @return All station types supported by this tram type
     */
    std::vector<std::string> getBediendeStationTypes() const;
    /**
     * @brief Sets the name of the tram type to a new value
     * @param newNaam the new value
     */
    void setNaam(const std::string &newNaam);
    /**
     * @brief Sets the speed of the tram type to a new value
     * @param newSnelheid The new value
     */
    void setSnelheid(const int &newSnelheid);
    /**
     * @brief Sets the supported station types to a new value
     * @param newBediendeStationTypes the new value
     */
    void setBediendeStationTypes(const std::vector<std::string> &newBediendeStationTypes);
};


#endif //PROJECT_SOFTWARE_PRACTICUM2_TRAMTYPE_H
