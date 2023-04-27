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

    std::map<int, std::pair<Station*, Station*> > fSporen; // spoorNr : (vorige, volgende)

    Station *fVorige;
    Station *fVolgende;

public:
    bool properlyInitialized() const;

    Station(const std::string &naam, const std::string &type);

    // getters
    std::string getNaam() const;
    Station* getVorige(const int &spoorNr) const;
    Station* getVolgende(const int &spoorNr) const;
    const std::string &getType() const;
    std::map<int, std::pair<Station*, Station*> > getSporen() const;
    std::pair<Station*, Station*> getSpoor(const int &spoorNr) const;

    // setters
    void setNaam(const std::string &newNaam);
    void setVorige(const int &spoorNr, Station* const &newVorige);
    void setVolgende(const int &spoorNr, Station* const &newVolgende);
    void setType(const std::string &type);
    void setSporen(const std::map<int, std::pair<Station*, Station*> > &newSporen);
    void setSpoor(const int &spoorNr, const std::pair<Station*, Station*> &newSpoor);
};


#endif //PROJECT_SOFTWARE_PRACTICUM2_STATION_H
