//
// Created by gruzi on 25/04/2023.
//

#ifndef PROJECT_SOFTWARE_PRACTICUM2_IMETROOBJECTVALIDATOR_H
#define PROJECT_SOFTWARE_PRACTICUM2_IMETROOBJECTVALIDATOR_H


#include "Utils/IMetroObject.h"

class IMetroObjectValidator {
public:
    virtual void validate(IMetroObject* object) const = 0;
};


#endif //PROJECT_SOFTWARE_PRACTICUM2_IMETROOBJECTVALIDATOR_H
