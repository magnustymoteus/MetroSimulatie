//
// Created by gruzi on 26/04/2023.
//

#ifndef PROJECT_SOFTWARE_PRACTICUM2_VHANDLEABLEMETROOBJECTEXCEPTION_H
#define PROJECT_SOFTWARE_PRACTICUM2_VHANDLEABLEMETROOBJECTEXCEPTION_H

#include "IMetroObjectException.h"

class VHandleableMetroObjectException : public IMetroObjectException {
public:
    VHandleableMetroObjectException(const char* msg) {message=msg;}
    virtual const char* what() const throw() {
        return message;
    }
};


#endif //PROJECT_SOFTWARE_PRACTICUM2_VHANDLEABLEMETROOBJECTEXCEPTION_H
