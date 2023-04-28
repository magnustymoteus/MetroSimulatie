//
// Created by gruzi on 26/04/2023.
//

#ifndef PROJECT_SOFTWARE_PRACTICUM2_IMETROOBJECTEXCEPTION_H
#define PROJECT_SOFTWARE_PRACTICUM2_IMETROOBJECTEXCEPTION_H

#include <exception>

class IMetroObjectException : public std::exception {
protected:
    const char* message;
public:
    virtual const char * what() const throw() = 0;
};


#endif //PROJECT_SOFTWARE_PRACTICUM2_IMETROOBJECTEXCEPTION_H
