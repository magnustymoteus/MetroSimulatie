//
// Created by gruzi on 24/04/2023.
//

#ifndef PROJECT_SOFTWARE_PRACTICUM2_VMETROOBJECTIMPORTER_H
#define PROJECT_SOFTWARE_PRACTICUM2_VMETROOBJECTIMPORTER_H

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>

#include "tinyxml/tinyxml.h"

#include "IMetroObject.h"

#include "DesignByContract.h"

/**
 * @brief An importer for IMetroObject
 * @author Patryk Pilichowski
 * @author Daria Matviichuk
 * @date 30/04/2023
 * @version 0.1
 */

class VMetroObjectImporter {
private:
    VMetroObjectImporter* _initCheck;
protected:
    std::map<std::string, std::vector<std::string> > fSupportedTags;
    std::string configPath;
public:
    bool properlyInitialized() const;
    /**
     * @brief Initializes the config path and calls loadSupportedTags()
     * @param configFilePath The path to the config file of the IMetroObject
     */
    VMetroObjectImporter(const std::string &configFilePath);

    /**
     * @brief Sets the config path to the new value
     * @param configFilePath The new value
     */
    void setConfigPath(const std::string &configFilePath);
    /**
     * @brief Gets the file path to the config
     * @return a string representing the file path to the config
     */
    std::string getConfigPath() const;

    /**
     * @brief Checks if a tag is supported
     * @param tagName The name of the tag
     * @return A boolean denoting if the tag is supported
     */
    bool isTagSupported(const std::string &tagName) const;
    /**
     * @brief Checks if a property of a certain tag is supported
     * @param tagName The name of the tag
     * @param propertyName The name of the property of the tag
     * @return A boolean denoting if the property is supported
     * @pre The tag itself is supported
     */
    bool isPropertySupported(const std::string &tagName, const std::string &propertyName) const;

    /**
     * @brief Loads supported tags with the default path to the configuration file
     */
    void loadSupportedTags();
    /**
     * @brief Loads supported tags with a given path to the configuration file
     * @param configFilePath The path to the configuration file
     */
    void loadSupportedTags(const std::string &configFilePath);
    /**
     * @brief Gets the tags that are supported
     * @return A map of all the supported tags
     */
    std::map<std::string, std::vector<std::string> > getSupportedTags() const;

    /**
     * @brief Parses an xml element into an instance of IMetroObject
     * @param tagElem The xml element, also called a tag
     * @return An instance of IMetroObject
     */
    virtual IMetroObject* parse(TiXmlElement *tagElem) const = 0;
};


#endif //PROJECT_SOFTWARE_PRACTICUM2_VMETROOBJECTIMPORTER_H
