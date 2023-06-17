//
// Created by gruzi on 16/06/2023.
//

#ifndef METROSIMULATIE_ALBATROS_H
#define METROSIMULATIE_ALBATROS_H

#include "StandardTram.h"

class Albatros : public StandardTram {
private:
    Albatros* _initCheck;
public:
    bool properlyInitialized() const;
    /**
     * @brief The constructor which initializes the line number, the vehicle number, defective and reparation steps
     * @post: Tram is properly initialised
     * @param lijnNr the line number
     * @param voertuigNr the vehicle number
     */
    Albatros(const int &lijnNr, const int &voertuigNr);
};


#endif //METROSIMULATIE_ALBATROS_H
