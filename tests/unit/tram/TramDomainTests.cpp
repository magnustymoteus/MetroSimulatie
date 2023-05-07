//
// Created by gruzi on 18/03/2023.
//
#include <gtest/gtest.h>
#include "Tram/Tram.h"

class TramDomainTest: public ::testing::Test {
protected:
    Station* station1 = new Station("A", "Halte");
    Station* station2 = new Station("B", "Halte");
    Station* station3 = new Station("C", "Halte");
    void setStations(){
        station1->setSpoor(1, std::make_pair(station3, station2));
        station2->setSpoor(1, std::make_pair(station1, station3));
        station3->setSpoor(1, std::make_pair(station2, station1));
    }
};

TEST_F(TramDomainTest, DefaultConstructor) {
    Tram tram_(1,2);
    EXPECT_TRUE(tram_.properlyInitialized());

    EXPECT_EQ(tram_.getLijnNr(), 1);
    EXPECT_FALSE(tram_.getType()->properlyInitialized());
    EXPECT_EQ(tram_.getVoertuigNr(), 2);
    EXPECT_EQ(tram_.getReparatieTijd(), 0);
    EXPECT_EQ(tram_.getAantalDefecten(), 0);

    EXPECT_FALSE(tram_.getHuidigeStation());
    EXPECT_FALSE(tram_.getBeginStation());
}
TEST_F(TramDomainTest, SettersGetters) {
    Tram tram_(1,2);
    EXPECT_TRUE(tram_.properlyInitialized());
    const int lijnNr=200;
    EXPECT_NO_FATAL_FAILURE(tram_.setVoertuigNr(12));
    EXPECT_EQ(tram_.getVoertuigNr(), 12);
    EXPECT_NO_FATAL_FAILURE(tram_.setAantalDefecten(10));
    EXPECT_EQ(tram_.getAantalDefecten(), 10);
    EXPECT_NO_FATAL_FAILURE(tram_.setReparatieTijd(2));
    EXPECT_EQ(tram_.getReparatieTijd(), 2);
    std::vector<std::string> bediendeStations;
    bediendeStations.emplace_back("Halte");
    TramType* tramType = new TramType("Albatros", 90, bediendeStations);
    EXPECT_NO_FATAL_FAILURE(tram_.setType(tramType));
    EXPECT_NO_FATAL_FAILURE(tram_.setLijnNr(lijnNr));
    EXPECT_EQ(tram_.getType(), tramType);
    EXPECT_EQ(tram_.getLijnNr(), lijnNr);
    EXPECT_FALSE(tram_.getBeginStation());
    EXPECT_FALSE(tram_.getHuidigeStation());
    delete tramType;
}
TEST_F(TramDomainTest, MoveOneTram){
    Tram tram(1, 2);
    setStations();
    tram.setBeginStation(station1);
    tram.setHuidigeStation(station1);
    std::vector<std::string > bediendeStations;
    bediendeStations.push_back("Halte");
    TramType* tramType = new TramType("Stadslijner", 70, bediendeStations);
    EXPECT_NO_THROW(tram.setType(tramType));
    EXPECT_NO_THROW(tram.move());
    Station* huidigeStation = tram.getHuidigeStation();
    EXPECT_EQ(huidigeStation, station2);
    delete tramType;
}