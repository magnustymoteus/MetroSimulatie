//
// Created by gruzi on 27/04/2023.
//

#ifndef PROJECT_SOFTWARE_PRACTICUM2_STATIONVALIDATOR_H
#define PROJECT_SOFTWARE_PRACTICUM2_STATIONVALIDATOR_H


#include "MetroObject/IMetroObjectValidator.h"

#include "Station.h"

class StationValidator : public IMetroObjectValidator {
private:
    StationValidator* _initCheck;
protected:
    const Station* const fStationObject;
public:
    StationValidator(const Station* const &stationObject);

    bool properlyInitialized() const;


    std::string getInvalidationMessage(const std::string &error) const;

    //void validate() const;
};


#endif //PROJECT_SOFTWARE_PRACTICUM2_STATIONVALIDATOR_H
