//
// Created by gruzi on 17/03/2023.
//

#include <gtest/gtest.h>
#include <metronet/Metronet.h>

class MetronetDomainTest: public ::testing::Test {
protected:
    Metronet metronet;
};

TEST_F(MetronetDomainTest, GetSetPush){
    EXPECT_TRUE(metronet.getSporen().empty());
    EXPECT_TRUE(metronet.getTrams().empty());
    Station* station1 = new Station;
    Station* station2 = new Station;
    Station* station3 = new Station;
    station1->setVolgende(station2);
    station2->setVolgende(station3);
    station3->setVolgende(station1);
    EXPECT_EQ(station1->getVolgende(), station2);
    EXPECT_EQ(station2->getVolgende(), station3);
    EXPECT_EQ(station3->getVolgende(), station1);
    station1->setVorige(station3);
    station3->setVorige(station2);
    station2->setVorige(station1);
    station1->setSpoorNr(1);
    station2->setSpoorNr(1);
    station3->setSpoorNr(1);
    EXPECT_EQ(station1->getVorige(), station3);
    EXPECT_EQ(station3->getVorige(), station2);
    EXPECT_EQ(station2->getVorige(), station1);
    EXPECT_EQ(station1->getSpoorNr(), 1);
    EXPECT_EQ(station2->getSpoorNr(), 1);
    EXPECT_EQ(station3->getSpoorNr(), 1);
    std::map<int, Station*> sporen;
    sporen.insert(std::make_pair(1, station1));
    metronet.setSporen(sporen);
    EXPECT_FALSE(metronet.getSporen().empty());
    Station* station4 = new Station;
    station4->setSpoorNr(4);
    metronet.pushStation(station4);
    EXPECT_EQ(metronet.getSporen().size(), 2);
    Tram* tram1 = new Tram;
    Tram* tram2 = new Tram;
    EXPECT_TRUE(metronet.getTrams().empty());
    metronet.pushTram(tram1);
    EXPECT_EQ(metronet.getTrams().size(), 1);
    std::map<int, Tram*> trammen;
    trammen.insert(std::make_pair(1, tram1));
    trammen.insert(std::make_pair(2, tram2));
    metronet.setTrams(trammen);
    EXPECT_EQ(metronet.getTrams().size(), 2);
    // Memory leaks?
//    delete station1;
//    delete station2;
//    delete station3;
//    delete station4;
//    delete tram1;
//    delete tram2;
}
