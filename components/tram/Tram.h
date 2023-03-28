//
// Created by gruzi on 06/03/2023.
//

#ifndef PROJECT_SOFTWARE_PRACTICUM2_TRAM_H
#define PROJECT_SOFTWARE_PRACTICUM2_TRAM_H


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
    Station* fBeginStation;
    Station* fHuidigeStation;


public:
    Tram();
    bool properlyInitialized() const;

    int getLijnNr() const;
    int getSnelheid() const;
    Station* getBeginStation() const;
    Station* getHuidigeStation() const;

    void setLijnNr(const int &newLijnNr);
    void setSnelheid(const int &newSnelheid);
    void setBeginStation(Station* const &newBeginStation);
    void setHuidigeStation(Station* newHuidigeStation);
    Station* getVolgendeStation() const;
    Station* getVorigeStation() const;
    void moveNaarVolgendeStation();
};


#endif //PROJECT_SOFTWARE_PRACTICUM2_TRAM_H
