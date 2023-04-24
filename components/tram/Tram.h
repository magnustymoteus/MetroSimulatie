//
// Created by gruzi on 06/03/2023.
//

#ifndef PROJECT_SOFTWARE_PRACTICUM2_TRAM_H
#define PROJECT_SOFTWARE_PRACTICUM2_TRAM_H

#include <vector>
#include <string>

#include "utils/IMetroObject.h"

class Station; // forward declaration

/**
 * This serves as a tram in a metro.
 * @author Patryk Pilichowski
 * @author Daria Matviichuk
 * @date 06/03/2023
 * @version 0.1
 */

class Tram : public IMetroObject {
protected:
    Tram* _initCheck;

    int fLijnNr;
    int fSnelheid;
    int fVoertuigNr;
    std::string fType;
    Station* fBeginStation;
    Station* fHuidigeStation;
    std::vector<std::string> fBediendeStationTypes;

public:
    Tram(const int &lijnNr, const int &voertuigNr, const std::string &type);
    bool properlyInitialized() const;

    int getLijnNr() const;
    int getSnelheid() const;
    Station* getBeginStation() const;
    Station* getHuidigeStation() const;
    const std::string &getType() const;
    std::vector<std::string> getBediendeStationTypes() const;
    int getVoertuigNr() const;

    void setVoertuigNr(const int &voertuigNr);
    void setType(const std::string &type);
    void setBediendeStationTypes(const std::vector<std::string> &newBediendeStationTypes);
    void setLijnNr(const int &newLijnNr);
    void setSnelheid(const int &newSnelheid);
    void setBeginStation(Station* const &newBeginStation);
    void setHuidigeStation(Station* newHuidigeStation);
    Station* getVolgendeStation() const;
    Station* getVorigeStation() const;
    void moveNaarVolgendeStation();
};


#endif //PROJECT_SOFTWARE_PRACTICUM2_TRAM_H
