//
// Created by gruzi on 06/03/2023.
//

#include "Parser.h"
#include "tinyxml.h"
#include "../../DesignByContract.h"



void Parser::parseFile(const char* &relativeFilePath) {
    TiXmlDocument doc;
    REQUIRE(doc.LoadFile(relativeFilePath), "file not found!");
    TiXmlElement* current_elem = doc.FirstChildElement();
    while(current_elem != nullptr) {
        if(current_elem->Value() == )
        current_elem = current_elem->NextSiblingElement();
    }
}