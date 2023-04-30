//
// Created by gruzi on 25/04/2023.
//

#ifndef PROJECT_SOFTWARE_PRACTICUM2_TRAMVALIDATOR_H
#define PROJECT_SOFTWARE_PRACTICUM2_TRAMVALIDATOR_H

#include "MetroObject/IMetroObjectValidator.h"

#include "Tram/Tram.h"

/**
 * @brief Validator for Tram
 * @author Patryk Pilichowski
 * @author Daria Matviichuk
 * @date 06/03/2023
 * @version 0.1
 */

class TramValidator : public IMetroObjectValidator {
private:
    TramValidator* _initCheck;
protected:
    const Tram* const fTramObject;
public:
    TramValidator(const Tram* const &tramObject);

    bool properlyInitialized() const;

    std::string getInvalidationMessage(const std::string &error) const;

    bool validate() const;
};


#endif //PROJECT_SOFTWARE_PRACTICUM2_TRAMVALIDATOR_H
