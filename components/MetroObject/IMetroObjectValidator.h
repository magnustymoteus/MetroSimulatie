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
#include "IfFalse.h"


/**
 * @brief A validator for (derived) instances of IMetroObject
 * @author Patryk Pilichowski
 * @author Daria Matviichuk
 * @date 30/04/2023
 * @version 0.1
 */

class IMetroObjectValidator {
private:
protected:
    std::string configPath;
public:
    /**
   * @brief Returns a string of the message in case validation failed
    * @param error A custom message telling what exactly went wrong
    * @return A string denoting failure of validation of a Metronet instance
   * */
    virtual std::string getInvalidationMessage(const std::string &error) const = 0;
    /**
   * @brief Validates an instance of Metronet
    * @return A boolean denoting if the Metronet instance is valid or not
   * */
    virtual bool validate() const = 0;
};


#endif //PROJECT_SOFTWARE_PRACTICUM2_IMETROOBJECTVALIDATOR_H
