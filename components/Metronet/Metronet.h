//
// Created by gruzi on 12/03/2023.
//

#ifndef PROJECT_SOFTWARE_PRACTICUM2_METRONET_H
#define PROJECT_SOFTWARE_PRACTICUM2_METRONET_H

#include "Station/Station.h"
#include "Tram/Tram.h"

class MetronetValidator; // forward declaration

/**
 * @brief This serves as a simulatable network of trams circulating around stations.
 * @author Patryk Pilichowski
 * @author Daria Matviichuk
 * @date 12/03/2023
 * @version 0.1
 */

class Metronet : public IMetroObject {
private:
    Metronet* _initCheck;
protected:
    /**
    * @brief All stations of the metronet
    */
    std::map<std::string, Station*> fStations; // stations (name : Station*)
    /**
    * @brief All trams of the metronet
    */
    std::multimap<int, Tram*> fTrams; // a map that holds all trams (lijnNr : Tram*)
    /**
    * @brief All tram types of the metronet
    */
    std::map<std::string, TramType*> fTramTypes;
    /**
    * @brief A boolean denoting the consistency of the metronet
    */
    bool isConsistent;
public:
    bool properlyInitialized() const;
    /**
    * @brief Gets the trams of the metronet
    * @return the trams of the metronet
    */
    std::multimap<int, Tram*> getTrams() const;
    /**
    * @brief Gets the stations of the metronet
    * @return the stations of the metronet
    */
    std::map<std::string, Station*> getStations() const;
    /**
    * @brief Gets the tram types of the metronet
    * @return the tram types of the metronet
    */
    std::map<std::string, TramType*> getTramTypes() const;
    /**
    * @brief Returns the consistency of the metronet
    * @return a boolean denoting the consistency of the metronet
    */
    bool getIsConsistent() const;

    /**
    * @brief Sets trams to a new value
    * @param newTrams the new value
    */
    void setTrams(std::multimap<int, Tram*> &newTrams);
    /**
    * @brief Sets stations to a new value
    * @param newStations the new value
    */
    void setStations(std::map<std::string, Station*> &newStations);
    /**
    * @brief Sets tramTypes to a new value
    * @param newTramTypes the new value
    */
    void setTramTypes(const std::map<std::string, TramType *> &newTramTypes);

    /**
    * @brief Sets isConsistent to a new value
    * @param newIsConsistent the new value
    */
    void setIsConsistent(const bool &newIsConsistent);

    /**
    * @brief Checks if there is a tram currently stopping at a station
    * @param stationName the name of the station
     *@param spoorNr the track number of the station
     * @return Boolean denoting if there is a tram currently stopping on a station
    */
    bool isTramOnStation(const std::string &stationName, const int &spoorNr) const;

    /**
    * @brief Initializes metronet
    * @param newStations the new stations of the metronet
     *@param newTrams the new trams of the metronet
    */
    Metronet(std::map<std::string, Station*> &newStations, std::multimap<int, Tram*> &newTrams);
    /**
    * @brief Initializes metronet
    */
    Metronet();
    /**
    * @brief Deletes all dynamically created instances of Tram, Station, and TramType
    */
    ~Metronet();

    /**
    * @brief Moves a tram to the next n stations
    * @param tram The tram that must be moved
    * @param steps Number of times we want to move the tram to the next station to
    * @pre steps > 0
    * @post Successfully moved the tram to the next supporting station n times
    */
    void moveTram(Tram* &tram, const unsigned int &steps=1) const;

    /**
    * @brief Adds a station to the metronet
    * @param station The station that must be added
    */
    void pushStation(Station* station);
    /**
    * @brief Adds a tram to the metronet
    * @param tram the tram that must be added
    */
    void pushTram(Tram* tram);

    /**
    * @brief Retrieves a station
    * @param naam the name of the station
    * @return A unique station
    */
    Station* retrieveStation(const std::string &naam) const;

    /**
    * @brief Retrieves a tram
    * @param lijnNr the line number of the tram
     * @param voertuigNr the vehicle number of the tram
    * @return A unique tram with a given line number and vehicle number
    */
    Tram* retrieveTram(const int &lijnNr, const int &voertuigNr) const;

    /**
    * @brief Checks if a tram with a given line number exists
    * @param lijnNr the line number of the tram that is to be checked
    * @return A boolean denoting if the tram exists
    */
    bool tramExists(const int &lijnNr) const;

    /**
     * @brief Simulates circulating of trams on the metronet
     * @param steps durationInSeconds number of steps (1 step/sec) made by all trams
     * @pre steps > 0
     * @pre Metronet is consistent
     * @post Successful simulation with no errors
     */
    void autoSimulate(const unsigned int &steps);
};


#endif //PROJECT_SOFTWARE_PRACTICUM2_METRONET_H