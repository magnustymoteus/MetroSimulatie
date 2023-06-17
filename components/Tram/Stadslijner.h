//
// Created by gruzi on 16/06/2023.
//

#ifndef METROSIMULATIE_STADSLIJNER_H
#define METROSIMULATIE_STADSLIJNER_H

#include "StandardTram.h"

class Stadslijner : public StandardTram {
private:
    Stadslijner* _initCheck;
public:
    bool properlyInitialized() const;
    /**
     * @brief The constructor which initializes the line number, the vehicle number, defective and reparation steps
     * @post: Tram is properly initialised
     * @param lijnNr the line number
     * @param voertuigNr the vehicle number
     */
    Stadslijner(const int &lijnNr, const int &voertuigNr);
};


#endif //METROSIMULATIE_STADSLIJNER_H
