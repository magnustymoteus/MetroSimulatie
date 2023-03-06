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
private:
    int fLijnNr;
    int fSnelheid;
    Station* fBeginStation;
public:
    int getLijnNr() const;
    int getSnelheid() const;
    Station* getBeginStation() const;

    void setLijnNr(const int &newLijnNr);
    void setSnelheid(const int &newSnelheid);
    void setBeginStation(Station* const &newBeginStation);
};


#endif //PROJECT_SOFTWARE_PRACTICUM2_TRAM_H
