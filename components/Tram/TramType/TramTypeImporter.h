//
// Created by gruzi on 25/04/2023.
//

#ifndef PROJECT_SOFTWARE_PRACTICUM2_TRAMTYPEIMPORTER_H
#define PROJECT_SOFTWARE_PRACTICUM2_TRAMTYPEIMPORTER_H

#include "Utils/VMetroObjectImporter.h"
#include "Tram/TramType/TramType.h"


const std::string tramType_defaultConfigPath = "components/Tram/TramType/config_tramType.xml";
const std::string defaultTramTypesPath = "components/Tram/TramType/tramTypes.xml";

class TramTypeImporter : protected VMetroObjectImporter {
private:
    TramTypeImporter* _initCheck;
    std::vector<TramType*> fSupportedTramTypes;
    std::string fTramTypesPath;
public:
    TramTypeImporter(const std::string &configPath=tramType_defaultConfigPath,
                     const std::string &tramTypesPath=defaultTramTypesPath);
    bool properlyInitialized() const;

    void loadSupportedTramTypes();

    TramType* getSupportedTramTypeByName(const std::string &tramTypeName) const;

    TramType* parse(TiXmlElement* tramTypeElem) const;
};


#endif //PROJECT_SOFTWARE_PRACTICUM2_TRAMTYPEIMPORTER_H
