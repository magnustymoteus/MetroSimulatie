//
// Created by dasha on 18.06.2023.
//
#include "Station.h"

#ifndef METROSIMULATIE_METROSTATION_H
#define METROSIMULATIE_METROSTATION_H


class Metrostation: public Station {
private:
    Metrostation* _initCheck;
public:
    bool properlyInitialized() const;
    /**
      * @brief The constructor which initializes a station with the given name
      * @post: Station is properly initialised
      * @param naam the name of the station
     */
    Metrostation(const std::string &naam);
};


#endif //METROSIMULATIE_METROSTATION_H
