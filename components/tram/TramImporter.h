//
// Created by gruzi on 20/04/2023.
//

#ifndef PROJECT_SOFTWARE_PRACTICUM2_TRAMIMPORTER_H
#define PROJECT_SOFTWARE_PRACTICUM2_TRAMIMPORTER_H

#include <tinyxml/tinyxml.h>
#include <vector>
#include <string>

class TramImporter {
protected:
    std::vector<std::string> fSupportedTramTypes;
    TramImporter* _initCheck;
    std::string configPath;
public:
    TramImporter();
    bool properlyInitialized() const;

    void setConfigPath(const std::string &configFilePath);
    std::string getConfigPath() const;
    std::vector<std::string> getSupportedTramTypes() const;

    void loadSupportedTramTypes();
    bool isTramTypeSupported(const std::string &tramType) const;
};


#endif //PROJECT_SOFTWARE_PRACTICUM2_TRAMIMPORTER_H
