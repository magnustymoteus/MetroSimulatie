//
// Created by gruzi on 12/03/2023.
//

#ifndef PROJECT_SOFTWARE_PRACTICUM2_METRONET_H
#define PROJECT_SOFTWARE_PRACTICUM2_METRONET_H

#include <map>
#include "../station/Station.h"
#include "../tram/Tram.h"

/**
 * This serves as the metronet, containing all information about the stations and trams.
 * @author Patryk Pilichowski
 * @author Daria Matviichuk
 * @date 12/03/2023
 * @version 0.1
 */
class Metronet {
private:
    std::map<int, Station*> fSporen; // a map that holds begin stations for each tram path (spoorNr : Station*)
    std::map<int, Tram*> fTrams; // a map that holds all trams (lijnNr : Tram*)
public:
    Metronet(std::map<int, Station*> &newSporen, std::map<int, Tram*> &newTrams);
    ~Metronet();
    void pushStation(Station* station);
    void pushTram(Tram* tram);
    Station* retrieveStation(const int &spoorNr, const std::string &naam) const;
    void insertAfterStation(const std::string &vorigeNaam, Station* station);
    bool spoorExists(const int &spoorNr) const;
    Metronet() {}
    void outputFile() const;
};


#endif //PROJECT_SOFTWARE_PRACTICUM2_METRONET_H
