//
// Created by gruzi on 06/03/2023.
//

#ifndef PROJECT_SOFTWARE_PRACTICUM2_TRAM_H
#define PROJECT_SOFTWARE_PRACTICUM2_TRAM_H

#include "MetroObject/IMetroObject.h"
#include "Station/Station.h"

/**
 * @brief This serves as a Tram in a metro.
 * @author Patryk Pilichowski
 * @author Daria Matviichuk
 * @date 06/03/2023
 * @version 0.1
 */

enum TramType {TramType_PCC=1, TramType_Stadslijner=2, TramType_Albatros=3, TramType_Null=0};
std::string tramTypeToString(TramType type);
TramType stringToTramType(const std::string &typeStr);

class Tram : public IMetroObject {
private:
    Tram* _initCheck;
protected:
    /**
     * @brief The line number which must correspond to a track number
     */
    const int fLijnNr;
    /**
     * @brief The vehicle number which must be unique if multiple trams have the same line number
     */
    const int fVoertuigNr;

    /**
     * @brief The type of the tram
     */
    const TramType fType;
    /**
    * @brief The speed of the tram
    */
    const int fSnelheid;
    /**
    * @brief The stations that the tram type supports (can stop at)
    */
    const std::vector<std::string> fBediendeStationTypes;
    /**
    * @brief How many stations it takes in a simulation before the tram is defective and must be repaired
    */
    const int fAantalDefecten;
    /**
     * @brief How many simulation steps it takes before the tram is repaired when it's defective
     */
    const int fReparatieTijd;
    /**
     * @brief Shows if the tram is now on reparation
     */
    bool fDefect;
    /**
    * @brief The starting station
    */
    Station*  fBeginStation;
    /**
    * @brief The reparation cost
    */
    double fReparatieKost;
    /**
    * @brief The total reparation cost
    */
    double fTotaleReparatieKost;
    /**
     * @brief The current station
     */
    Station* fHuidigeStation;
public:
    bool properlyInitialized() const;
    /**
     * @brief The constructor which initializes the line number, the vehicle number, defective and reparation steps
     * @post: Tram is properly initialised
     * @param lijnNr the line number
     * @param voertuigNr the vehicle number
     * @param aantalDefecten the defective steps
     * @param reparatieTijd the reparation steps
     */
    Tram(const int &lijnNr, const int &voertuigNr, TramType type, const int &snelheid,
         const std::vector<std::string> &bediendeStationTypes, const int &aantalDefecten, const int &reparatieTijd);

    /**
     * @brief Returns the line number
     * @pre: Tram is properly initialised
     * @post: Tram is unchanged
     * @return the line number
     */
    int getLijnNr() const;
    /**
     * @brief Returns the current station
     * @pre: Tram is properly initialised
     * @post: Tram is unchanged
     * @return the current station
     */
    Station* getHuidigeStation() const;
    /**
     * @brief Returns the type of the tram
     * @pre: Tram is properly initialised
     * @post: Tram is unchanged
     * @return the tram type
     */
    TramType getType() const;
    /**
     * @brief Returns the starting station
     * @pre: Tram is properly initialised
     * @post: Tram is unchanged
     * @return the starting station
     */
    Station* getBeginStation() const;
    /**
     * @brief Returns the vehicle number
     * @pre: Tram is properly initialised
     * @post: Tram is unchanged
     * @return the vehicle number
     */
    int getVoertuigNr() const;
    /**
    * @brief Returns the successor of the tram's current station
    * @pre: Tram is properly initialised
    * @post: Tram is unchanged
    * @return the successor of the tram's current station
    */
    Station* getVolgendeStation() const;
    /**
     * @brief Returns the predecessor of the tram's current station
     * @pre: Tram is properly initialised
     * @post: Tram is unchanged
     * @return the predecessor of the tram's current station
     */
    Station* getVorigeStation() const;
    /**
    * @brief Returns all supported station types
    * @pre: Tram is properly initialised
    * @post: Tram is unchanged
    * @return All station types supported by this tram type
    */
    std::vector<std::string> getBediendeStationTypes() const;
    /**
     * @brief Returns the costs for tram reparation
     * @pre: Tram is properly initialised
     * @post: Tram is unchanged
     * @return Reparation costs
     */
    double getReparatieKost() const;
    /**
     * @brief Returns the total costs after all tram reparations
     * @pre: Tram is properly initialised
     * @post: Tram is unchanged
     * @return Total reparation costs
     */
    double getTotaleReparatieKost() const;
    /**
    * @brief Increases the total repation cots of the tram
    * @pre: Tram is properly initialised
    * @post: Tram total repation costs have increased
    * @return the amount of defective steps
    */
    void increaseTotaleReparatieKost();
    /**
    * @brief Returns the amount of defective steps
    * @pre: Tram is properly initialised
    * @post: Tram is unchanged
    * @return the amount of defective steps
    */
    int getAantalDefecten() const;
    /**
     * @brief Returns the amount of reparation steps
     * @pre: Tram is properly initialised
     * @post: Tram is unchanged
     * @return the amount of reparation steps
     */
    int getReparatieTijd() const;
    /**
    * @brief Returns the speed of the tram
    * @pre: Tram is properly initialised
    * @post: Tram is unchanged
    * @return The speed
    */
    int getSnelheid() const;
    /**
    * @brief Checks of the tram is defect
    * @pre: Tram is properly initialised
    * @post: Tram is unchanged
    * @return Is tram on reparation now
    */
    bool isDefect() const;
    /**
    * @brief Sets if the trams is defect
    * @pre: Tram is properly initialised
    * @post: The given tram defect status is set
    * @param defect Defect status to set
    */
    void setDefect(bool defect);
    /**
     * @brief Sets the starting station to a new value
     * @pre: Tram is properly initialised
     * @post: Tram is unchanged
     * @param newBeginStation the new value
     */
    void setBeginStation(Station* const &newBeginStation);
    /**
     * @brief Sets the current station to a new value
     * @pre: Tram is properly initialised
     * @post: The given station is set as begin station
     * @param newHuidigeStation the new value
     */
    void setHuidigeStation(Station* newHuidigeStation);
    /**
     * @brief Moves the tram to its next supported station
     * @pre: Tram is properly initialised
     * @post: Tram is on the next supported station
     * @return amount of unsupported stations that were skipped by the tram
     */
    unsigned int move();
    /**
     * @brief Moves the tram to its next supported station steps times
     * @param steps amount of times to move the tram
     * @return amount of unsupported stations that were skipped by the tram
     * @pre: Tram is properly initialised
     * @pre steps >= 0
     */
    unsigned int move(const unsigned int &steps);
    /**
     * @brief Checks if the tram supports a certain station (type)
     * @pre: Tram is properly initialised
     * @param station the station
     * @return Boolean denoting if the tram supports the given station
     */
    bool supportsStation(const Station* const &station) const;
};


#endif //PROJECT_SOFTWARE_PRACTICUM2_TRAM_H
