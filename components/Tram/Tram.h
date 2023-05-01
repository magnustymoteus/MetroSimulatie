//
// Created by gruzi on 06/03/2023.
//

#ifndef PROJECT_SOFTWARE_PRACTICUM2_TRAM_H
#define PROJECT_SOFTWARE_PRACTICUM2_TRAM_H

#include "MetroObject/IMetroObject.h"
#include "Station/Station.h"
#include "Tram/TramType/TramType.h"

/**
 * @brief This serves as a Tram in a metro.
 * @author Patryk Pilichowski
 * @author Daria Matviichuk
 * @date 06/03/2023
 * @version 0.1
 */

class Tram : public IMetroObject {
private:
    Tram* _initCheck;
protected:
    /**
     * @brief The line number which must correspond to a track number
     */
    int fLijnNr;
    /**
     * @brief The vehicle number which must be unique if multiple trams have the same line number
     */
    int fVoertuigNr;
    /**
     * @brief The type of the tram
     */
    TramType* fType;
    /**
     * @brief The starting station
     */
    Station* fBeginStation;
    /**
     * @brief The current station
     */
    Station* fHuidigeStation;

    /**
     * @brief How many stations it takes in a simulation before the tram is defective and must be repaired
     */
    int fAantalDefecten;
    /**
     * @brief How many simulation steps it takes before the tram is repaired when it's defective
     */
    int fReparatieTijd;
public:
    bool properlyInitialized() const;
    /**
     * @brief The constructor which initializes the line number, the vehicle number, defective and reparation steps
     * @param lijnNr the line number
     * @param voertuigNr the vehicle number
     * @param aantalDefecten the defective steps
     * @param reparatieTijd the reparation steps
     */
    Tram(const int &lijnNr, const int &voertuigNr, const int &aantalDefecten=0, const int &reparatieTijd=0);

    /**
     * @brief Returns the line number
     * @return the line number
     */
    int getLijnNr() const;
    /**
     * @brief Returns the starting station
     * @return the starting station
     */
    Station* getBeginStation() const;
    /**
     * @brief Returns the current station
     * @return the current station
     */
    Station* getHuidigeStation() const;
    /**
     * @brief Returns the type of the tram
     * @return the tram type
     */
    TramType* getType() const;
    /**
     * @brief Returns the vehicle number
     * @return the vehicle number
     */
    int getVoertuigNr() const;
    /**
     * @brief Returns the amount of defective steps
     * @return the amount of defective steps
     */
    int getAantalDefecten() const;
    /**
     * @brief Returns the amount of reparation steps
     * @return the amount of reparation steps
     */
    int getReparatieTijd() const;
    /**
    * @brief Returns the successor of the tram's current station
    * @return the successor of the tram's current station
    */
    Station* getVolgendeStation() const;
    /**
     * @brief Returns the predecessor of the tram's current station
     * @return the predecessor of the tram's current station
     */
    Station* getVorigeStation() const;


    /**
     * @brief Sets the amount of defective steps to a new value
     * @param newAantalDefecten the new value
     */
    void setAantalDefecten(const int &newAantalDefecten);
    /**
     * @brief Sets the amount of reparation steps to a new value
     * @param newReparatieTijd the new value
     */
    void setReparatieTijd(const int &newReparatieTijd);
    /**
     * @brief Sets the vehicle number to a new value
     * @param voertuigNr the new value
     */
    void setVoertuigNr(const int &voertuigNr);
    /**
     * @brief Sets the tram type to a new value
     * @param newType the new value
     */
    void setType(TramType* &newType);
    /**
     * @brief Sets the line number to a new value
     * @param newLijnNr The new value
     */
    void setLijnNr(const int &newLijnNr);
    /**
     * @brief Sets the starting station to a new value
     * @param newBeginStation the new value
     */
    void setBeginStation(Station* const &newBeginStation);
    /**
     * @brief Sets the current station to a new value
     * @param newHuidigeStation the new value
     */
    void setHuidigeStation(Station* newHuidigeStation);

    /**
     * @brief Moves the tram to its next supported station
     * @return amount of unsupported stations that were skipped by the tram
     */
    unsigned int move();
    /**
     * @brief Moves the tram to its next supported station steps times
     * @param steps amount of times to move the tram
     * @return amount of unsupported stations that were skipped by the tram
     * @pre steps >= 0
     */
    unsigned int move(const unsigned int &steps);
    /**
     * @brief Checks if the tram supports a certain station (type)
     * @param station the station
     * @return Boolean denoting if the tram supports the given station
     */
    bool supportsStation(const Station* const &station) const;
};


#endif //PROJECT_SOFTWARE_PRACTICUM2_TRAM_H
