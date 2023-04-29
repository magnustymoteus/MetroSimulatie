//
// Created by gruzi on 25/04/2023.
//

#ifndef PROJECT_SOFTWARE_PRACTICUM2_IMETROOBJECTVALIDATOR_H
#define PROJECT_SOFTWARE_PRACTICUM2_IMETROOBJECTVALIDATOR_H

#include <iostream>


#include "IMetroObject.h"

#include "MetroObject/Exceptions/IMetroObjectException.h"
#include "MetroObject/Exceptions/VHandleableMetroObjectException.h"
#include "MetroObject/Exceptions/VUnhandleableMetroObjectException.h"

#include "DesignByContract.h"
#include "Expect.h"

class IMetroObjectValidator {
private:
protected:
    std::string configPath;
public:
    virtual std::string getInvalidationMessage(const std::string &error) const = 0;
    virtual bool validate() const = 0;
};


#endif //PROJECT_SOFTWARE_PRACTICUM2_IMETROOBJECTVALIDATOR_H
