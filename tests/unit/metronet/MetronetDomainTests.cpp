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
        station1->setVolgende(1, station2);
        station2->setVolgende(1, station3);
        station3->setVolgende(1, station1);
        station1->setVorige(1, station3);
        station3->setVorige(1, station2);
        station2->setVorige(1, station1);
        metronet.pushStation(station1);
        metronet.pushStation(station2);
        metronet.pushStation(station3);
    }
    Tram* tram1 = new Tram(1,1);
    Tram* tram2 = new Tram(1,2);
    void setTrams(){
        tram1->setBeginStation(station1);
        tram2->setBeginStation(station3);
        metronet.pushTram(tram1);
        metronet.pushTram(tram2);
    }
};
TEST_F(MetronetDomainTest, SettersGetters) {
    EXPECT_TRUE(metronet.properlyInitialized());
    EXPECT_TRUE(metronet.getStations().empty());
    EXPECT_TRUE(metronet.getTrams().empty());

    setSporen();
    setStations();

    EXPECT_EQ(station1->getVolgende(1), station2);
    EXPECT_EQ(station2->getVolgende(1), station3);
    EXPECT_EQ(station3->getVolgende(1), station1);
    EXPECT_EQ(station1->getVorige(1), station3);
    EXPECT_EQ(station3->getVorige(1), station2);
    EXPECT_EQ(station2->getVorige(1), station1);
    EXPECT_TRUE(metronet.properlyInitialized());
}
TEST_F(MetronetDomainTest, Push) {
    setSporen();
    setStations();
    EXPECT_EQ(metronet.getStations().size(), 3);
    EXPECT_EQ(station1->getSporen().size(), 1);
    EXPECT_EQ(station2->getSporen().size(), 1);
    EXPECT_EQ(station3->getSporen().size(), 1);

    metronet.pushStation(station4);

    EXPECT_EQ(metronet.getStations().size(), 4);

    metronet.pushSpoor("A", 17, std::make_pair(station4, station2));
    metronet.pushSpoor("B", 17, std::make_pair(station1, station3));
    metronet.pushSpoor("C", 17, std::make_pair(station2, station4));
    metronet.pushSpoor("D", 17, std::make_pair(station3, station1));

    EXPECT_EQ(station1->getSporen().size(), 2);
    EXPECT_EQ(station2->getSporen().size(), 2);
    EXPECT_EQ(station3->getSporen().size(), 2);
    EXPECT_EQ(station4->getSporen().size(), 1);

    setTrams();
    EXPECT_EQ(metronet.getTrams().size(), 2);
}

//TEST_F(MetronetDomainTest, MoveTrams){
//    setSporen();
//    setStations();
//    setTrams();
//    EXPECT_NO_THROW(metronet.moveTram(tram1, 3));
//    EXPECT_NO_THROW(metronet.moveTram(tram2, 3));
//}
