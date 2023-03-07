//
// Created by gruzi on 06/03/2023.
//

#include "Parser.h"
#include "tinyxml.h"
#include "../../DesignByContract.h"

void Parser::parseFile(const char* &relativeFilePath) {
    TiXmlDocument doc;
    REQUIRE(doc.LoadFile(relativeFilePath), "file not found!");
    bool volledigGelezen = false;
    while(!volledigGelezen) {

    }
}