//
// Created by gruzi on 17/03/2023.
//

#include <gtest/gtest.h>
#include "Metronet/Metronet.h"

//class MetronetDomainTest: public ::testing::Test {
//protected:
//    Metronet metronet;
//
//    Station* station1 = new Station("A", "type", 1);
//    Station* station2 = new Station("B", "type", 1);
//    Station* station3 = new Station("C", "type", 1);
//    Station* station4 = new Station("D", "type", 1);
//
//    Tram* tram1 = new Tram(1,1, 0);
//    Tram* tram2 = new Tram(1,2, 0);
//
//    void setStations() {
//        station1->setVolgende(station2);
//        station2->setVolgende(station3);
//        station3->setVolgende(station1);
//        station1->setVorige(station3);
//        station3->setVorige(station2);
//        station2->setVorige(station1);
//    }
//};
//TEST_F(MetronetDomainTest, SettersGetters) {
//    EXPECT_TRUE(metronet.properlyInitialized());
//    EXPECT_TRUE(metronet.getSporen().empty());
//    EXPECT_TRUE(metronet.getTrams().empty());
//
//    setStations();
//
//    EXPECT_EQ(station1->getVolgende(), station2);
//    EXPECT_EQ(station2->getVolgende(), station3);
//    EXPECT_EQ(station3->getVolgende(), station1);
//    EXPECT_EQ(station1->getVorige(), station3);
//    EXPECT_EQ(station3->getVorige(), station2);
//    EXPECT_EQ(station2->getVorige(), station1);
//    EXPECT_EQ(station1->getSpoorNr(), 1);
//    EXPECT_EQ(station2->getSpoorNr(), 1);
//    EXPECT_EQ(station3->getSpoorNr(), 1);
//    EXPECT_TRUE(metronet.properlyInitialized());
//}
//TEST_F(MetronetDomainTest, Push) {
//    setStations();
//    std::map<int, Station*> sporen;
//    sporen.insert(std::make_pair(1, station1));
//    metronet.setSporen(sporen);
//    EXPECT_FALSE(metronet.getSporen().empty());
//    station4->setSpoorNr(4);
//    metronet.pushStation(station4);
//    EXPECT_EQ(metronet.getSporen().size(), 2);
//    EXPECT_TRUE(metronet.getTrams().empty());
//    metronet.pushTram(tram1);
//    EXPECT_EQ(metronet.getTrams().size(), 1);
//    std::multimap<int, Tram*> trammen;
//    trammen.insert(std::make_pair(1, tram1));
//    trammen.insert(std::make_pair(2, tram2));
//    metronet.setTrams(trammen);
//    EXPECT_EQ(metronet.getTrams().size(), 2);
//}
