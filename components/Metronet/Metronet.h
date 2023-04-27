//
// Created by gruzi on 12/03/2023.
//

#ifndef PROJECT_SOFTWARE_PRACTICUM2_METRONET_H
#define PROJECT_SOFTWARE_PRACTICUM2_METRONET_H

#include "Station/Station.h"
#include "Tram/Tram.h"

class MetronetValidator; // forward declaration

/**
 * This serves as the Metronet, containing all information about the stations and trams.
 * @author Patryk Pilichowski
 * @author Daria Matviichuk
 * @date 12/03/2023
 * @version 0.1
 */

class Metronet : IMetroObject {
private:
    Metronet* _initCheck;
protected:
    std::map<std::string, Station*> fStations; // a map that holds begin stations for each Tram path (spoorNr : Station*)
    std::multimap<int, Tram*> fTrams; // a map that holds all trams (lijnNr : Tram*)
    std::map<std::string, TramType*> fTramTypes;
public:
    bool properlyInitialized() const;

    std::multimap<int, Tram*> getTrams() const;
    Tram* getTram(const int &lijnNr, const int &voertuigNr) const;
    std::map<std::string, Station*> getStations() const;
    std::map<std::string, TramType*> getTramTypes () const;

    void setTrams(std::multimap<int, Tram*> &newTrams);
    void setStations(std::map<std::string, Station*> &newStations);
    void setTramTypes(std::map<std::string, TramType *> newTramTypes);


    Metronet(std::map<std::string, Station*> &newStations, std::multimap<int, Tram*> &newTrams);
    Metronet();
    ~Metronet();

    void moveTram(const int &lijnNr, const int &voertuigNr, const int &steps=1);

    void pushStation(Station* station);
    void pushTram(Tram* tram);

    Station* retrieveStation(const std::string &naam) const;
    bool tramExists(const int &lijnNr) const;

    void autoSimulate(const int &durationInSeconds);
};


#endif //PROJECT_SOFTWARE_PRACTICUM2_METRONET_H
