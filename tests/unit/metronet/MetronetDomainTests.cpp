//
// Created by gruzi on 17/03/2023.
//

#include <gtest/gtest.h>
#include "Metronet/Metronet.h"

class MetronetDomainTest: public ::testing::Test {
protected:
    Metronet metronet;

    Station* station1 = new Station("A", "type");
    Station* station2 = new Station("B", "type");
    Station* station3 = new Station("C", "type");
    Station* station4 = new Station("D", "type");
    void setSporen(){
        station1->setSpoor(1, std::make_pair(station3, station2));
        station2->setSpoor(1, std::make_pair(station1, station3));
        station3->setSpoor(1, std::make_pair(station2, station1));
    }
    void setStations() {
        metronet.pushStation(station1);
        metronet.pushStation(station2);
        metronet.pushStation(station3);
    }
    Tram* tram1 = new Tram(1,1);
    Tram* tram2 = new Tram(1,2);
    void setTrams(){
        tram1->setBeginStation(station1);
        tram2->setBeginStation(station3);
        tram1->setHuidigeStation(station1);
        tram2->setHuidigeStation(station3);
        std::vector<std::string > bediendeStations;
        bediendeStations.push_back("type");
        TramType* tramType = new TramType("tramType", 40, bediendeStations);
        tram1->setType(tramType);
        tram2->setType(tramType);
        metronet.pushTram(tram1);
        metronet.pushTram(tram2);
    }
};
TEST_F(MetronetDomainTest, SettersGetters) {
    EXPECT_TRUE(metronet.properlyInitialized());
    EXPECT_TRUE(metronet.getStations().empty());
    EXPECT_TRUE(metronet.getTrams().empty());

    EXPECT_NO_THROW(setSporen());
    EXPECT_NO_THROW(setStations());

    EXPECT_EQ(station1->getVolgende(1), station2);
    EXPECT_EQ(station2->getVolgende(1), station3);
    EXPECT_EQ(station3->getVolgende(1), station1);
    EXPECT_EQ(station1->getVorige(1), station3);
    EXPECT_EQ(station3->getVorige(1), station2);
    EXPECT_EQ(station2->getVorige(1), station1);
    EXPECT_TRUE(metronet.properlyInitialized());
}
TEST_F(MetronetDomainTest, Push) {
    EXPECT_NO_THROW(setSporen());
    EXPECT_NO_THROW(setStations());
    EXPECT_EQ(metronet.getStations().size(), 3);
    EXPECT_EQ(station1->getSporen().size(), 1);
    EXPECT_EQ(station2->getSporen().size(), 1);
    EXPECT_EQ(station3->getSporen().size(), 1);

    EXPECT_NO_THROW(metronet.pushStation(station4));

    EXPECT_EQ(metronet.getStations().size(), 4);

    EXPECT_NO_THROW(metronet.pushSpoor("A", 17, std::make_pair(station4, station2)));
    EXPECT_NO_THROW(metronet.pushSpoor("B", 17, std::make_pair(station1, station3)));
    EXPECT_NO_THROW(metronet.pushSpoor("C", 17, std::make_pair(station2, station4)));
    EXPECT_NO_THROW(metronet.pushSpoor("D", 17, std::make_pair(station3, station1)));

    EXPECT_EQ(station1->getSporen().size(), 2);
    EXPECT_EQ(station2->getSporen().size(), 2);
    EXPECT_EQ(station3->getSporen().size(), 2);
    EXPECT_EQ(station4->getSporen().size(), 1);

    EXPECT_NO_THROW(setTrams());
    EXPECT_EQ(metronet.getTrams().size(), 2);
}

TEST_F(MetronetDomainTest, MoveTrams){
    EXPECT_NO_THROW(setSporen());
    EXPECT_NO_THROW(setStations());
    EXPECT_NO_THROW(setTrams());
    EXPECT_NO_THROW(metronet.moveTram(tram1, 4));
    EXPECT_NO_THROW(metronet.moveTram(tram2, 4));
    EXPECT_EQ(tram1->getHuidigeStation(), station2);
    EXPECT_EQ(tram2->getHuidigeStation(), station1);
}
TEST_F(MetronetDomainTest, AutoSimulatie){
    EXPECT_NO_THROW(setSporen());
    EXPECT_NO_THROW(setStations());
    EXPECT_NO_THROW(setTrams());
    EXPECT_NO_THROW(metronet.autoSimulate(3));
}