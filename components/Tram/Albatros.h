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

    Albatros(const int &lijnNr, const int &voertuigNr, TramType type);
};


#endif //METROSIMULATIE_ALBATROS_H
