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
    MetronetExporter exporter;
};

TEST_F(MetronetOutputTest, ShowMeYourTrains){
    std::remove("tests/unit/metronet/output/ShowMeYourTrains.txt");
    Station* stationA = new Station;
    stationA->setNaam("A");
    stationA->setSpoorNr(314);
    Station* stationB = new Station;
    stationB->setNaam("B");
    stationB->setSpoorNr(314);
    Station* stationC = new Station;
    stationC->setNaam("C");
    stationC->setSpoorNr(314);
    Station* stationD = new Station;
    stationD->setNaam("D");
    stationD->setSpoorNr(314);
    Station* stationE = new Station;
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
    Tram* tram = new Tram;
    tram->setBeginStation(stationB);
    tram->setHuidigeStation(stationD);
    tram->setLijnNr(314);
    metronet.pushTram(tram);
    exporter.outputMetronet(metronet, "tests/unit/metronet/output/ShowMeYourTrains.txt");
    std::string haveToBe;
    std::string resultOfTest;
    std::ifstream inputStream1("tests/unit/metronet/output/ShowMeYourTrainsReference.txt");
    std::ifstream inputStream2("tests/unit/metronet/output/ShowMeYourTrains.txt");
    if (inputStream1.is_open()) {
        char mychar;
        while (inputStream1) {
            mychar = inputStream1.get();
            haveToBe += mychar;
        }
    }
    if (inputStream2.is_open()) {
        char mychar;
        while (inputStream2) {
            mychar = inputStream2.get();
            resultOfTest += mychar;
        }
    }
    EXPECT_EQ(haveToBe, resultOfTest);
}