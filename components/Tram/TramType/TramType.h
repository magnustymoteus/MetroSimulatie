//
// Created by gruzi on 25/04/2023.
//

#ifndef PROJECT_SOFTWARE_PRACTICUM2_TRAMTYPE_H
#define PROJECT_SOFTWARE_PRACTICUM2_TRAMTYPE_H

#include "MetroObject/IMetroObject.h"

class TramType : public IMetroObject {
private:
    TramType* _initCheck;
protected:
    std::string fNaam;
    int fSnelheid;
    std::vector<std::string> fBediendeStationTypes;
public:
    TramType(const std::string &newNaam, const int &newSnelheid,
             const std::vector<std::string> &newBediendeStationTypes);

    bool properlyInitialized() const;

    std::string getNaam() const;
    int getSnelheid() const;
    std::vector<std::string> getBediendeStationTypes();

    void setNaam(const std::string &newNaam);
    void setSnelheid(const int &newSnelheid);
    void setBediendeStationTypes(const std::vector<std::string> &newBediendeStationTypes);
};


#endif //PROJECT_SOFTWARE_PRACTICUM2_TRAMTYPE_H
