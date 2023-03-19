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
    Station* stationA = new Station;
    Station* stationB = new Station;
    Station* stationC = new Station;
    Station* stationD = new Station;
    Station* stationE = new Station;
    Tram* tram = new Tram;

    void setStations() {
        stationA->setNaam("A");
        stationA->setSpoorNr(314);

        stationB->setNaam("B");
        stationB->setSpoorNr(314);

        stationC->setNaam("C");
        stationC->setSpoorNr(314);

        stationD->setNaam("D");
        stationD->setSpoorNr(314);

        stationE->setNaam("E");
        stationE->setSpoorNr(314);
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
        tram->setLijnNr(314);
        metronet.pushTram(tram);
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