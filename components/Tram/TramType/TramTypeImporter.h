//
// Created by gruzi on 25/04/2023.
//

#ifndef PROJECT_SOFTWARE_PRACTICUM2_TRAMTYPEIMPORTER_H
#define PROJECT_SOFTWARE_PRACTICUM2_TRAMTYPEIMPORTER_H

#include "MetroObject/VMetroObjectImporter.h"
#include "Tram/TramType/TramType.h"

const std::string defaultTramTypesPath = "components/Tram/TramType/tramTypes.xml";

class TramTypeImporter : protected VMetroObjectImporter {
private:
    TramTypeImporter* _initCheck;
protected:
    std::map<std::string, TramType*> fSupportedTramTypes;
    std::string fTramTypesPath;
public:
    TramTypeImporter(const std::string &configPath=ConfigManager::TramTypeConfig(),
                     const std::string &tramTypesPath=defaultTramTypesPath);
    bool properlyInitialized() const;

    void loadSupportedTramTypes();

    std::map<std::string, TramType*> getSupportedTramTypes() const;

    TramType* parse(TiXmlElement* tramTypeElem) const;
};


#endif //PROJECT_SOFTWARE_PRACTICUM2_TRAMTYPEIMPORTER_H
