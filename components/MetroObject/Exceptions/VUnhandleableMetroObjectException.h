//
// Created by gruzi on 26/04/2023.
//

#ifndef PROJECT_SOFTWARE_PRACTICUM2_VUNHANDLEABLEMETROOBJECTEXCEPTION_H
#define PROJECT_SOFTWARE_PRACTICUM2_VUNHANDLEABLEMETROOBJECTEXCEPTION_H

#include "IMetroObjectException.h"

/**
 * @brief This exception should be raised when a unhandleable error occurs related to an instance of IMetroObject
 * @details An exception is unhandleable when the following is true:
 *  - Unlike a handleable exception, the program can't carry on because the exception cannot be handled
 * @author Patryk Pilichowski
 * @author Daria Matviichuk
 * @date 30/04/2023
 * @version 0.1
 */

class VUnhandleableMetroObjectException : public IMetroObjectException {
public:
    VUnhandleableMetroObjectException(const char* msg) {message=msg;}
    virtual const char* what() const throw() {
        return message;
    }
};


#endif //PROJECT_SOFTWARE_PRACTICUM2_VUNHANDLEABLEMETROOBJECTEXCEPTION_H
