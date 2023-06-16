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

    Stadslijner(const int &lijnNr, const int &voertuigNr, TramType type);
};


#endif //METROSIMULATIE_STADSLIJNER_H
