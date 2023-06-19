//
// Created by gruzi on 27/04/2023.
//

#ifndef PROJECT_SOFTWARE_PRACTICUM2_STATIONVALIDATOR_H
#define PROJECT_SOFTWARE_PRACTICUM2_STATIONVALIDATOR_H


#include "MetroObject/IMetroObjectValidator.h"

#include "Station.h"

/**
 * @brief A validator for Station
 * @author Patryk Pilichowski
 * @author Daria Matviichuk
 * @date 06/03/2023
 * @version 0.1
 */

class StationValidator : public IMetroObjectValidator {
private:
    StationValidator* _initCheck;
protected:
    const Station* const fStationObject;
public:
    StationValidator(const Station* const &stationObject);

    const Station* getStationObject() const;

    bool properlyInitialized() const;


    std::string getInvalidationMessage(const std::string &error) const;

    bool validate() const;
};


#endif //PROJECT_SOFTWARE_PRACTICUM2_STATIONVALIDATOR_H
