//
// Created by gruzi on 28/04/2023.
//

#ifndef PROJECT_SOFTWARE_PRACTICUM2_METRONETINCONSISTENTEXCEPTION_H
#define PROJECT_SOFTWARE_PRACTICUM2_METRONETINCONSISTENTEXCEPTION_H

#include "MetroObject/Exceptions/VHandleableMetroObjectException.h"

#include <string>

/**
 * @brief This serves as an exception that should be called whenever an instance of Metronet is inconsistent.
 * @details An instance of Metronet is inconsistent when any of the following are true:
 *  - A station has doesn't have a predecessor or a successor
 *  - A tram doesn't have a corresponding track
 *  - A track doesn't have a corresponding tram
 *  - The start station of a tram is invalid (unsupported, null, or not in metronet)
 *  - There are duplicate tracks
 *  - There are duplicate trams
 *
 * @author Patryk Pilichowski
 * @author Daria Matviichuk
 * @date 30/04/2023
 * @version 0.1
 */

class MetronetInconsistentException : public VHandleableMetroObjectException {
public:
    MetronetInconsistentException(const char * msg) : VHandleableMetroObjectException(msg) {}
    const char * what() const throw() {
        return message;
    }
};


#endif //PROJECT_SOFTWARE_PRACTICUM2_METRONETINCONSISTENTEXCEPTION_H
