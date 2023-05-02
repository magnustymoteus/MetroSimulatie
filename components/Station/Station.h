//
// Created by gruzi on 06/03/2023.
//

#ifndef PROJECT_SOFTWARE_PRACTICUM2_STATION_H
#define PROJECT_SOFTWARE_PRACTICUM2_STATION_H

#include <string>

#include "MetroObject/IMetroObject.h"

/**
 * @brief This serves as a metro Station.
 * @author Patryk Pilichowski
 * @author Daria Matviichuk
 * @date 06/03/2023
 * @version 0.1
 */

class Station : public IMetroObject {
private:
    Station* _initCheck;
protected:
    /**
     * @brief The name of the station
     */
    std::string fNaam;
    /**
     * @brief The type of the station, this is crucial for different tram types that only stop at certain station types
     */
    std::string fType;

    /**
     * @brief The tracks of the station, different tracks have different previous stations (predecessors) and
     * next stations (successors)
     */
    std::map<int, std::pair<Station*, Station*> > fSporen; // spoorNr : (vorige, volgende)
public:
    bool properlyInitialized() const;

    /**
     * @brief Constructor that initializes name and type of the station
     * @param naam name of the station
     * @param type type of the station, crucial for certain tram types that only stop at specific station types
     */
    Station(const std::string &naam, const std::string &type);

    // getters
    /**
     * @brief Returns the name of the station
     * @return name of the station
     */
    std::string getNaam() const;
    /**
     * @brief Returns the station's predecessor depending on the track number
     * @param spoorNr The track number
     * @return The preceding station on a specific track
     */
    Station* getVorige(const int &spoorNr) const;
    /**
    * @brief Returns the station's successor depending on the track number
    * @param spoorNr The track number
    * @return The succeeding station on a specific track
    */
    Station* getVolgende(const int &spoorNr) const;
    /**
     * @brief Returns the type of the station
     * @return Station type
     */
    const std::string &getType() const;
    /**
     * @brief Returns all the tracks of the station
     * @return Tracks of the station
     */
    std::map<int, std::pair<Station*, Station*> > getSporen() const;
    /**
     * @brief Returns a specific track of the station based on the given track number
     * @param spoorNr The given track number
     * @return The track with that track number
     * @pre Spoor exists
     */
    std::pair<Station*, Station*> getSpoor(const int &spoorNr) const;
    /**
     * @brief Checks if a certain track exits
     * @param spoorNr the track number
     * @return A boolean denoting if the track exists
     */
    bool spoorExists(const int &spoorNr) const;

    // setters
    /**
     * @brief Sets name of the station to the new value
     * @param newNaam The new value
     */
    void setNaam(const std::string &newNaam);
    /**
     * @brief Sets the station's predecessor on a specific track based on the track number
     * @param spoorNr the track number
     * @param newVorige the new predecessor
     */
    void setVorige(const int &spoorNr, Station* const &newVorige);
    /**
     * @brief Sets the station's successor on a specific track based on the track number
     * @param spoorNr the track number
     * @param newVolgende the new successor
     */
    void setVolgende(const int &spoorNr, Station* const &newVolgende);
    /**
     * @brief Sets the station's type to a new value
     * @param type the new value
     */
    void setType(const std::string &type);
    /**
     * @brief Sets the station's tracks to a new value
     * @param newSporen the new value
     */
    void setSporen(const std::map<int, std::pair<Station*, Station*> > &newSporen);
    /**
     * @brief Sets a station's specific track to a new value
     * @param spoorNr The track number
     * @param newSpoor the new value
     */
    void setSpoor(const int &spoorNr, const std::pair<Station*, Station*> &newSpoor);
};


#endif //PROJECT_SOFTWARE_PRACTICUM2_STATION_H
