//
// Created by gruzi on 28/04/2023.
//

#ifndef PROJECT_SOFTWARE_PRACTICUM2_METRONETINCONSISTENTEXCEPTION_H
#define PROJECT_SOFTWARE_PRACTICUM2_METRONETINCONSISTENTEXCEPTION_H

#include "MetroObject/Exceptions/VHandleableMetroObjectException.h"

#include <string>

class MetronetInconsistentException : public VHandleableMetroObjectException {
public:
    MetronetInconsistentException(const char * msg) : VHandleableMetroObjectException(msg) {}
    const char * what() const throw() {
        return message;
    }
};


#endif //PROJECT_SOFTWARE_PRACTICUM2_METRONETINCONSISTENTEXCEPTION_H
