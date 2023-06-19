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
#include "Exceptions/VHandleableMetroObjectException.h"

#include "DesignByContract.h"
#include "IfFalse.h"

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
    std::string fConfigPath;
public:
    bool properlyInitialized() const;
    /**
     * @brief Returns the value of an XML element (the name of the tag itself)
     * @param elem The XML element
     * @return The value of the element
     * @pre: VMetroObjectImporter is properly initialised
     * @pre elem is not null
     */
    std::string getValue(TiXmlElement* elem) const;
    /**
     * @brief Returns the text in an XML element
     * @param elem The XML element
     * @return The text of the element
     * @pre: VMetroObjectImporter is properly initialised
     * @pre elem is not null
     */
    std::string getText(TiXmlElement* elem) const;
    /**
     * @brief returns the next sibling element of an xml element
     * @param elem The current xml element
     * @param tagName The name of the first child element to be found if it's supported
     * @pre: VMetroObjectImporter is properly initialised
     * @pre The tag (sibling) of the property must be supported
     * @return The next sibling element
     */
    TiXmlElement* getNextSiblingProperty(TiXmlElement* elem, const std::string &propertyName) const;
    /**
    * @brief returns the next sibling tag
    * @pre: VMetroObjectImporter is properly initialised
    * @param elem The current xml element
    * @param tagName The tag name of the next sibling element
    * @return The next sibling element
    */
    TiXmlElement* getNextSiblingTag(TiXmlElement* elem, const std::string &tagName) const;
    /**
     * @brief returns the first child element of an xml element only if the property of the tag is supported
     * @param elem The current xml element
     * @param tagName The name of the first child element to be found if it's supported
     * @pre: VMetroObjectImporter is properly initialised
     * @pre The tag (parent) of the property must be supported
     * @return The first child element
     */
    TiXmlElement* getFirstChildProperty(TiXmlElement* elem, const std::string &propertyName) const;
    /**
     * @brief returns the first child element of an xml element only if the tag is supported
     * @pre: VMetroObjectImporter is properly initialised
     * @param elem The current xml element
     * @param tagName The name of the first child element to be found if it's supported
     * @return The first child element
     */
    TiXmlElement* getFirstChildTag(TiXmlElement* elem, const std::string &tagName) const;
    /**
     * @pre: VMetroObjectImporter is properly initialised
     * @brief Initializes the config path and calls loadSupportedTags()
     * @param configFilePath The path to the config file of the IMetroObject
     */
    VMetroObjectImporter(const std::string &configFilePath);
    VMetroObjectImporter();

    /**
     * @brief Sets the config path to the new value
     * @pre: VMetroObjectImporter is properly initialised
     * @param configFilePath The new value
     */
    void setConfigPath(const std::string &configFilePath);
    /**
     * @brief Gets the file path to the config
     * @pre: VMetroObjectImporter is properly initialised
     * @return a string representing the file path to the config
     */
    std::string getConfigPath() const;

    /**
     * @brief Checks if a tag is supported
     * @pre: VMetroObjectImporter is properly initialised
     * @param tagName The name of the tag
     * @return A boolean denoting if the tag is supported
     */
    bool isTagSupported(const std::string &tagName) const;
    /**
     * @brief Checks if a property of a certain tag is supported
     * @pre: VMetroObjectImporter is properly initialised
     * @param tagName The name of the tag
     * @param propertyName The name of the property of the tag
     * @return A boolean denoting if the property is supported
     * @pre The tag itself is supported
     */
    bool isPropertySupported(const std::string &tagName, const std::string &propertyName) const;

    /**
     * @brief Loads supported tags with the default path to the configuration file
     * @pre: VMetroObjectImporter is properly initialised
     */
    void loadSupportedTags();
    /**
     * @brief Loads supported tags with a given path to the configuration file
     * @pre: VMetroObjectImporter is properly initialised
     * @param configFilePath The path to the configuration file
     */
    void loadSupportedTags(const std::string &configFilePath);
    /**
     * @brief Gets the tags that are supported
     * @pre: VMetroObjectImporter is properly initialised
     * @return A map of all the supported tags
     */
    std::map<std::string, std::vector<std::string> > getSupportedTags() const;

    /**
     * @brief Parses an xml element into an instance of IMetroObject
     * @pre: VMetroObjectImporter is properly initialised
     * @param tagElem The xml element, also called a tag
     * @return An instance of IMetroObject
     */
    virtual IMetroObject* parse(TiXmlElement *tagElem) const = 0;
};


#endif //PROJECT_SOFTWARE_PRACTICUM2_VMETROOBJECTIMPORTER_H
