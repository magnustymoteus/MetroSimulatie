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
    /**
     * @brief The constructor which initializes the line number, the vehicle number, defective and reparation steps
     * @post: Tram is properly initialised
     * @param lijnNr the line number
     * @param voertuigNr the vehicle number
     * @param aantalDefecten the defective steps
     * @param reparatieTijd the reparation steps
     * @param reparatieKost the reparation costs
     */
    PCC(const int &lijnNr, const int &voertuigNr,
        const int &aantalDefecten=0, const int &reparatieTijd=0, const double& reparatieKost=0);

};


#endif //METROSIMULATIE_PCC_H
