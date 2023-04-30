//
// Created by gruzi on 26/04/2023.
//

#ifndef PROJECT_SOFTWARE_PRACTICUM2_VHANDLEABLEMETROOBJECTEXCEPTION_H
#define PROJECT_SOFTWARE_PRACTICUM2_VHANDLEABLEMETROOBJECTEXCEPTION_H

#include "IMetroObjectException.h"

/**
 * @brief This exception should be raised when a handleable error occurs related to an instance of IMetroObject
 * @details An exception is handleable when one of the following is true:
 *  - The program can carry on even without handling the exception
 *  - The program can carry on only after handling the exception
 * @author Patryk Pilichowski
 * @author Daria Matviichuk
 * @date 30/04/2023
 * @version 0.1
 */

class VHandleableMetroObjectException : public IMetroObjectException {
public:
    VHandleableMetroObjectException(const char* msg) {message=msg;}
    virtual const char* what() const throw() {
        return message;
    }
};


#endif //PROJECT_SOFTWARE_PRACTICUM2_VHANDLEABLEMETROOBJECTEXCEPTION_H
