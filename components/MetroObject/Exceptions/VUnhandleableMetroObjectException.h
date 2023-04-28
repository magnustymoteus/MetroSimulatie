//
// Created by gruzi on 26/04/2023.
//

#ifndef PROJECT_SOFTWARE_PRACTICUM2_VUNHANDLEABLEMETROOBJECTEXCEPTION_H
#define PROJECT_SOFTWARE_PRACTICUM2_VUNHANDLEABLEMETROOBJECTEXCEPTION_H

#include "IMetroObjectException.h"

class VUnhandleableMetroObjectException : public IMetroObjectException {
public:
    VUnhandleableMetroObjectException(const char* msg) {message=msg;}
    virtual const char* what() const throw() {
        return message;
    }
};


#endif //PROJECT_SOFTWARE_PRACTICUM2_VUNHANDLEABLEMETROOBJECTEXCEPTION_H
