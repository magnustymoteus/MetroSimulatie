//
// Created by gruzi on 06/03/2023.
//

#ifndef PROJECT_SOFTWARE_PRACTICUM2_STATION_H
#define PROJECT_SOFTWARE_PRACTICUM2_STATION_H

#include <string>

/**
 * This serves as a metro station.
 * @author Patryk Pilichowski
 * @author Daria Matviichuk
 * @date 06/03/2023
 * @version 0.1
 */

class Station {
protected:
    Station* _initCheck;
    std::string fNaam;
    std::string fType;
    int fSpoorNr;
    Station *fVorige;
    Station *fVolgende;

public:
    bool properlyInitialized() const;
    Station();
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
