//
// Created by gruzi on 17/03/2023.
//
#include <gtest/gtest.h>
#include "Metronet/MetronetExporter.h"
#include "Metronet/MetronetImporter.h"
#include <fstream>

class MetronetOutputTest: public ::testing::Test {};

std::string fileToString(const std::string &filePath) {
    std::ifstream file(filePath);
    std::string content;
    content.assign( (std::istreambuf_iterator<char>(file) ),
                    (std::istreambuf_iterator<char>()    ) );
    return content;
}

TEST_F(MetronetOutputTest, ShowMeYourTrainsSimple){
    const std::string outputPath = "tests/unit/metronet/OutputTests/output/ShowMeYourTrains.txt";
    const std::string referencePath = "tests/unit/metronet/OutputTests/references/ShowMeYourTrains.txt";
    const std::string inputPath = "tests/unit/metronet/OutputTests/input/ShowMeYourTrains.xml";
    MetronetImporter metronetImporter;
    Metronet* metronet = metronetImporter.parseFile(inputPath);
    MetronetExporter::output(metronet, outputPath);
    //std::string fileStrA= fileToString(outputPath), fileStrB= fileToString(referencePath);

    //EXPECT_EQ(fileStrA, fileStrB);
}
