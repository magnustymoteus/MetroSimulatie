//
// Created by gruzi on 15/03/2023.
//

#ifndef PROJECT_SOFTWARE_PRACTICUM2_METRONETVALIDATOR_H
#define PROJECT_SOFTWARE_PRACTICUM2_METRONETVALIDATOR_H

#include "MetroObject/IMetroObjectValidator.h"
#include "Exceptions/MetronetInconsistentException.h"

#include "Metronet.h"

/**
 * @brief This serves as the Metronet validator, it checks for any inconsistencies but also errors in the Metronet class
 * @author Patryk Pilichowski
 * @author Daria Matviichuk
 * @date 15/03/2023
 * @version 0.1
 */

class MetronetValidator : IMetroObjectValidator {
private:
    MetronetValidator* _initCheck;
protected:
    /**
     * @brief a Metronet instance that we want to validate whenever we want to
     * */
    const Metronet* const fMetronet;

    /**
     * @brief Checks if there are trams with the same line number and vehicle number
     * @return a boolean denoting if there are any duplicate trams in the metronet
     * */
    bool noDuplicateTrams() const;
    /**
    * @brief Checks if all stations have a predecessor and a successor
    * @return a boolean denoting if the stations are properly linked
    * */
    bool stationsLinked() const;
    /**
    * @brief Checks if for all trams there exists a station if the same track number as their line number
    * @return a boolean denoting if all trams have their track
    * */
    bool tramsHaveSpoor() const;
    /**
    * @brief Checks if for all tracks there exists a tram with the same line number as their track number
    * @return a boolean denoting if all tracks have their tram
    * */
    bool sporenHaveTrams() const;
    /**
    * @brief Checks if all trams have a start station that exists in the metronet but also if the station itself is
     * supported by the type of that tram.
    * @return a boolean denoting if all trams have a valid start station
    * */
    bool tramsHaveValidBeginStation() const;
    /**
    * @brief For all trams calls the function validate() of a TramValidator instance
    * */
    void validateTrams() const;
public:
    bool properlyInitialized() const;

    /**
    * @brief Constructor of the MetronetValidator instance
     * @param metronet The instance of Metronet that we want to validate
    * */
    MetronetValidator(const Metronet* const &metronet);

    /**
    * @brief Returns a string of the message in case validation failed
     * @param error A custom message telling what exactly went wrong
     * @return A string denoting failure of validation of a Metronet instance
    * */
    std::string getInvalidationMessage(const std::string &error) const;
    /**
    * @brief Validates an instance of Metronet
     * @return A boolean denoting if the Metronet instance is valid or not
    * */
    bool validate() const;
};


#endif //PROJECT_SOFTWARE_PRACTICUM2_METRONETVALIDATOR_H
