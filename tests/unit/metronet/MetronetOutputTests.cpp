//
// Created by gruzi on 17/03/2023.
//
#include <gtest/gtest.h>
#include <metronet/Metronet.h>
#include <metronet/MetronetExporter.h>
#include <fstream>

class MetronetOutputTest: public ::testing::Test {
protected:
    Metronet metronet;
    Station* stationA = new Station("A", "type", 314);
    Station* stationB = new Station("B", "type", 314);
    Station* stationC = new Station("C", "type", 314);
    Station* stationD = new Station("D", "type", 314);
    Station* stationE = new Station("E", "type", 314);
    Tram* tram = new Tram(314, 1, "type");

    void setStations() {
        stationA->setVolgende(stationB);
        stationB->setVolgende(stationC);
        stationC->setVolgende(stationD);
        stationD->setVolgende(stationE);
        stationD->setVolgende(stationA);
        metronet.pushStation(stationA);
        metronet.pushStation(stationB);
        metronet.pushStation(stationC);
        metronet.pushStation(stationD);
        metronet.pushStation(stationE);
    }
    void setTram() {
        tram->setBeginStation(stationB);
        tram->setHuidigeStation(stationD);
    }
};

std::string fileToString(const std::string &filePath) {
    std::ifstream file(filePath);
    std::string content;
    content.assign( (std::istreambuf_iterator<char>(file) ),
                    (std::istreambuf_iterator<char>()    ) );
    return content;
}

TEST_F(MetronetOutputTest, ShowMeYourTrains){
    const std::string outputPath = "tests/unit/metronet/output/ShowMeYourTrains.txt";
    const std::string referencePath = "tests/unit/metronet/output/ShowMeYourTrainsReference.txt";

    setStations();
    setTram();

    MetronetExporter::outputMetronet(metronet, outputPath);
    std::string fileStrA= fileToString(outputPath), fileStrB= fileToString(referencePath);

    EXPECT_EQ(fileStrA, fileStrB);
}