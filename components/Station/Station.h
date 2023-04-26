//
// Created by gruzi on 06/03/2023.
//

#ifndef PROJECT_SOFTWARE_PRACTICUM2_STATION_H
#define PROJECT_SOFTWARE_PRACTICUM2_STATION_H

#include <string>

#include "MetroObject/IMetroObject.h"

/**
 * This serves as a metro Station.
 * @author Patryk Pilichowski
 * @author Daria Matviichuk
 * @date 06/03/2023
 * @version 0.1
 */

class Station : public IMetroObject {
private:
    Station* _initCheck;
protected:
    std::string fNaam;
    std::string fType;
    int fSpoorNr;
    Station *fVorige;
    Station *fVolgende;

public:
    bool properlyInitialized() const;

    Station(const std::string &naam, const std::string &type, const int &spoorNr);

    // getters
    std::string getNaam() const;
    int getSpoorNr () const;
    Station* getVorige() const;
    Station* getVolgende() const;
    const std::string &getType() const;

    // setters
    void setNaam(const std::string &newNaam);
    void setSpoorNr(const int &newSpoorNr);
    void setVorige(Station* const &newVorige);
    void setVolgende(Station* const &newVolgende);
    void setType(const std::string &type);
};


#endif //PROJECT_SOFTWARE_PRACTICUM2_STATION_H
