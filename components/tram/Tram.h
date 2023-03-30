//
// Created by gruzi on 06/03/2023.
//

#ifndef PROJECT_SOFTWARE_PRACTICUM2_TRAM_H
#define PROJECT_SOFTWARE_PRACTICUM2_TRAM_H
#include <string>

class Station; // forward declaration

/**
 * This serves as a tram in a metro.
 * @author Patryk Pilichowski
 * @author Daria Matviichuk
 * @date 06/03/2023
 * @version 0.1
 */

class Tram {
protected:
    Tram* _initCheck;

    int fLijnNr;
    int fSnelheid;
    int fVoertuigNr;
    std::string fType;
    Station* fBeginStation;
    Station* fHuidigeStation;


public:
    Tram();
    bool properlyInitialized() const;

    int getLijnNr() const;
    int getSnelheid() const;
    Station* getBeginStation() const;
    Station* getHuidigeStation() const;
    const std::string &getType() const;
    int getVoertuigNr() const;

    void setVoertuigNr(const int &voertuigNr);
    void setType(const std::string &type);
    void setLijnNr(const int &newLijnNr);
    void setSnelheid(const int &newSnelheid);
    void setBeginStation(Station* const &newBeginStation);
    void setHuidigeStation(Station* newHuidigeStation);
    Station* getVolgendeStation() const;
    Station* getVorigeStation() const;
    void moveNaarVolgendeStation();
};


#endif //PROJECT_SOFTWARE_PRACTICUM2_TRAM_H
