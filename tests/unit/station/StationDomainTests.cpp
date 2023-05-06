//
// Created by gruzi on 18/03/2023.
//
#include <gtest/gtest.h>
#include "Station/Station.h"

class StationDomainTest: public ::testing::Test {
protected:
    Station* vorigeStation;
    Station* volgendeStation;
};

TEST_F(StationDomainTest, DefaultConstructor) {
    Station station_("test_naam", "test_type");
    EXPECT_TRUE(station_.properlyInitialized());
    EXPECT_EQ(station_.getNaam(), "test_naam");
    EXPECT_DEATH(station_.getVolgende(12), "Expected spoor to exist!");
    EXPECT_DEATH(station_.getVorige(12), "Expected spoor to exist!");
    EXPECT_EQ(station_.getType(), "test_type");
}
TEST_F(StationDomainTest, SettersGetters) {
    Station station_("test_naam", "test_type");
    const std::string name="naamTest";
    const std::string stationType="Albatros";
    std::pair<Station*,Station*> spoorTupel = std::make_pair(vorigeStation, volgendeStation);
    EXPECT_TRUE(station_.properlyInitialized());
    const int spoorNr = 17;
    EXPECT_NO_FATAL_FAILURE(station_.setNaam(name));
    EXPECT_NO_FATAL_FAILURE(station_.setType(stationType));
    EXPECT_NO_FATAL_FAILURE(station_.setSpoor(spoorNr, std::make_pair(vorigeStation, volgendeStation)));
    EXPECT_EQ(station_.getNaam(), name);
    EXPECT_EQ(station_.getType(), stationType);
    EXPECT_EQ(station_.getSpoor(17), spoorTupel);
    EXPECT_DEATH(station_.getVolgende(12), "Expected spoor to exist!");
    EXPECT_DEATH(station_.getVorige(12), "Expected spoor to exist!");
}