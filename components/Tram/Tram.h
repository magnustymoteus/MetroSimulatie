//
// Created by gruzi on 06/03/2023.
//

#ifndef PROJECT_SOFTWARE_PRACTICUM2_TRAM_H
#define PROJECT_SOFTWARE_PRACTICUM2_TRAM_H

#include "MetroObject/IMetroObject.h"
#include "Station/Station.h"
#include "Tram/TramType/TramType.h"

/**
 * @brief This serves as a Tram in a metro.
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

    int fAantalDefecten;
    int fReparatieTijd;
public:
    Tram(const int &lijnNr, const int &voertuigNr, const int &aantalDefecten=0, const int &reparatieTijd=0);
    bool properlyInitialized() const;

    int getLijnNr() const;
    Station* getBeginStation() const;
    Station* getHuidigeStation() const;
    TramType* getType() const;
    int getVoertuigNr() const;
    int getAantalDefecten() const;
    int getReparatieTijd() const;


    void setAantalDefecten(const int &newAantalDefecten);
    void setReparatieTijd(const int &newReparatieTijd);
    void setVoertuigNr(const int &voertuigNr);
    void setType(TramType* &newType);
    void setLijnNr(const int &newLijnNr);
    void setBeginStation(Station* const &newBeginStation);
    void setHuidigeStation(Station* newHuidigeStation);
    Station* getVolgendeStation() const;
    Station* getVorigeStation() const;

    unsigned int move();
    unsigned int move(const unsigned int &steps);
    bool supportsStation(const Station* const &station) const;
};


#endif //PROJECT_SOFTWARE_PRACTICUM2_TRAM_H
