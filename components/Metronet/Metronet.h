//
// Created by gruzi on 12/03/2023.
//

#ifndef PROJECT_SOFTWARE_PRACTICUM2_METRONET_H
#define PROJECT_SOFTWARE_PRACTICUM2_METRONET_H

#include "Station/Station.h"
#include "Tram/Tram.h"
#include <set>

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
    Metronet *_initCheck;
protected:
    /**
    * @brief All stations of the metronet
    */
    std::map<std::string, Station *> fStations; // stations (name : Station*)
    /**
    * @brief All trams of the metronet
    */
    std::multimap<int, Tram *> fTrams; // a map that holds all trams (lijnNr : Tram*)
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
    std::multimap<int, Tram *> getTrams() const;

    /**
    * @brief Gets the stations of the metronet
    * @pre: Metronet is properly initialised
    * @return the stations of the metronet
    */
    std::map<std::string, Station *> getStations() const;

    /**
    * @brief Returns the consistency of the metronet
    * @pre: Metronet is properly initialised
    * @return a boolean denoting the consistency of the metronet
    */
    bool getIsConsistent() const;

    /**
    * @brief Sets trams to a new value
    * @pre: Metronet is properly initialised
    * @param newTrams the new value
    */
    void setTrams(std::multimap<int, Tram *> &newTrams);

    /**
    * @brief Sets stations to a new value
    * @pre: Metronet is properly initialised
    * @param newStations the new value
    */
    void setStations(std::map<std::string, Station *> &newStations);


    /**
    * @brief Sets isConsistent to a new value
    * @pre: Metronet is properly initialised
    * @param newIsConsistent the new value
    */
    void setIsConsistent(const bool &newIsConsistent);

    /**
    * @brief Get the tram currently stopping at a station
    * @param stationName the name of the station
     *@param spoorNr the track number of the station
     * @return Tram pointer denoting the tram currently stopping on the station
     * @pre: Metronet is properly initialised
     * @pre Station is valid
     * @pre Station has the given track number
    */
    Tram* getTramOnStation(const std::string &stationName, const int &spoorNr) const;
    /**
    * @brief Checks if there is a tram currently stopping at a station
    * @param stationName the name of the station
     *@param spoorNr the track number of the station
     * @return Boolean denoting if there is a tram currently stopping on a station
     * @pre: Metronet is properly initialised
     * @pre Station is valid
     * @pre Station has the given track number
    */
    bool isTramOnStation(const std::string &stationName, const int &spoorNr) const;

    /**
    * @brief Initializes metronet
    * @pre: Metronet is properly initialised
    * @param newStations the new stations of the metronet
     *@param newTrams the new trams of the metronet
    */
    Metronet(std::map<std::string, Station *> &newStations, std::multimap<int, Tram *> &newTrams);

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
    * @pre: Metronet is properly initialised
    * @pre steps > 0
    * @post Successfully moved the tram to the next supporting station n times
    */
    void moveTram(Tram *&tram, const unsigned int &steps = 1) const;

    /**
    * @brief Adds a station to the metronet
    * @param station The station that must be added
    * @pre: Metronet is properly initialised
    * @post new Station instance has been added to the stations
    */
    void pushStation(Station *station);

    /**
    * @brief Adds a tram to the metronet
    * @pre: Metronet is properly initialised
    * @param tram the tram that must be added
    * @post new Tram instance has been added to the trams
    */
    void pushTram(Tram *tram);

    /**
    * @brief Adds a tram to the metronet
    * @pre: Metronet is properly initialised
    * @param tram the tram that must be added
     *@post new Tram instance has been added to the trams
    */
    void pushSpoor(const std::string &stationName, const int &spoorNr, const std::pair<Station *, Station *> &newSpoor);

    /**
    * @brief Retrieves a station
    * @pre: Metronet is properly initialised
    * @param naam the name of the station
    * @return A unique station
    */

    Station *retrieveStation(const std::string &naam) const;

    /**
    * @brief Retrieves a tram
    * @pre: Metronet is properly initialised
    * @param lijnNr the line number of the tram
    * @param voertuigNr the vehicle number of the tram
    * @return A unique tram with a given line number and vehicle number
    */
    Tram *retrieveTram(const int &lijnNr, const int &voertuigNr) const;

    /**
    * @brief Checks if a tram with a given line number exists
    * @pre: Metronet is properly initialised
    * @param lijnNr the line number of the tram that is to be checked
    * @return A boolean denoting if the tram exists
    */
    bool tramExists(const int &lijnNr) const;

    /**
    * @brief Checks if a spoor with a given line number exists
    * @pre: Metronet is properly initialised
    * @param lijnNr the line number of the spoor that is to be checked
    * @return A boolean denoting if the spoor exists
    */
    bool spoorExists(const int &lijnNr) const;

    /**
     * @brief Simulates circulating of trams on the metronet
     * @param steps durationInSeconds number of steps (1 step/sec) made by all trams
     * @param printRapportOn does the rapport has to be printed
     * @pre: Metronet is properly initialised
     * @pre steps > 0
     * @pre Metronet is consistent
     * @post Successful simulation with no errors
     */
    void autoSimulate(const unsigned int &steps, bool printRapportOn=true);
    /**
     * @brief Prints the rapport of the metronet after simulation
     * @pre: Metronet is properly initialised
     * @pre Metronet is consistent
     * @post Metronet is unchanged
     */
    void printRapport() const;
    /**
     * @brief Gets all station types in the current metronet
     * @pre: Metronet is properly initialised
     * @pre Metronet is consistent
     * @post Metronet is unchanged
     */
    std::set<std::string> getStationTypes() const;
    /**
     * @brief Gets all tram types in the current metronet
     * @pre: Metronet is properly initialised
     * @pre Metronet is consistent
     * @post Metronet is unchanged
     */
    std::set<std::string> getTramTypes() const;
    /**
     * @brief Gets number of stations with the given type
     * @pre: Metronet is properly initialised
     * @pre Metronet is consistent
     * @post Metronet is unchanged
     * @return Number of stations with the given type
     */
    int getNumberOfStationsWithGivenType(const std::string& stationType) const;
    /**
     * @brief Gets number of trams with the given type
     * @pre: Metronet is properly initialised
     * @pre Metronet is consistent
     * @post Metronet is unchanged
     * @return Number of trams with the given type
     */
    int getNumberOfTramsWithGivenType(const std::string& tramType) const;
    /**
     * @brief Gets stations with the given type
     * @pre: Metronet is properly initialised
     * @pre Metronet is consistent
     * @post Metronet is unchanged
     * @return Set of pointers to stations with the given type
     */
    std::set<Station*> getStationsWithGivenType(const std::string& stationType) const;
    /**
     * @brief Gets stations with the given type
     * @pre: Metronet is properly initialised
     * @pre Metronet is consistent
     * @post Metronet is unchanged
     * @return Set of pointers to stations with the given type
     */
    std::set<Tram*> getTramsWithGivenType(const std::string& tramType) const;
    /**
     * @brief Returns number of stations on the give line
     * @pre: Metronet is properly initialised
     * @pre Metronet is consistent
     * @post Metronet is unchanged
     * @return Returns number of stations on the give line
     */
    int getNumberOfStations(int lijnNr) const;
    /**
     * @brief Gets all line numbers
     * @pre: Metronet is properly initialised
     * @pre Metronet is consistent
     * @post Metronet is unchanged
     * @return Set of numbers of line numbers with the given type
     */
    std::set<int> getAllLineNrs() const;
    /**
     * @brief Generates an ini of the metronet in output/GeneratedImages
     * @pre: Metronet is properly initialised
     * @pre Metronet is consistent
     * @post Metronet is unchanged
     * @return Path to the generated ini file
     */
    std::string generateIni() const;
    /**
     * @brief Simulates circulating of trams on the metronet
     * @param steps number of steps made by all trams
     * @pre: Metronet is properly initialised
     * @pre steps > 0
     * @pre Metronet is consistent
     * @post Successful simulation with no errors
     */
    void graphicalSimulation(const unsigned int &steps);
};
#endif //PROJECT_SOFTWARE_PRACTICUM2_METRONET_H
