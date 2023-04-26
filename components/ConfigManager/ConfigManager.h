//
// Created by gruzi on 25/04/2023.
//

#ifndef PROJECT_SOFTWARE_PRACTICUM2_CONFIGFILES_H
#define PROJECT_SOFTWARE_PRACTICUM2_CONFIGFILES_H

#include <string>

const std::string station_defaultConfigPath = "components/Station/config_station.xml";
const std::string tramType_defaultConfigPath = "components/Tram/TramType/config_tramType.xml";
const std::string tram_defaultConfigPath = "components/Tram/config_tram.xml";

class ConfigManager {
public:
    static std::string StationConfig() {return station_defaultConfigPath;}
    static std::string TramTypeConfig() {return tramType_defaultConfigPath;}
    static std::string TramConfig() {return tram_defaultConfigPath;}
};


#endif //PROJECT_SOFTWARE_PRACTICUM2_CONFIGFILES_H


