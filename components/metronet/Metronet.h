//
// Created by gruzi on 12/03/2023.
//

#ifndef PROJECT_SOFTWARE_PRACTICUM2_METRONET_H
#define PROJECT_SOFTWARE_PRACTICUM2_METRONET_H

#include <map>
#include "station/Station.h"
#include "tram/Tram.h"


class MetronetValidator; // forward declaration

/**
 * This serves as the metronet, containing all information about the stations and trams.
 * @author Patryk Pilichowski
 * @author Daria Matviichuk
 * @date 12/03/2023
 * @version 0.1
 */

class Metronet {
protected:
    Metronet* _initCheck;
    std::map<int, Station*> fSporen; // a map that holds begin stations for each tram path (spoorNr : Station*)
    std::map<int, Tram*> fTrams; // a map that holds all trams (lijnNr : Tram*)

public:
    bool properlyInitialized() const;

    std::map<int, Tram*> getTrams() const;
    void setTrams(std::map<int, Tram*> &newTrams);

    std::map<int, Station*> getSporen() const;
    void setSporen(std::map<int, Station*> &newSporen);

    Metronet(std::map<int, Station*> &newSporen, std::map<int, Tram*> &newTrams);
    Metronet();
    ~Metronet();

    void moveTram(const int &lijnNr, const int &steps=1);

    void pushStation(Station* station);
    void pushTram(Tram* tram);
    void insertAfterStation(const std::string &vorigeNaam, Station* station);

    Station* retrieveStation(const int &spoorNr, const std::string &naam) const;
    bool spoorExists(const int &spoorNr) const;
    bool tramExists(const int &lijnNr) const;

    void autoSimulate(const int &durationInSeconds);
};


#endif //PROJECT_SOFTWARE_PRACTICUM2_METRONET_H
