//
// Created by gruzi on 26/04/2023.
//

#ifndef PROJECT_SOFTWARE_PRACTICUM2_IMETROOBJECTEXCEPTION_H
#define PROJECT_SOFTWARE_PRACTICUM2_IMETROOBJECTEXCEPTION_H

#include <exception>
/**
 * @brief This is an exception class that is thrown whenever an error occurs related to a (derived) instance of
 * IMetroObject
 *
 * @author Patryk Pilichowski
 * @author Daria Matviichuk
 * @date 30/04/2023
 * @version 0.1
 */

class IMetroObjectException : public std::exception {
protected:
    /**
     * @brief The custom message that is the reason for why the exception is thrown.
     */
    const char* message;
public:
    virtual const char * what() const throw() = 0;
};


#endif //PROJECT_SOFTWARE_PRACTICUM2_IMETROOBJECTEXCEPTION_H
