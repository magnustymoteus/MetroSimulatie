//
// Created by dasha on 18.06.2023.
//
#include "Station.h"

#ifndef METROSIMULATIE_HALTE_H
#define METROSIMULATIE_HALTE_H


class Halte: public Station {
private:
    Halte* _initCheck;
public:
    bool properlyInitialized() const;
    /**
     * @brief The constructor which initializes a station with the given name
     * @post: Station is properly initialised
     * @param naam the name of the station
     */
    Halte(const std::string &naam);
};


#endif //METROSIMULATIE_HALTE_H
