//
// Created by gruzi on 16/06/2023.
//

#ifndef METROSIMULATIE_STANDARDTRAM_H
#define METROSIMULATIE_STANDARDTRAM_H

#include "Tram.h"

class StandardTram : public Tram {
private:
    StandardTram* _initCheck;
public:
    bool properlyInitialized() const;

    StandardTram(const int &lijnNr, const int &voertuigNr, TramType type);
};


#endif //METROSIMULATIE_STANDARDTRAM_H
