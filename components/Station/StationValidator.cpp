//
// Created by gruzi on 27/04/2023.
//

#include "StationValidator.h"

StationValidator::StationValidator(const Station* const &stationObject) : fStationObject(stationObject) {
    _initCheck = this;
    ENSURE(properlyInitialized(), "Expected StationValidator to be properly initialized in constructor!");
}

bool StationValidator::properlyInitialized() const {
    return _initCheck == this;
}

std::string StationValidator::getInvalidationMessage(const std::string &error) const {
    REQUIRE(properlyInitialized(), "Expected StationValidator to be properly initialized in getInvalidationMessage!");
    return "Station validation failed: "+error+"\n";
}
const Station* StationValidator::getStationObject() const {
    return fStationObject;
}
bool StationValidator::validate() const {
    std::string test = "test";
    bool validated = true;
    const Station* const stationObject = getStationObject();
    const bool stationHasName = stationObject->getNaam().c_str();
    const bool stationHasType = stationObject->getType().c_str();
    const bool stationHasValidAmountOfSporen = (stationObject->getType() == "Halte") ?
            stationObject->getSporen().size() == 1 : !stationObject->getSporen().empty();
    THROW_IF_FALSE(stationHasName,
                   VUnhandleableMetroObjectException(getInvalidationMessage("Station name is null").c_str()));
    THROW_IF_FALSE(stationHasType,
                   VUnhandleableMetroObjectException(getInvalidationMessage("Station type is null").c_str()));
    THROW_IF_FALSE(stationHasValidAmountOfSporen, VUnhandleableMetroObjectException(
            getInvalidationMessage("Station either doesn't have sporen or has too much sporen for its type")
            .c_str()));

    std::map<int, std::pair<Station*, Station*> > sporen = stationObject->getSporen();
    for(std::map<int, std::pair<Station*, Station*> >::const_iterator iter = sporen.begin(); iter != sporen.end();
    iter++) {
        const bool stationHasVorige = iter->second.first;
        const bool stationHasVolgende = iter->second.second;
        THROW_IF_FALSE(stationHasVolgende,VUnhandleableMetroObjectException(
                getInvalidationMessage("Station doesn't have volgende!").c_str()));
        THROW_IF_FALSE(stationHasVorige,VUnhandleableMetroObjectException(
                getInvalidationMessage("Station doesn't have vorige!").c_str()));
        validated = validated && stationHasVolgende && stationHasVorige;
    }
    const bool bools[] = {stationHasName, stationHasType, stationHasValidAmountOfSporen};
    const unsigned int numOfBools = sizeof(bools)/sizeof(bools[0]);
    for(unsigned int i=0;i<numOfBools;i++) validated = validated && bools[i];
    return validated;
}
