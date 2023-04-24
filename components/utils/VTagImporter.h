//
// Created by gruzi on 24/04/2023.
//

#ifndef PROJECT_SOFTWARE_PRACTICUM2_VTAGIMPORTER_H
#define PROJECT_SOFTWARE_PRACTICUM2_VTAGIMPORTER_H

#include <string>
#include <vector>
#include <map>

#include <tinyxml/tinyxml.h>

#include "utils/IMetroObject.h"

class VTagImporter {
protected:
    std::map<std::string, std::vector<std::string> > fSupportedTags;
    std::string configPath;
    VTagImporter* _initCheck;
public:
    VTagImporter(const std::string &configFilePath);
    bool properlyInitialized() const;

    void setConfigPath(const std::string &configFilePath);
    std::string getConfigPath() const;

    bool isTagSupported(const std::string &tagName) const;
    bool isPropertySupported(const std::string &tagName, const std::string &propertyName) const;

    void loadSupportedTags();
    void loadSupportedTags(const std::string &configFilePath);
    std::map<std::string, std::vector<std::string> > getSupportedTags() const;

    virtual IMetroObject* parse(TiXmlElement *tagElem) const = 0;
};


#endif //PROJECT_SOFTWARE_PRACTICUM2_VTAGIMPORTER_H
