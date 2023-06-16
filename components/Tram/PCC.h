//
// Created by gruzi on 16/06/2023.
//

#ifndef METROSIMULATIE_PCC_H
#define METROSIMULATIE_PCC_H

#include "Tram.h"

class PCC :  public Tram {
private:
    PCC* _initCheck;
public:
    bool properlyInitialized() const;

    PCC(const int &lijnNr, const int &voertuigNr,
        const int &aantalDefecten=0, const int &reparatieTijd=0);
};


#endif //METROSIMULATIE_PCC_H
