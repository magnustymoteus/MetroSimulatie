//
// Created by gruzi on 06/03/2023.
//

#ifndef PROJECT_SOFTWARE_PRACTICUM2_TRAM_H
#define PROJECT_SOFTWARE_PRACTICUM2_TRAM_H

#include "MetroObject/IMetroObject.h"
#include "Station/Station.h"
#include "Tram/TramType/TramType.h"

/**
 * This serves as a Tram in a metro.
 * @author Patryk Pilichowski
 * @author Daria Matviichuk
 * @date 06/03/2023
 * @version 0.1
 */

class Tram : public IMetroObject {
private:
    Tram* _initCheck;
protected:
    int fLijnNr;
    int fVoertuigNr;
    TramType* fType;
    Station* fBeginStation;
    Station* fHuidigeStation;

public:
    Tram(const int &lijnNr, const int &voertuigNr);
    bool properlyInitialized() const;

    int getLijnNr() const;
    Station* getBeginStation() const;
    Station* getHuidigeStation() const;
    TramType* getType() const;
    int getVoertuigNr() const;

    void setVoertuigNr(const int &voertuigNr);
    void setType(TramType* &newType);
    void setLijnNr(const int &newLijnNr);
    void setBeginStation(Station* const &newBeginStation);
    void setHuidigeStation(Station* newHuidigeStation);
    Station* getVolgendeStation() const;
    Station* getVorigeStation() const;
    void moveNaarVolgendeStation();
};


#endif //PROJECT_SOFTWARE_PRACTICUM2_TRAM_H
