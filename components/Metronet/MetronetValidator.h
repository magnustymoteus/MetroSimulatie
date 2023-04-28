//
// Created by gruzi on 15/03/2023.
//

#ifndef PROJECT_SOFTWARE_PRACTICUM2_METRONETVALIDATOR_H
#define PROJECT_SOFTWARE_PRACTICUM2_METRONETVALIDATOR_H

#include "MetroObject/IMetroObjectValidator.h"
#include "Exceptions/MetronetInconsistentException.h"

#include "Metronet.h"

/**
 * This serves as the Metronet validator, it checks for data consistency in the Metronet class.
 * @author Patryk Pilichowski
 * @author Daria Matviichuk
 * @date 15/03/2023
 * @version 0.1
 */

class MetronetValidator : IMetroObjectValidator {
private:
    MetronetValidator* _initCheck;
protected:
    const Metronet* const fMetronet;

    void noDuplicateTramsValidation() const;
public:
    MetronetValidator(const Metronet* const &metronet);

    bool properlyInitialized() const;

    std::string getInvalidationMessage(const std::string &error) const;
    void validate() const;
};


#endif //PROJECT_SOFTWARE_PRACTICUM2_METRONETVALIDATOR_H
